#include "delayT0.h" 
/**================================================================
* delay_ms
* this function gives your application some delay of time as you need 
 * 
* INPUTS : it takes 1 argument :
* 1. t      >>>>  time in milli seconds you can put any value from 1ms to 
 *                  (2^32) - 1 
 * NOTE THAT : this driver depends on your CPU frequency, so you should 
 *             edit the MACRO (Fclk_CPU) every time you want to edit the clock 
 *             frequency of the cpu.
* it returns nothing !
**/

void delay_ms(int t)
   {
       int i,j;
       for(j=0;j<t;j++){
       //delay = 1ms
       for(i=0;i<=XDELAY;i++){asm("NOP");}} 
   }


