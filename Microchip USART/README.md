Microchip USART
================
A barebone script to send and recieve data synchronously between two microcontrollers via USART. Specifically designed/tested for the PIC16F628A, but I can imagine it'll work on most PIC-compatible microcontrollers with a few modifications.


### Usage ###

Use an XC8 compiler or similar to compile the hex and load it onto a PIC Programmer. I personally used Microchip's own IDE and IPE. I used two microcontrollers, one working as a master transferring via data/clock signaling to the slave. A delay was added in the sending code to slow down the rate of transmission.


### Notes ###

* Recieving code implements a circular buffer to prevent buffer overflow and ensure all data bits are written.

* while(1) loop implimented at the end to ensure the main function doesn't loop continously

* Sending code's baud rate, clock frequency, and delay can be adjusted as desired.

### License ###
Released under the [MIT License](https://github.com/Blackglade/Snippets/blob/master/LICENSE)
