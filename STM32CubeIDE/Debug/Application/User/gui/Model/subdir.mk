################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Application/User/gui/Model/Bullet.cpp \
../Application/User/gui/Model/Enemy.cpp \
../Application/User/gui/Model/Ship.cpp 

OBJS += \
./Application/User/gui/Model/Bullet.o \
./Application/User/gui/Model/Enemy.o \
./Application/User/gui/Model/Ship.o 

CPP_DEPS += \
./Application/User/gui/Model/Bullet.d \
./Application/User/gui/Model/Enemy.d \
./Application/User/gui/Model/Ship.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/gui/Model/%.o Application/User/gui/Model/%.su Application/User/gui/Model/%.cyclo: ../Application/User/gui/Model/%.cpp Application/User/gui/Model/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F429xx -c -I../../Core/Inc -I../../Drivers/CMSIS/Include -I../../Drivers/BSP -I../../TouchGFX/target -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../TouchGFX/App -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../../TouchGFX/target/generated -I../../Middlewares/Third_Party/FreeRTOS/Source/include -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/gui/include -I../../TouchGFX/generated/videos/include -Os -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-gui-2f-Model

clean-Application-2f-User-2f-gui-2f-Model:
	-$(RM) ./Application/User/gui/Model/Bullet.cyclo ./Application/User/gui/Model/Bullet.d ./Application/User/gui/Model/Bullet.o ./Application/User/gui/Model/Bullet.su ./Application/User/gui/Model/Enemy.cyclo ./Application/User/gui/Model/Enemy.d ./Application/User/gui/Model/Enemy.o ./Application/User/gui/Model/Enemy.su ./Application/User/gui/Model/Ship.cyclo ./Application/User/gui/Model/Ship.d ./Application/User/gui/Model/Ship.o ./Application/User/gui/Model/Ship.su

.PHONY: clean-Application-2f-User-2f-gui-2f-Model

