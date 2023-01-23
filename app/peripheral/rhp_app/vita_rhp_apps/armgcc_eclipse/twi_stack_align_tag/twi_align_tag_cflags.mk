#CFLAGS += -DMOCK_SENSORS 				#Define this to mock all sensor data
#CFLAGS += -DUSE_BATT_SENSOR       		# HW Handler
CFLAGS += -DUSE_TEMP_SENSOR       		# HW Handler
CFLAGS += -DUSE_PRESSURE_SENSOR			# HW Handler
CFLAGS += -DUSE_ACC_SENSOR				# HW Handler
CFLAGS += -DUSE_FORCE_SENSOR			# HW Handler
CFLAGS += -DUSE_PH_SENSOR				# HW Handler
CFLAGS += -DTEST_TRI_WAVE				# This define sending the data to cloud as triangle wave form
#CFLAGS += -DINSTANCE_SENSORS_READING 	# This flag to print the sensors readings live.
#CFLAGS += -DPACKET_DATA_TESTING  		# This flag to test each packet befor sending it.
#CFLAGS += -DTEST_GPIOS_SNIFFING 		# This flag to test the GPIOs signals for racing detection

ifeq (USE_ACC_SENSOR, $(findstring USE_ACC_SENSOR,$(CFLAGS)))
#add those to solve warnings, remove if not needed by the acc sensor
CFLAGS += -DTWI_ENABLE_ACC_HW_SETUP
CFLAGS += -DTWI_ACC_ENABLE_CONFIGRATION_FEATURE
CFLAGS += -DTWI_ACC_ENABLE_3_AXSIS_ACCELERATION_READING_FEATURE
#CFLAGS += -DTWI_HW_ACC_FULL_FUNCTION
CFLAGS += -DTWI_RHP_HW_ACC_SENSOR
CFLAGS += -DTWI_ACC_ENABLE_3_AXSIS_ACCELERATION_READING_FEATURE
CFLAGS += -DKXTJ3_ACC_SENSOR
#CFLAGS += -DENABLE_START_UP_DELAY
CFLAGS += -DENABLE_POWER_UP_DELAY
CFLAGS += -DKXTJ3_OPTIMIZATION_MODE
endif

ifeq (USE_PRESSURE_SENSOR, $(findstring USE_PRESSURE_SENSOR,$(CFLAGS)))
#ifeq ($(CFLAGS),$(filter $(CFLAGS),USE_PRESSURE_SENSOR))
CFLAGS += -DTWI_RHP_HW_PRESSURE_SENSOR		
CFLAGS += -DMS5637_PRESS_SENSOR
endif

ifeq (USE_TEMP_SENSOR, $(findstring USE_TEMP_SENSOR,$(CFLAGS)))
CFLAGS += -DTWI_RHP_HW_TEMP_SENSOR		
endif

ifeq (USE_FORCE_SENSOR, $(findstring USE_FORCE_SENSOR,$(CFLAGS)))
CFLAGS += -DTWI_RHP_HW_FORCE_SENSOR
CFLAGS += -DDF_8800_FORCE_SENSOR	
endif

ifeq (USE_PH_SENSOR, $(findstring USE_PH_SENSOR,$(CFLAGS)))
CFLAGS += -DTWI_RHP_HW_PH_SENSOR
endif

CFLAGS += -DTWI_VITA_SDK
CFLAGS += -DADV_PKT_COUNTER_ENABLED
CFLAGS += -DADVERTISE_WITHOUT_AML_AND_OPP
CFLAGS += -DTWI_RHP_HW_BLE
CFLAGS += -DOUTPUT_DESTS_NUM=1
CFLAGS += -DTWI_RHP_APP
CFLAGS += -DDISABLE_EXTENDED_RANGE
CFLAGS += -DTWI_BLE_ENABLE_TX_POWER_HANDLER
CFLAGS += -DTWI_RHP_HW_SENSORS
CFLAGS += -DTWI_RHP_HW_BAT_SENSOR
CFLAGS += -DSAVE_NVDS_DATA_USING_SAVE_SETTINGS
CFLAGS += -DSAVE_PAIRING_DATA_USING_SAVE_SETTINGS
CFLAGS += -DSAVE_SYSTEM_SETTINGS
CFLAGS += -DUTC_SAVE_SETTINGS_ENABLE
CFLAGS += -DUSE_UTC_MODULE
CFLAGS += -DTWI_RHP_HW_TIME 
CFLAGS += -DTWI_RHP_HW_ABSTRACTS 
CFLAGS += -DTWI_RHP_HW_DIGITAL
CFLAGS += -DTWI_CONN_PARAM_MGMT
CFLAGS += -DTWI_RHP_HW_PERIPHERALS
CFLAGS += -DTWI_RHP_LOGGER
CFLAGS += -DTWI_BLE_ENABLE_ADV_INTERVAL

