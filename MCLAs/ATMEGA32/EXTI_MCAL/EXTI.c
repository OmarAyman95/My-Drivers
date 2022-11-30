#include "EXTI.h" 




/**================================================================
* ExtInterrupt_init
* this function initializes a specific pin to be external interrupt pin,
* selects the mode it is working on
* INPUTS : it takes 1 argument :
* 1. Ext_interrupt_t *    
* it returns nothing !
* object examples : : 
   Ext_interrupt_t ext_INT0={INT_0,RISING_EDGE_MODE};
   Ext_interrupt_t ext_INT1={INT_1,BOTH_EDGES_MODE};
   Ext_interrupt_t ext_INT2={INT_2,FALLING_EDGE_MODE};
 
**/
void ExtInterrupt_init(Ext_interrupt_t *ext_object)
{
    GLOBAL_INTERRUPT_ENABLE();
    if(ext_object->interrupt_no == INT_0 || ext_object->interrupt_no == INT_1)
    {
        if(ext_object->interrupt_no == INT_0)GICR_REG->INT0bit=1;
        else if(ext_object->interrupt_no == INT_1)GICR_REG->INT1bit=1; 
         MCUCR_REG->_MCUCR &= ~(0b11U<<(ext_object->interrupt_no));
         if(ext_object->interrupt_mode ==RISING_EDGE_MODE)
        {
           MCUCR_REG->_MCUCR |=(RISING_EDGE_MODE<<(ext_object->interrupt_no));
        }
        else if (ext_object->interrupt_mode == FALLING_EDGE_MODE)
        {
           MCUCR_REG->_MCUCR |=(FALLING_EDGE_MODE<<(ext_object->interrupt_no));
        }
        else if (ext_object->interrupt_mode == BOTH_EDGES_MODE)
        {
           MCUCR_REG->_MCUCR |=(BOTH_EDGES_MODE<<(ext_object->interrupt_no));
        }
         else if (ext_object->interrupt_mode == LOW_LEVEL_MODE)
        {
           MCUCR_REG->_MCUCR |=(LOW_LEVEL_MODE<<(ext_object->interrupt_no));
        }
        else{}   
    }
    else if (ext_object->interrupt_no == INT_2)
    {
        GICR_REG->INT2bit = 1 ;
  
       if(ext_object->interrupt_mode ==RISING_EDGE_MODE)
       {
           MCUCSR_REG->ISC2bit = 1; 
       }
       else if (ext_object->interrupt_mode == FALLING_EDGE_MODE)
       {
            MCUCSR_REG->ISC2bit = 0; 
       }
       else{}  
    }
    else{}
    
}

ISR(INT0_vect)
{
    //PORTB_Toggle_pin(_PIN0);
    PORT_Toggle_pin(GPIOB,_PIN0);
}
ISR(INT1_vect)
{
  // PORTB_Toggle_pin(_PIN1);
    PORT_Toggle_pin(GPIOB,_PIN1);     
}
ISR(INT2_vect)
{
    // PORTB_Toggle_pin(_PIN3);
      PORT_Toggle_pin(GPIOB,_PIN3);
   
}