// CONFIG
#pragma config FOSC = INTOSCIO  // Oscillator Selection bits (INTOSC oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA5/MCLR/VPP Pin Function Select bit (RA5/MCLR/VPP pin function is MCLR)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config LVP = OFF        // Low-Voltage Programming Enable bit (RB4/PGM pin has digital I/O function, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EE Memory Code Protection bit (Data memory code protection off)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 4000000

//--------------------------------------------------------------

#include <xc.h>
#include <stdio.h>
#include "string.h"

//------------------------------------------------
void USART_Transmit(unsigned char tx_byte)
{
  while(!TRMT) ;
  TXREG=tx_byte;
}
//------------------------------------------------
void USART_Transmit_Arr(unsigned char *tx_buff, unsigned int tx_len)
{
  unsigned int cnt=0;
  while(cnt<tx_len)
  {
    USART_Transmit(tx_buff[cnt]);
    cnt++;
  }
}
//------------------------------------------------
void USART_Transmit_Str(char *str_buff)
{
  unsigned int cnt=0;
  unsigned int tx_len = strlen(str_buff);
  while(cnt<tx_len)
  {
    USART_Transmit(str_buff[cnt]);
    cnt++;
  }
}
//------------------------------------------------





void main(void) 
{
//------------------USART------------------------------
  char str1[15];
  TRISB2 = 1; //USART (TX);
  TRISB1 = 1; //USART (RX);
  SPBRG = 12; //19200
  TX9  = 0; //off 9bit transmit 
  TXEN = 1; //on transmitter
  SYNC = 0; //async
  BRGH = 1; //high speed
  TX9D = 0; //off 9bit transmit 
  SPEN = 1; //on serial port  
//------------------USART------------------------------
  
  CMCON = 0x07;
  VRCON = 0x00;
  TRISA = 0x00;
  PORTA = 0x00;

    while(1)
    {

        //------------------USART------------------------------
        for(int i=0; i<256; i++)
        {
          switch(i % 5)
          {
              case 0:
                  PORTAbits.RA2 = 1;
                  PORTAbits.RA0 = 0;
                  PORTAbits.RA1 = 0;
                 //__delay_ms(500);
                  break;
                  
              case 1:
                  PORTAbits.RA2 = 1;
                  PORTAbits.RA0 = 1;
                  PORTAbits.RA1 = 0;
                 // __delay_ms(500);
                  break;
                  
              case 2:
                  PORTAbits.RA2 = 1;
                  PORTAbits.RA0 = 1;
                  PORTAbits.RA1 = 1;
                 // __delay_ms(500);
                  break;
                  
              case 3:
                  PORTAbits.RA2 = 0;
                  PORTAbits.RA0 = 1;
                  PORTAbits.RA1 = 1;
                  //__delay_ms(500);
                  break;
                  
              case 4:
                  PORTAbits.RA2 = 0;
                  PORTAbits.RA0 = 0;
                  PORTAbits.RA1 = 1;
                  //__delay_ms(500);
                  break;    
          }
          
          
          //TXREG=i;
          //USART_Transmit(i);
          //USART_Transmit_Arr("1234567890\r\n",12);
          //USART_Transmit_Str("1234567890\r\n");
          sprintf(str1,"PICstring%03d\r\n",i);
          USART_Transmit_Str(str1);
          __delay_ms(500);
        }

    }
    
  return;
}
