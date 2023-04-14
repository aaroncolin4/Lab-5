/*
Team Members: Aaron Colin Del Angel, Tyler Wilson, Jasiah Jospeh
Date:03/20/2023
Assignment:  Lab 5 

Description: This file implements the initialization of an external switch.
*/

/*
    Development board header PIN relation 
    PIN10 <=> (Port PB4) => PCINT4 

    Register names:
    (PCICR) Pin Change Interrupt Control Register 
    (PCMSK#) Pin Change Mask Register 
    PCIE# (PCICR group) includes PCINT0 to PCINT7 (0-7) See Datasheet for more groups
    Note: PCICR group needs to be anable first in order to enable PCMSK0 
 */


#include "switch.h"
#include <avr/io.h>

void initSwitch(){

    // Set PORTB Data Direction as input (read)    
    DDRB &= ~(1 << DDB4);  
    // enable the pull-up resistor for stable input
    PORTB |= (1 << PORTB4);     
    
    // enable PCICR register group "PCIE0" 
    PCICR |= (1 << PCIE0);

    // enable PCINT4 Register
    PCMSK0 |= (1 << PCINT4);   
}
