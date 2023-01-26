ifeq ($(findstring 86, $(ProgramFiles)), )
	PROGFILES := C:/Program Files
else
	PROGFILES := C:/Program Files (x86)
endif

GNU_INSTALL_ROOT := $(PROGFILES)/GNU Tools ARM Embedded/4.8 2014q1
GNU_VERSION := 4.8.3
GNU_PREFIX := arm-none-eabi

CFLAGS +=-DNRF52
DEVICE := nrf52
DEVICESERIES := nrf52832
CPU := cortex-m4

INCLUDEPATHS += -I"../../../../../../hal/source/nrf5x/nrf52/boards"
INCLUDEPATHS += -I"../../../../../../hal/source/nrf5x/nrf52"

CFLAGS += -DNRF_SD_BLE_API_VERSION=4
ASMFLAGS += -DNRF_SD_BLE_API_VERSION=4

# Define the used LF Clock source depending on board type.
ifeq ($(KIT),$(filter $(KIT),TAGPCC_001))
	CFLAGS += -DUSE_RC_LFCLK
else
	CFLAGS += -DUSE_XTAL_LFCLK
endif

# SOFTDEVICE_PATH := Align-Package\platform_sdk\softdevice
NORDIC_SDK_VERSION := nordic_sdk_16_0_0

SDK_PATH = ../../../../../../../platform_sdk/nordic_sdk/$(NORDIC_SDK_VERSION)/nordic_sdk/

CFLAGS += -DS132
OTHER_HEX += s132_nrf52_7.0.1_softdevice.hex

LINKER_SCRIPT_PATH := -L ../../../../../../../platform_sdk/softdevice/s132/toolchain/armgcc
LINKER_SCRIPT = armgcc_s132_nrf52832_xxaa.ld

# Toolchain commands
NO_ECHO 		:= @
CC       		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-gcc"
CPP       		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-g++"
AS       		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-as"
AR       		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ar" -r
LD       		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-ld"
NM       		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-nm"
OBJDUMP  		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objdump"
OBJCOPY  		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-objcopy"
SIZE    		:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-size" -Ax
STRIP			:= $(NO_ECHO)"$(GNU_INSTALL_ROOT)/bin/$(GNU_PREFIX)-strip" --strip-unneeded


BUILD_DIRECTORY	:= _build

ifeq ($(BUILD_TYPE), debug)
		BUILD_TYPE_DIRECTORY := $(BUILD_DIRECTORY)\_debug
	else
		ifeq ($(BUILD_TYPE), release)
			BUILD_TYPE_DIRECTORY := $(BUILD_DIRECTORY)\_release
		endif
endif


OUTPUT_BINARY_DIRECTORY := $(BUILD_TYPE_DIRECTORY)\_binary

OBJECT_DIRECTORY		:= $(BUILD_TYPE_DIRECTORY)\_obj_folder
LISTING_DIRECTORY		:= $(BUILD_TYPE_DIRECTORY)\_linking_folder

MK				:= mkdir
RM				:= rm -rf
CP				:= cp -r

# Linker flags
LDFLAGS += -L"$(GNU_INSTALL_ROOT)/arm-none-eabi/lib/armv6-m"
LDFLAGS += -L"$(GNU_INSTALL_ROOT)/lib/gcc/arm-none-eabi/$(GNU_VERSION)/armv6-m"
LDFLAGS += $(TWI_LIB_DIRS)
LDFLAGS += -Xlinker -Map=$(LISTING_DIRECTORY)/$(OUTPUT_FILENAME).map
LDFLAGS += -mcpu=$(CPU) -mthumb -mabi=aapcs $(LINKER_SCRIPT_PATH) -L $(MAKEFILE_COMMON_PATH) -T$(LINKER_SCRIPT) 
LDFLAGS += -fwhole-program -Os --specs=nano.specs
LDFLAGS += -Wl,--start-group -lc -lc -lnosys $(addprefix -l_, $(TWI_LIBS)) -Wl,--end-group

CFLAGS += $(addprefix -D, $(BLE_ROLE))
CFLAGS += $(addprefix -D, $(TP_ROLE))
CFLAGS += $(addprefix -D, $(TWI_FLAGS))
CFLAGS += $(addprefix -D, $(TWI_PLUGINS))
CFLAGS += $(addprefix -D, $(TWI_MP_MODE))
CFLAGS += $(addprefix -D, $(TWI_DEBUG_MODE))
CFLAGS += -D$(PLATFORM)
CFLAGS += -D$(KIT)
CFLAGS += -D$(BUILD_TYPE)
CFLAGS += -D$(DEBUGGING)
CFLAGS += -D$(IMAGE_TYPE)
CFLAGS += -D$(HEX_TYPE)
CFLAGS += -mcpu=$(CPU) -mthumb -mabi=aapcs -D$(DEVICE) -D$(BLESTACK) -D$(DEBUGUSER) --std=gnu99
CFLAGS += -Wall
CFLAGS += -mfloat-abi=soft

