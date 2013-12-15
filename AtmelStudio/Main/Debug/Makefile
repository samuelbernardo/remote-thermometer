################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../Comm.cpp \
../Main.cpp \
../Task2.cpp \
../Task1.cpp \
../task4.cpp


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
Comm.o \
Main.o \
Task2.o \
Task1.o \
task4.o

OBJS_AS_ARGS +=  \
Comm.o \
Main.o \
Task2.o \
Task1.o \
task4.o

C_DEPS +=  \
Comm.d \
Main.d \
Task2.d \
Task1.d \
task4.d

C_DEPS_AS_ARGS +=  \
Comm.d \
Main.d \
Task2.d \
Task1.d \
task4.d

OUTPUT_FILE_PATH +=Main.elf

OUTPUT_FILE_PATH_AS_ARGS +=Main.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler











./%.o: .././%.cpp
	@echo Building file: $<
	@echo Invoking: AVR8/GNU C Compiler : 3.4.2
	$(QUOTE)..\..\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -funsigned-char -funsigned-bitfields -DDEBUG -DARDUINO=100 -DF_CPU=16000000L  -I"../../hardware/arduino/cores/arduino" -I"../../hardware/arduino/variants/leonardo" -I".."  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega32u4 -c -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<"
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR8/GNU Linker : 3.4.2
	$(QUOTE)..\..\avr8-gnu-toolchain\bin\avr-g++.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Main.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega32u4 
	@echo Finished building target: $@
	"..\..\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Main.elf" "Main.hex"
	"..\..\avr8-gnu-toolchain\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Main.elf" "Main.eep" || exit 0
	"..\..\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Main.elf" > "Main.lss"
	"..\..\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature  "Main.elf" "Main.srec"
	"..\..\avr8-gnu-toolchain\bin\avr-size.exe" "Main.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Main.elf" "Main.a" "Main.hex" "Main.lss" "Main.eep" "Main.map" "Main.srec"
	
	
upload:
	avrdude -p m32u4 -c avr109 -P COM8   -Uflash:w:Main.hex:i  