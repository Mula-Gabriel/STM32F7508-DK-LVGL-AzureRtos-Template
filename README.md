# STM32F7508-DK-LVGL-AzureRtos-Template


There is 2 STM32 project :

 ExtMem_Boot : 
 The original project can be found in ST package
 This is more or less a bootloader, it boot from the internal flash, setup QSPI, clock, and external SDRAM, then it jump to external qspi flash.
 
 Template Project :
 It's based on https://github.com/lvgl/lv_port_stm32f746_disco
 
 The internal ram is allocated to Threadx pool (see _threadx_heap in the linker scrip)
 The frame buffer, (like everything actually) is place at the begining off the external sdram (see .LCD_Buffer in the linker script)
 This project build lvgl demo.
 The project create 2 task : 
 
 - LvglThread_entry_function that call lv_task_handler
 - LiveLedThread_entry_function that blink the green led
 
 Dma2d is disable for now, because lv_gpu_stm32_dma2d.c do not build.
 
