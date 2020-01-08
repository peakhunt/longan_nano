# longan_nano

## Most of all
I ordered this from Aliexpress expecting GD32VF103CBT6 but GD32VF103C8T6 came, which is smaller in flash/sram size.
Just ordered real CBT6.

## ToDo
1. debug setup  
   it seems to be working but needs more experiment.  
   Especially I wonder if we really have to go with SRST connected to Reset.  
   There could be an workaround using system reset of ECLIC.  
2. basic documentation (in progress )  
   ...
3. FreeRTOS template ( in progress )  
   basically demo is working but I had to modify portASM.S.  
   The issue was mcause bit encoding. It surely seems different from  
   standard RISC-V literature.
   And I'm not sure interrupt handling is being done properly.  
   It's just too hard to read the chinese Bumblebee core document.  
4. ...
