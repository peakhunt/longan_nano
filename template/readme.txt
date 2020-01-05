1) https://github.com/riscv-mcu/gd32-dfu-utils.git
   go there and download/build gd32 dfu utils
   GD32 bootloader DFU has a bug. that's why.

2) download & extract GD32VF103_Firmware_Library_V1.0.2 somewhere

3) edit DFU_UTIL and FIRMWARE_DIR in Makefile

4) make -j4

5) use DFU to flash the firmware
   5.1) hold down BOOT0 pin to enter DFU bootloader
   5.2) dfu-util -l
       will show you the device
   5.3)
