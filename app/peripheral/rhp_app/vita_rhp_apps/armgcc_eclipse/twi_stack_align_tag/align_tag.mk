TWI_RHPVITA_DIR := .\twi_rhpvita_library
TWI_RHPVITA_LIB_DIR := $(TWI_RHPVITA_DIR)\gcc\$(BUILD_TYPE)

TWI_LIB_DIRS += -L"$(TWI_RHPVITA_LIB_DIR)"

TWI_RHPVITA_LIBRARIY1_FILES_DIRS 	+= $(BRANCH_PATH)app\peripheral/twi_vita_sdk/vita_sdk_lib/gcc/$(BUILD_TYPE)
TWI_RHPVITA_LIBRARIY2_FILES_DIRS 	+= $(BRANCH_PATH)app\peripheral/twi_rhp/twi_rhp_lib/gcc/$(BUILD_TYPE)
TWI_RHPVITA_LIBRARIY1_FILES 		+= lib_twi_vita_sdk.a
TWI_RHPVITA_LIBRARIY2_FILES 		+= lib_twi_rhp.a

prebuildrhpvita:
	@call $(BRANCH_PATH)scripts/src/git_all.bat $(SDK_NAME) $(SDK_VER)
	
twi_rhpvita: $(OBJECT_DIRECTORY) $(TWI_RHPVITA_LIB_DIR) 
	@echo ********** Creating Library: lib_$@.a **********
	$(RM) $(TWI_RHPVITA_LIB_DIR)/lib_$@.a
	$(AR) $(TWI_RHPVITA_LIB_DIR)/lib_$@.a $(TWI_RHPVITA_LIBRARIY1_FILES_DIRS)/$(TWI_RHPVITA_LIBRARIY1_FILES) $(TWI_RHPVITA_LIBRARIY2_FILES_DIRS)/$(TWI_RHPVITA_LIBRARIY2_FILES)
	$(STRIP) $(TWI_RHPVITA_LIB_DIR)/lib_$@.a
	$(CP) $(TWI_RHPVITA_LIB_DIR)/lib_$@.a $(BRANCH_PATH)app/peripheral/conn_stack/conn_stack_lib/gcc/lib_$@_$(BUILD_TYPE).a

clean_twi_rhpvita:
	@echo ********** Cleaning lib_rhpvita **********
	$(NO_ECHO)$(RM) $(TWI_RHPVITA_LIB_DIR)

twi_rhpvita_library:  clean_twi_rhpvita
	make prebuildrhpvita clean twi_rhpvita 


rhpvita_delivery: twi_rhpvita_library
				make all

$(TWI_RHPVITA_LIB_DIR):
	$(NO_ECHO)$(MK) $@