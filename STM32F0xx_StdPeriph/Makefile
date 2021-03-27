#--------------------------------- 编译器调用指令 ------------------------------------#
PREFIX := arm-none-eabi
CC := $(PREFIX)-gcc
CXX := $(PREFIX)-g++
LD := $(PREFIX)-gcc
AR := $(PREFIX)-ar
AS := $(PREFIX)-as
OBJCOPY := $(PREFIX)-objcopy
OBJDUMP := $(PREFIX)-objdump
GDB := $(PREFIX)-gdb

#------------------------------------ 编译参数 ---------------------------------------#
TARGET := Template

OPT := -Og				#软件优化等级
CSTD := -std=c11    	#C和C++标准
CXXSTD := -std=c++11 

#用到的shell命令#
RM = rm -rf   
CP = cp 
RM_FILE=$(shell find -name '*.o' -o -name '*.bin' -o -name '*.hex' -o -name '*.elf' -o -name '*.list' -o -name '*.images' -o -name '*.map') 

#编译命令选项#
AS_FLAGS += -mthumb			#汇编选项
AS_FLAGS += -mcpu=cortex-m0

CWARN_FLAGS += -Wall -Wshadow		#C语言警告提示 选项
CWARN_FLAGS += -fno-common -ffunction-sections -fdata-sections
CWARN_FLAGS += -Wimplicit-function-declaration
CWARN_FLAGS += -Wstrict-prototypes

#链接库选项
LDLIBS += -Wl,--start-group -lc -lgcc -Wl,--end-group -lm

#链接脚本
LDSCRIPT := ./STM32F072CBTx_FLASH.ld

# STM32芯片选择
DEFINES += STM32F072
DEFINES += USE_STDPERIPH_DRIVER		#决定是否调用stm32fxxx_conf头文件
DEFINES := $(addprefix -D, $(DEFINES))

#--------------------------------- 编译需要的头文件 ------------------------------------#
INCS += CMSIS/CoreSupport
INCS += CMSIS/DeviceSupport
INCS += STM32F0xx_StdPeriph_Driver/inc
INCS += USER/inc
INCS := $(addprefix -I, $(INCS))
vpath %.h ./CMSIS/CoreSupport ./CMSIS/DeviceSupport ./STM32F10x_StdPeriph_Driver/src ./USER/src
#--------------------------------- 需要编译的源码 ------------------------------------#
#ST标准外设库C文件
ST_SRC =  \
CMSIS/DeviceSupport/system_stm32f0xx.c \
STM32F0xx_StdPeriph_Driver/src/stm32f0xx_misc.c \
STM32F0xx_StdPeriph_Driver/src/stm32f0xx_rcc.c \
STM32F0xx_StdPeriph_Driver/src/stm32f0xx_gpio.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_adc.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_bkp.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_can.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_cec.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_crc.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_dac.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_dbgmcu.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_dma.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_exti.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_flash.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_fsmc.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_i2c.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_iwdg.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_pwr.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_rtc.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_sdio.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_spi.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_tim.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_usart.c \
# STM32F0xx_StdPeriph_Driver/src/stm32f0xx_wwdg.c 

#用户C文件
USR_SRC =  \
USER/src/main.c \
USER/src/led.c \
# USER/src/clock_config.c \

#汇编启动文件
AS_SRC:=  CMSIS/DeviceSupport/startup/gcc_ride7/startup_stm32f072.s

#--------------------------------- 需生成的目标 ------------------------------------#
ST_OBJS :=$(ST_SRC:%.c=%.o)
USR_OBJS :=$(USR_SRC:%.c=%.o)
C_OBJS += $(ST_OBJS)
C_OBJS += $(USR_OBJS)

AS_OBJS := $(AS_SRC:%.s=%.o)

OBJS := $(C_OBJS) $(AS_OBJS)
#--------------------------------- 编译参数整合 ------------------------------------#
# C flags
CFLAGS := $(OPT) $(CSTD) $(INCS) $(FP_FLAGS)
CFLAGS += $(DEFINES) $(ARCH_FLAGS) $(CWARN_FLAGS) -g
# Linker flags
LDFLAGS := --static
LDFLAGS += -Wl,-Map=$(TARGET).map -Wl,--gc-sections
LDFLAGS += -T$(LDSCRIPT) $(AS_FLAGS) $(LDLIBS)

#----------------------------------- 编译对象 -----------------------------------
.SUFFIXES: .elf .bin .hex .list .map .images
.SECONDEXPANSION:
.SECONDARY:

all: elf bin hex

elf: $(TARGET).elf
bin: $(TARGET).bin
hex: $(TARGET).hex
list: $(TARGET).list
images: $(TARGET).images

%.images: %.bin %.hex %.list %.map

%.bin: %.elf
	 $(OBJCOPY) -Obinary $(*).elf $(*).bin
%.hex: %.elf
	 $(OBJCOPY) -Oihex $(*).elf $(*).hex
%.list: %.elf
	 $(OBJDUMP) -S $(*).elf > $(*).list
%.elf %.map: $(OBJS) $(LDSCRIPT)
	 $(LD) $(OBJS) $(LDFLAGS) -o $(TARGET).elf
$(AS_OBJS): %.o:%.S
	 $(CC) $(ARCH_FLAGS) $(FP_FLAGS) -g -Wa,--no-warn -x assembler-with-cpp  -c $(*).S -o $(*).o
$(C_OBJS): %.o:%.c
	 $(CC) $(CFLAGS) -c $(*).c -o $(*).o
#--------------------------------- 清空缓存 ------------------------------------
clean:
	 $(RM) $(RM_FILE)
show:
	@echo $(OBJS)
.PHONY: images clean elf bin hex list flash debug