# Assembler flags
ASMFLAGS += -x assembler-with-cpp

# Sorting removes duplicates
BUILD_DIRECTORIES := $(sort $(BUILD_TYPE_DIRECTORY) $(OBJECT_DIRECTORY) $(LISTING_DIRECTORY) )


####################################################################
# Rules															   #
####################################################################

C_SOURCE_FILENAMES			= $(notdir $(sort $(C_SOURCE_FILES)))
SORT_INCLUDEPATHS			= $(sort $(INCLUDEPATHS))
ASSEMBLER_SOURCE_FILENAMES	= $(notdir $(ASSEMBLER_SOURCE_FILES) )

ASSEMBLER_SOURCE_PATHS += $(SDK_PATH)components/toolchain/gcc/

ifeq ($(NORDIC_SDK_VERSION), $(filter $(NORDIC_SDK_VERSION), nordic_sdk_16_0_0))
	ASSEMBLER_SOURCE_PATHS += $(SDK_PATH)modules/nrfx/mdk/
endif

C_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(C_SOURCE_FILENAMES:.c=.o) )
ASSEMBLER_OBJECTS = $(addprefix $(OBJECT_DIRECTORY)/, $(ASSEMBLER_SOURCE_FILENAMES:.s=.o) )

# Set source lookup paths
vpath %.c $(C_SOURCE_PATHS)
vpath %.cpp $(C_SOURCE_PATHS)
vpath %.s $(ASSEMBLER_SOURCE_PATHS)

# Include automatically previously generated dependencies
#-include $(addprefix $(OBJECT_DIRECTORY)/, $(COBJS:.o=.d))

ifeq ($(BUILD_TYPE), debug)
	CFLAGS += -DDEBUG -g3 -O1
	ASMFLAGS += -DDEBUG -g3 -O1
else
	ifeq ($(BUILD_TYPE), release)
		CFLAGS += -DNDEBUG -Os
		ASMFLAGS += -DNDEBUG -Os
	endif
endif



### Targets
.PHONY: debug
debug: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex
	$(NO_ECHO)make echosize

.PHONY: release
release: $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).bin $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).hex
	$(NO_ECHO)make echosize

## Create build directories
$(BUILD_DIRECTORIES):
	$(NO_ECHO)$(MK) $@

## Create ordinary binary directory in case of all.
$(OUTPUT_BINARY_DIRECTORY):
	$(NO_ECHO)$(MK) $@

## Create objects from C source files
$(OBJECT_DIRECTORY)/%.o: %.c
	@echo Compiling file: $(notdir $<)
	$(CC) $(CFLAGS) $(SORT_INCLUDEPATHS) -MMD -o $@ -c $<

## Assemble .s files
$(OBJECT_DIRECTORY)/%.o: %.s
	@echo Compiling file: $(notdir $<)
	$(CC) $(ASMFLAGS) $(SORT_INCLUDEPATHS) -c -o $@ $<

## Link Libraries, C and assembler objects to an .out file
$(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out: $(BUILD_DIRECTORIES) $(OUTPUT_BINARY_DIRECTORY) $(C_OBJECTS) $(ASSEMBLER_OBJECTS)
	@echo Linking target: $(OUTPUT_FILENAME).out
	$(CC) $(C_OBJECTS) $(ASSEMBLER_OBJECTS) $(LDFLAGS) -o $(OUTPUT_BINARY_DIRECTORY)/$(OUTPUT_FILENAME).out
	@echo PLATFORM = $(PLATFORM) >> $(OUTPUT_BINARY_DIRECTORY)/readme.txt
	@echo KIT = $(KIT) >> $(OUTPUT_BINARY_DIRECTORY)/readme.txt
	@echo PROJECT_NAME = $(PROJECT_NAME) >> $(OUTPUT_BINARY_DIRECTORY)/readme.txt
	@echo TWI_PLUGINS = $(TWI_PLUGINS) >> $(OUTPUT_BINARY_DIRECTORY)/readme.txt

## Create binary .bin file from the .out file
%/$(OUTPUT_FILENAME).bin: %/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).bin
	$(OBJCOPY) -O binary $< $@

## Create binary .hex file from the .out file
%/$(OUTPUT_FILENAME).hex: %/$(OUTPUT_FILENAME).out
	@echo Preparing: $(OUTPUT_FILENAME).hex
	$(OBJCOPY) -O ihex $< $@

## Default build target
.DEFAULT_GOAL = all

.PHONY: all
all: clean debug

.PHONY: clean
clean:
	@echo Cleaning...
	$(NO_ECHO)$(RM) $(BUILD_TYPE_DIRECTORY)

.PHONY: clean_all
clean_all:
	@echo Cleaning All...
	$(NO_ECHO)$(RM) $(BUILD_DIRECTORY)

cflags_echo:
	@echo [$(CFLAGS)]

-include $(OBJECT_DIRECTORY)/*.d
