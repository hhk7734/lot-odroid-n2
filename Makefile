MAJOR   = 0
MINOR   = 1
PATCH   = 0
VERSION = $(MAJOR).$(MINOR).$(PATCH)

STATIC_LIB  = liblot.a
DYNAMIC_LIB = liblot.so

BUILD_DIR     = build
LOCAL_INCLUDE = /usr/local/include/lot
LOCAL_LIB     = /usr/local/lib

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

CXXSRCS = \

INCS_DIR = .\

LOT_API_HEADERS = $(shell ls lot-API/*.h)
LOT_HEADERS     = $(shell ls *.h)

all: $(DYNAMIC_LIB).$(VERSION)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

.PHONY: install
install:
	install -m 0755 -d $(LOCAL_INCLUDE)
	install -m 0755 -d $(LOCAL_INCLUDE)/lot-API
	install -m 0644 $(LOT_HEADERS) $(LOCAL_INCLUDE)
	install -m 0644 $(LOT_API_HEADERS) $(LOCAL_INCLUDE)/lot-API
	install -m 0755 -d $(LOCAL_LIB)
	install -m 0755 $(BUILD_DIR)/$(DYNAMIC_LIB).$(VERSION) $(LOCAL_LIB)
	ln -sf $(LOCAL_LIB)/$(DYNAMIC_LIB).$(VERSION) $(LOCAL_LIB)/$(DYNAMIC_LIB).$(MAJOR)
	ln -sf $(LOCAL_LIB)/$(DYNAMIC_LIB).$(MAJOR) $(LOCAL_LIB)/$(DYNAMIC_LIB)
	ldconfig

.PHONY: uninstall
uninstall:
	rm -rf $(LOCAL_INCLUDE)
	rm -f $(LOCAL_LIB)/liblot.*
	ldconfig

.PHONY: clang
clang: $(call rwildcard,,*.c) $(call rwildcard,,*.cpp) $(call rwildcard,,*.h)
	clang-format -style=file -i -verbose $^

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