PLATFORM := nrf5x

#*************************************** PILL DISPENSER PROJECT CONFIGURATIONS ***************************************

#*************************************** PILL DISPENSER TARGET BOARD *******************************
# NRF52 Boards
KIT := PCA10040
#KIT := TAGPCC_001
#KIT := TE8707
#******************************************************************************************************

#*************************************** PROJECT PRODUCT NAME ***************************************
PRODUCT := TWI_BLE_ALIGN_TAG_VITA_SDK
#****************************************************************************************************

#*************************************** PROJECT PRODUCT NAME ***************************************
PROJECT_NAME := BLE_ALIGN_TAG
#******************************************************************************************************

#*************************************** PROJECT BUILD TYPE *******************************************
BUILD_TYPE := debug
#BUILD_TYPE := release
##****************************************************************************************************
TWI_STACK_SZ = 2048
TWI_HEAP_SZ = 0

ifeq ($(KIT),$(filter $(KIT),PCA10040 TAGPCC_001 TE8707))
DEVICE := nrf52
CFLAGS += -DNRF52
endif

CFLAGS += -D$(PRODUCT)

#*************************************** PROJECT IMAGE TYPE *****************************************
IMAGE_TYPE := NORMAL
#****************************************************************************************************

#********************************************* C FLAGS **********************************************
include twi_align_tag_cflags.mk
#****************************************************************************************************

#*************************************** PROJECT HEX TYPE *******************************************
HEX_TYPE := WITHOUT_SD
#HEX_TYPE := WITH_SD
#****************************************************************************************************
ifeq ($(BUILD_TYPE), debug)
DEBUGGING := DEBUGGING_ENABLE
else
DEBUGGING := DEBUGGING_DISABLE
endif

#*************************************** PROJECT FIRMWARE VERSION ***********************************
TWI_FW_MAJOR_VERSION := 0
TWI_FW_MINOR_VERSION := 2
TWI_FW_PATCH_VERSION := 4

CFLAGS += -DTWI_FW_MAJOR_VERSION=$(TWI_FW_MAJOR_VERSION)
CFLAGS += -DTWI_FW_MINOR_VERSION=$(TWI_FW_MINOR_VERSION)
CFLAGS += -DTWI_FW_PATCH_VERSION=$(TWI_FW_PATCH_VERSION)
#****************************************************************************************************

#*************************************** PROJECT OUTPUT FILENAME ***********************************
OUTPUT_FILENAME := $(PROJECT_NAME)_$(KIT)_$(BUILD_TYPE)_v$(TWI_FW_MAJOR_VERSION)_$(TWI_FW_MINOR_VERSION)_$(TWI_FW_PATCH_VERSION)
#***************************************************************************************************

#************************************ PROJECT NORDIC SDK VERSION ***********************************
#NORDIC_SDK_VERSION := nordic_sdk_12_2_0
NORDIC_SDK_VERSION := nordic_sdk_16_0_0
#***************************************************************************************************

#************* Enter your SDK installation directory **************************
SDK_PATH = C:/platform_sdk/nordic_sdk/$(NORDIC_SDK_VERSION)/nordic_sdk/
SDK_NAME = master	
SDK_VER  = GIT_SDK_VER
#******************************************************************************

#*************  Enter your branch path ****************************************
BRANCH_PATH = ../../../../../../
#******************************************************************************

#********************** PROJECT Libraries to be linked  ***********************	
ifeq ($(BUILD_TYPE), debug)
LDFLAGS += -l_twi_vita_sdk
LDFLAGS += -l_twi_stack
TWI_LIB_DIRS += -L"../../../../Security_Communication_Libraries/Debug_Version"
else
LDFLAGS += -l_twi_vita_sdk
LDFLAGS += -l_twi_stack
TWI_LIB_DIRS += -L"../../../../Security_Communication_Libraries/Release_Verison"
endif
#******************************************************************************


#*************** END OF PILL DISPENSER PROJECT CONFIGURATIONS *****************

