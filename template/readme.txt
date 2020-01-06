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

6) openocd
   clone https://github.com/riscv-mcu/riscv-openocd.git
   it looks like the branch is nuclei_dev.
   build and use.

   to break at main or anything earlier)
   riscv-none-embed-gdb -ex 'target extended-remote: 3333' ./build/gd32vf103.elf
   monitor reset halt
   load
   break XXX
   continue

   XXX maybe there is a problem with "reset". let's investigate
