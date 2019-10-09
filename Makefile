prefix = /usr

VERSION = $(shell head -n1 debian/changelog | sed 's/.*(\([0-9]*\.[0-9]*\.[0-9]*\).*/\1/')
MAJOR   = $(shell echo $(VERSION) | sed 's/\([0-9]*\)\..*/\1/')

DYNAMIC_LIB = liblot.so

BUILD_DIR = build

CC  = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
LD  = $(CROSS_COMPILE)ld

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

CXXSRCS = lot-API/lot_ios.cpp \
          lot-API/lot_ostream.cpp \

INCS_DIR = .\

LOT_API_HEADERS  = $(shell ls lot-API/*.h)
LOT_API_HEADERS += $(shell ls lot-API/*.hpp)
LOT_HEADERS      = $(shell ls *.h)
LOT_HEADERS     += $(shell ls *.hpp)

.PHONY: all
all: $(DYNAMIC_LIB).$(VERSION)

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

$(DYNAMIC_LIB).$(VERSION):	$(OBJS)
	$(LD) -shared $(LIBS) $^ -o $(BUILD_DIR)/$@

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: install
install:
	install -m 0755 -d $(DESTDIR)$(prefix)/include/lot
	install -m 0755 -d $(DESTDIR)$(prefix)/include/lot/lot-API
	install -m 0644 $(LOT_HEADERS) $(DESTDIR)$(prefix)/include/lot
	install -m 0644 $(LOT_API_HEADERS) $(DESTDIR)$(prefix)/include/lot/lot-API
	install -m 0755 -d $(DESTDIR)$(prefix)/lib
	install -m 0755 $(BUILD_DIR)/$(DYNAMIC_LIB).$(VERSION) $(DESTDIR)$(prefix)/lib
	ln -sf $(DYNAMIC_LIB).$(VERSION) $(DESTDIR)$(prefix)/lib/$(DYNAMIC_LIB).$(MAJOR)
	ln -sf $(DYNAMIC_LIB).$(MAJOR) $(DESTDIR)$(prefix)/lib/$(DYNAMIC_LIB)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: distclean
distclean: clean

.PHONY: uninstall
uninstall:
	rm -rf $(DESTDIR)$(prefix)/include/lot
	rm -f $(DESTDIR)$(prefix)/lib/liblot.*

.PHONY: clang
clang: $(call rwildcard,,*.c) $(call rwildcard,,*.cpp) $(call rwildcard,,*.h) $(call rwildcard,,*.hpp)
	clang-format -style=file -i -verbose $^