# GIT_VER_SZ = 7
# GIT_VER = $(shell git rev-parse --short=$(GIT_VER_SZ) HEAD)
# GIT_NAME = $(shell git rev-parse --abbrev-ref HEAD)

# CFLAGS += -DGIT_VER_SIZE=$(GIT_VER_SZ)
# CFLAGS += -DGIT_VERSION=\"$(GIT_VER)\"
# CFLAGS += -DGIT_BRANCH_NAME=\"$(GIT_NAME)\"

CFLAGS += -D$(USE_SOFTDEVICE)
CFLAGS += -D$(NORDIC_SDK_VERSION)

#************* Include paths **************************************************
INCLUDEPATHS += -I"../../../../../../common/include"
INCLUDEPATHS += -I"../../../../../../twi_protocols/twi_ble_aml_v2_proto"
INCLUDEPATHS += -I"../../../../../../twi_protocols/twi_rh_proto"
INCLUDEPATHS += -I"../../../products/ble_align_tag"
INCLUDEPATHS += -I"../../../twi_app/include"
INCLUDEPATHS += -I"../../../../twi_vita_sdk/include"
INCLUDEPATHS += -I"../../../../../../hal/source/nrf5x"
INCLUDEPATHS += -I"../../../../../../hal/source/ext_sensors/temperature_sensor/as621x"
INCLUDEPATHS += -I"../../../../../../hal/source/ext_sensors/ms5637_sensor"
INCLUDEPATHS += -I"../../../../../../hal/source/ext_sensors/accelerometer/kxtj3/"
INCLUDEPATHS += -I"../../../../../../hal/source/ext_sensors/df_8800_sensor"
INCLUDEPATHS += -I"../../../../../../twi_protocols/twi_rh_proto/hardware/twi_rhp_hw_peripheral"
INCLUDEPATHS += -I"../../../../../../twi_protocols/twi_rh_proto/hardware"
INCLUDEPATHS += -I"../../../../../../twi_protocols/twi_rh_proto/hardware/twi_rhp_hw_digital"
INCLUDEPATHS += -I"../../../../../../twi_protocols/twi_rh_proto/hardware/twi_rhp_hw_sensor"
INCLUDEPATHS += -I"../../../../../../twi_protocols/twi_rh_proto/hardware/twi_rhp_hw_abstract"
INCLUDEPATHS += -I"../../../../../../utils/twi_nvds"
INCLUDEPATHS += -I"../../../../../../utils/twi_ble_adv_scan"
INCLUDEPATHS += -I"../../../../../../utils/twi_conn_param_mgmt"
INCLUDEPATHS += -I"$(SDK_PATH)components/device"
INCLUDEPATHS += -I"$(SDK_PATH)components/toolchain"
INCLUDEPATHS += -I"$(SDK_PATH)components/ble/common"
INCLUDEPATHS += -I"$(SDK_PATH)components/softdevice/common/softdevice_handler"
INCLUDEPATHS += -I"$(SDK_PATH)components/drivers_nrf/delay"
INCLUDEPATHS += -I"$(SDK_PATH)components/libraries/util"
INCLUDEPATHS += -I"$(SDK_PATH)components/libraries/timer"
INCLUDEPATHS += -I"$(SDK_PATH)components/libraries/log"
INCLUDEPATHS += -I"$(SDK_PATH)components/libraries/log/src"
INCLUDEPATHS += -I"$(SDK_PATH)components/drivers_nrf/hal"
INCLUDEPATHS += -I"$(SDK_PATH)components/toolchain/gcc"

ifeq ($(NORDIC_SDK_VERSION), $(filter $(NORDIC_SDK_VERSION), nordic_sdk_12_2_0))
INCLUDEPATHS += -I"$(SDK_PATH)components/toolchain/CMSIS/Include"
ifeq ($(USE_SOFTDEVICE), $(filter $(USE_SOFTDEVICE), s132))
INCLUDEPATHS += -I"$(SDK_PATH)components/softdevice/$(USE_SOFTDEVICE)/headers"
ifeq ($(DEVICE), $(filter $(DEVICE), nrf52))
INCLUDEPATHS += -I"$(SDK_PATH)components/softdevice/$(USE_SOFTDEVICE)/headers/$(DEVICE)"
endif
endif 
endif

