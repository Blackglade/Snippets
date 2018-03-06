#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#include <pic16f628a.h>
#define _XTAL_FREQ 20000000

void USART_init(void){
   
   TRISBbits.TRISB1 = 1;
   TRISBbits.TRISB2 = 1;
   
   SPBRG = 0x9;

   TXSTAbits.SYNC = 1;
   RCSTAbits.SPEN = 1;
   TXSTAbits.CSRC = 1;
   
   TXSTAbits.TXEN = 1;
}

void main(void){
   unsigned char msg[] = "HelloWorld";
   unsigned int i;
   USART_init();
   TRISBbits.TRISB0 = 0;
   while(1){
       PORTBbits.RB0 = 1;
       for(i = 0; i < 10; i++){
           while(PIR1bits.TXIF == 0 && TXSTAbits.TRMT == 0){}
           TXREG = msg[i];
       }
       PORTBbits.RB0 = 0;
       __delay_ms(1000);
   }
   
}