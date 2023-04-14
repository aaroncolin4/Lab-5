/*
Team Members: Aaron Colin Del Angel, Tyler Wilson, Jasiah Jospeh
Date:03/20/2023
Assignment:  Lab 5 
*/

#include <Arduino.h>
#include <avr/io.h>
#include "timer.h"
#include "switch.h"



/*
 * Define a set of states that can be used in the state machine using an enum.
 */

typedef enum stateType{
  wait_press, debounce_press, wait_release, debounce_release 
} stateType;

// Initialize states.  Remember to use volatile 
//prevents information from being changed by the compiler
volatile stateType buttonState = wait_press;


int main() {

  initTimer1();
  initSwitch();

  sei(); // Enable global interrupts.

  while(1){

     switch(buttonState){
      case wait_press:
        break;
      case debounce_press:
        delay_ms(1);
        buttonState = wait_release;
        break;
      case wait_release:
        break;
      case debounce_release:
        delay_ms(1);
        buttonState = wait_press;
      break;
    }
  }

  return 0;
}

/* 
Pin Change Interrupt which handles the switch being
pressed and released. When the switch is pressed and 
released, the Buzzer stops making chirping sound
*/
ISR(PCINT0_vect){
  
   //checks which state the state machine is in
  switch(buttonState){
    case wait_press:
      buttonState = debounce_press;
      break;
  
    case wait_release:
      
      break;
  }
  
}