##************* Source paths **************************************************
C_SOURCE_PATHS += ../../../products/ble_align_tag
C_SOURCE_PATHS += ../../../../../../hal/source/ext_sensors/bat_sensor
C_SOURCE_PATHS += ../../../../../../hal/source/ext_sensors/temperature_sensor/as621x/
C_SOURCE_PATHS += ../../../../../../hal/source/ext_sensors/ms5637_sensor/
C_SOURCE_PATHS += ../../../../../../hal/source/ext_sensors/accelerometer/kxtj3/
C_SOURCE_PATHS += ../../../../../../hal/source/ext_sensors/df_8800_sensor/
C_SOURCE_PATHS += ../../../../../../hal/source/ext_sensors/ph_sensor/Align/
C_SOURCE_PATHS += ../../../../../../twi_protocols/twi_rh_proto/hardware/twi_rhp_hw_sensor
C_SOURCE_PATHS += ../../../../../../twi_protocols/twi_rh_proto/hardware/twi_rhp_hw_peripheral
C_SOURCE_PATHS += $(SDK_PATH)components/softdevice/common/softdevice_handler
C_SOURCE_PATHS += $(SDK_PATH)components/libraries/util
C_SOURCE_PATHS += $(SDK_PATH)components/toolchain
C_SOURCE_PATHS += $(SDK_PATH)components/ble/common

CFLAGS += -DTWI_APP_DEVICE_NAME=\""Align Tag"\"
#*************************************************************************************************************

#********************** PILL DISPENSER PROJECT TWI PLUGINS *********************
TWI_PLUGINS += ENABLE_SAVE_SETTINGS_RESET
#TWI_PLUGINS += TWI_RHP_TRIGGER
#*******************************************************************************

#****************************** RHP BLE ROLE ***********************************
BLE_ROLE += BLE_PERIPHERAL_ROLE_SUPPORTED
#*******************************************************************************

#*********************** Assembler flags ***************************************
ASMFLAGS += -D__STACK_SIZE=$(TWI_STACK_SZ)
ASMFLAGS += -D__HEAP_SIZE=$(TWI_HEAP_SZ)

############################################STARTUP SOURCE############################################
C_SOURCE_FILES += system_$(DEVICE).c

############################################ Drivers SOURCES ############################################
ifeq (MOCK_SENSORS, $(findstring MOCK_SENSORS,$(CFLAGS)))

else
C_SOURCE_FILES += twi_ms5637_sensor.c
C_SOURCE_FILES += twi_rhp_hw_pressure_sensor_handlers.c
C_SOURCE_FILES += twi_accelerometer_kxtj3_driver.c
C_SOURCE_FILES += twi_accelerometer.c
C_SOURCE_FILES += twi_rhp_hw_acc_sensor_handlers.c
C_SOURCE_FILES += twi_temp_as621x_temp_sensor.c
C_SOURCE_FILES += twi_rhp_hw_temp_sensor_handlers.c
C_SOURCE_FILES += twi_df_8800_sensor.c
C_SOURCE_FILES += twi_rhp_hw_force_sensor_handlers.c
C_SOURCE_FILES += twi_ph_sensor.c
C_SOURCE_FILES += twi_rhp_hw_ph_sensor_handlers.c
endif
C_SOURCE_FILES += twi_bat_sensor.c

############################################ PROFILE SOURCES ############################################
C_SOURCE_FILES += twi_rhp_ble_align_tag_app.c
C_SOURCE_FILES += twi_rhp_ble_align_tag_profile.c
C_SOURCE_FILES += twi_ble_align_tag_uuids_cfg.c
C_SOURCE_FILES += twi_opp_app.c
############################################ ASSEMBLY SOURCES ############################################
ASSEMBLER_SOURCE_FILES += gcc_startup_$(DEVICE).s

#**********************  SDK SOURSE  ************************************************
SDK_SOURCE_PATH = $(SDK_PATH)components/

include $(BRANCH_PATH)common/gcc/Makefile.TWI
