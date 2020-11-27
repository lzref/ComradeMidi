Introduction
===========================

Preferred way of compiling and uploading this code to the Blue Pill board is by using PlatformIO and ST-LINK (though uploading over USB-to-TTL adapters is also possible).

Step 1. Connecting Blue Pill board to a computer
================================================

In order to upload code to the Blue Pill board you'll need ST-LINK or a USB-to-TTL adapter,
since by default the board doesn't have a bootloader that would support programming via USB.
More information can be found in section 6 (Bootloader and programming tools)
[here](https://www.e-tinkers.com/2020/01/getting-started-with-stm32-and-things-you-need-to-be-aware-of/).
I recommend getting a cheap Chinese ST-LINK knockoff since you won't need to change any jumpers when programming,
you won't need to select COM-ports and it also supports debugging.
If you decide to get a USB-to-TTL adapter though, make sure it's based on a contemporary chip that's automatically recognized by operating systems.
For example, I had bad luck with PL2303HXA.

ST-LINK knockoffs may incorrectly handle the power pin and always provide power instead of sensing it
(and this can lead to burning the board if another power source is connected at the same time).
Plus, there's always a possibility of connecting 5V instead of 3.3V.
So I prefer to not connect the power wire to the ST-LINK and instead power the board with USB.

So use the following 3 wires to connect ST-LINK: ground, SWCLK, SWDIO.

![Image](https://idyl.io/wp-content/uploads/2018/07/stm32f103-pinout-diagram.png)

Step2. Compiling and uploading firmware using PlatformIO or Arduino IDE
================================================================

PlatformIO
-----------------------------

PlatformIO is an IDE that can be installed over [Atom](https://atom.io/) or [Visual Studio Code](https://code.visualstudio.com/)
(both are free and available on all major platforms). 
Visual Studio Code is preferred due to better debugging support.

Follow instructions here: https://platformio.org/platformio-ide

This repository already includes the workspace file for PlatformIO (
firmware/ComradeMidiPlatformIO.code-workspace). Just open it and you should be able to use the Upload feature (Ctrl + Alt + U).

If you use USB-to-TTL instead of ST-LINK, make sure to update the upload_protocol key in platformio.ini first.

Arduino IDE
-----------

You'll need to rename firmware/src/main.cpp into ComradeMidi.ino and place it into a directory ComradeMidi (must match the file name).

Then install [Roger Clark's STM32 core](https://github.com/rogerclarkmelbourne/Arduino_STM32/wiki/Installation).
Note that this is different from the [standard core](https://github.com/stm32duino/Arduino_Core_STM32) officially supported by ST.

Installer should ask you what libraries to install. Make sure to install the [USB Composite](https://github.com/arpruss/USBComposite_stm32f1) library.

You'll also need to install [STM32CubeProgrammer](https://www.st.com/en/development-tools/stm32cubeprog.html).

When trying to upload the code, it's very important to select the right board. Blue Pills are usually based on STM32F103C8 chip and have 64K of memory
(32K variant is often selected by default in Arduino IDE but it doesn't work)
