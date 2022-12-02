
#include "delayT0.h" 
static uint8_t delay_init(void)
{
       double Fin,_1count,_1msCounts;
       uint16_t Ps_test;
       uint8_t _1ms;
       
       Fin= (double)Fclk_CPU;
       _1count = (double)(1.0/Fin);
       _1count*=1E9;
       _1msCounts = (double)(1E6/_1count);
        _1ms = (uint8_t) _1msCounts;
       if (_1msCounts>(double)200)
       {
          Ps_test = (uint16_t)(_1msCounts/200);
          PS_NO();
          if(Ps_test <=8)
          {
              Ps_test = 8 ;             
              PS_8();
          }
          else if(Ps_test <=64)
          {
              Ps_test = 64 ;          
              PS_64();
          }
          else if(Ps_test <=256)
          {
              Ps_test = 256 ;           
              PS_256();
          }
          else if(Ps_test <=1024)
          {
              Ps_test = 1024 ;         
              PS_1024();
          }
          
         Fin= (double)(Fclk_CPU/Ps_test);
       _1count = (double)(1/Fin);
       _1count*=1E9;
       _1msCounts = (double)(1E6/_1count);
      _1ms = (uint8_t) _1msCounts;
      
       }
        
        return (_1ms);
}

   
void delay_ms(uint32_t t)
{
    uint8_t _0Entering=0;
    uint8_t _1ms;
    _1ms=delay_init();
    if(_0Entering==0){delay_init();_0Entering = 1 ; }
    uint32_t counter = 0 ;  
    while(counter<t)
    {
    TCNT0_REG = 0 ;
    while(TCNT0_REG<=(uint8_t)_1ms);
    counter++;
    }
}