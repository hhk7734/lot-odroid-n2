prefix = /usr

VERSION = $(shell head -n1 debian/changelog | sed 's/.* .\([0-9]\+\.[0-9]\+\.[0-9]\+\).*/\1/')
MAJOR   = $(shell echo $(VERSION) | sed 's/\([0-9]*\)\..*/\1/')

STATIC_LIB  = liblot.a
DYNAMIC_LIB = liblot.so

BUILD_DIR = build

CC  = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
LD  = $(CROSS_COMPILE)g++
AR  = $(CROSS_COMPILE)ar

DEBUG = -g
COMMON_FLAGS  = -Wall -fPIC $(DEBUG)
COMMON_FLAGS += -O1
COMMON_FLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

CFLAGS  = $(COMMON_FLAGS)

CXXFLAGS  = $(COMMON_FLAGS)
CXXFLAGS += -std=c++11

LIBS =

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

CSRCS = \

CXXSRCS = \
	lot-API/Log.cpp \
	lot-API/lot_ios.cpp \
	lot-API/lot_ostream.cpp \
	common/time.cpp \
	common/Uart.cpp \
	common/I2c.cpp \
	common/Spi.cpp \
	lot_gpio.cpp \

INCS_DIR = .\

LOT_API_HEADERS  = $(shell ls lot-API/*.h)
LOT_API_HEADERS += $(shell ls lot-API/*.hpp)
LOT_HEADERS      = $(shell ls *.h)
LOT_HEADERS     += $(shell ls *.hpp)

.PHONY: all
all: $(DYNAMIC_LIB).$(VERSION) pkgconfig

$(BUILD_DIR):
	mkdir $@

vpath %.c $(sort $(dir $(CSRCS)))
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(addprefix -I,$(INCS_DIR)) -Wa,-a,-ad,-alms=$(@:.o=.lst) -c -o $@ $<
 
vpath %.cpp $(sort $(dir $(CXXSRCS)))
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCS_DIR)) -Wa,-a,-ad,-alms=$(@:.o=.lst) -c -o $@ $<

OBJS  = $(addprefix $(BUILD_DIR)/,$(notdir $(patsubst %.c,%.o,$(CSRCS))))
OBJS += $(addprefix $(BUILD_DIR)/,$(notdir $(patsubst %.cpp,%.o,$(CXXSRCS))))
OBJS += $(call rwildcard,obj,*.o)

.PHONY: $(DYNAMIC_LIB).$(VERSION)
$(DYNAMIC_LIB).$(VERSION): $(OBJS)
	$(LD) -shared $(LIBS) $^ -o $(BUILD_DIR)/$@

.PHONY: $(STATIC_LIB)
$(STATIC_LIB): $(OBJS)
	$(AR) rscs $(BUILD_DIR)/$@ $^

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: install
install:
	install -m 0755 -d $(DESTDIR)$(prefix)/include/lot/lot-API
	install -m 0644 $(LOT_HEADERS) $(DESTDIR)$(prefix)/include/lot
	install -m 0644 $(LOT_API_HEADERS) $(DESTDIR)$(prefix)/include/lot/lot-API
	install -m 0755 -d $(DESTDIR)$(prefix)/lib
	install -m 0755 $(BUILD_DIR)/$(DYNAMIC_LIB).$(VERSION) $(DESTDIR)$(prefix)/lib
	install -m 0755 -d $(DESTDIR)$(prefix)/share/pkgconfig
	install -m 0644 lot.pc $(DESTDIR)$(prefix)/share/pkgconfig
	ln -sf $(DYNAMIC_LIB).$(VERSION) $(DESTDIR)$(prefix)/lib/$(DYNAMIC_LIB).$(MAJOR)
	ln -sf $(DYNAMIC_LIB).$(MAJOR) $(DESTDIR)$(prefix)/lib/$(DYNAMIC_LIB)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
	sed -i 's/Version:.*$$/Version:/g' lot.pc

.PHONY: distclean
distclean: clean

.PHONY: uninstall
uninstall:
	rm -rf $(DESTDIR)$(prefix)/include/lot
	rm -f $(DESTDIR)$(prefix)/lib/liblot.*
	rm -f $(DESTDIR)$(prefix)/share/pkgconfig/lot.pc

.PHONY: clang
clang: $(call rwildcard,,*.c) $(call rwildcard,,*.cpp) $(call rwildcard,,*.h) $(call rwildcard,,*.hpp)
	clang-format -style=file -i -verbose $^

.PHONY: pkgconfig
pkgconfig:
	sed -i 's/Version:.*$$/Version: $(VERSION)/g' lot.pc