CFLAGS += -DENABLE_WDT					# This define to enable watchdog timer
CFLAGS += -DTWI_ENABLE_SAFETY

CFLAGS += -DTWI_APP_DEVICE_NAME=\""Align Tag"\"

CFLAGS += -DBLE_ALIGN_TAG		


#VITA SDK flags
CFLAGS += -DTWI_VITA_LOGIC_SAVING_IS_ENABLED
CFLAGS += -DGENERATE_PUBLIC_DATA=1	# 50 in case using ST boards, for Nordic, it is enough to be 1 (This logic is replaced by GENERATING_PUBLIC_DATA_EVENT_BASED)
CFLAGS += -DOUTGOING_QUEUE_LENGTH=4
CFLAGS += -DINCOMING_QUEUE_LENGTH=4
# The flag is commented to undefine the auto disconnection which cause failure of the paring process after recieving GP1 command.
# When The last flag in COMM header is set it stuck
#CFLAGS += -DENABLE_AUTO_DISCONNECTION  
CFLAGS += -D__HEAP_SIZE=0
CFLAGS += -DPEER_CERT_BUF_LEN=220
#CFLAGS += -DTWI_PAIR_MODE
CFLAGS += -DTWI_PAIR_MODE_VSDK               			# DANGER !!!!!!!!!!!!!!! #
CFLAGS += -DSEC_PAIR_CURVE256R1_SUPPORT=1
CFLAGS += -DSEC_PAIR_PASSWORD_SUPPORT=0
CFLAGS += -DSEC_PAIR_ENABLE_CERTIFICATE_SUPPORT=1
CFLAGS += -DSEC_PAIR_CURVE25519_DONNA_SUPPORT=0
CFLAGS += -DSEC_PAIR_DISABLE_CERTIFICATE_SUPPORT=0
CFLAGS += -DSEC_PAIR_DATA_RAM_USE=1
CFLAGS += -DSEC_PAIR_DATA_FLASH_USE=2
CFLAGS += -DSEC_PAIR_DATA_USE=SEC_PAIR_DATA_RAM_USE
#TWI_SDK_CONTROL_SECURITY_ENABLE: This Flag allow the application to control the sdk security (Enabled or Disabled)
CFLAGS += -DTWI_SDK_CONTROL_SECURITY_ENABLE
#CFLAGS += -DENABLE_PERIODIC_NUDGE_DISCONNECTION

#RHP flags
CFLAGS += -DTWI_BLE_ENABLE_TX_POWER_HANDLER
ifeq ($(KIT),$(filter $(KIT),PCA10040 TAGPCC_001 TE8707))
CFLAGS += -DMAX_NUM_INSTANCES=15
CFLAGS += -DBLE_NRF_POWER_DCDC_ENABLE
endif
CFLAGS += -DDISABLE_APP_SENDING_BUFFER
CFLAGS += -DTWI_SLEEPMODE_WAKETIMER
#this flag "TWI_UPDATE_GET_ATTRIBUTE" to notify the app before Getting an attribute value.
#CFLAGS += -DTWI_UPDATE_GET_ATTRIBUTE
#this flag "MULTIPLY_FLASH_TIMEOUT" to adjust the timeout, it is just determined by trail and error approach.
CFLAGS += -DMULTIPLY_FLASH_TIMEOUT
#this flag "DISABLE_ADC_BUG_ERRATA_WORKARROUND" to disable the multichannel adc bug solution "errata bug"
#https://devzone.nordicsemi.com/f/nordic-q-a/94105/using-saadc-for-2-channels-burst-mode-current-consumption-remains-constant-after-nrf_drv_saadc_uninit-call
#https://infocenter.nordicsemi.com/index.jsp?topic=%2Ferrata_nRF52810_Rev3%2FERR%2FnRF52810%2FRev3%2Flatest%2Fanomaly_810_246.html
#https://devzone.nordicsemi.com/f/nordic-q-a/68486/saadc-multichannel-power-consumption-is-higher-than-single-channel
#CFLAGS += -DDISABLE_ADC_BUG_ERRATA_WORKARROUND
#FLAGS += -DTWI_RHP_PILL_DISPENSER # to be used in future
CFLAGS += -DENABLE_VITA_SDK_RESET