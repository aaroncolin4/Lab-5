/*
Team Members: Aaron Colin Del Angel, Tyler Wilson, Jasiah Jospeh
Date:03/20/2023
Assignment:  Lab 5 

Description: This file implements a 1ms Timer1  
//----------------------------------------------------------------------//
*/

/*
    TCCR1B - Timer/Counter 1 Control Register A (Pg.154)
              _______________________________________________________________
    Bit      |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
             |-------+-------+-------+-------+-------+-------+-------+-------|
    (0x80)   |COM1A1 |COM1A0 |COM1B1 |COM1B0 |COM1C1 |COM1C0 | WGM11 | WGM10 |
             |-------+-------+-------+-------+-------+-------+-------+-------|
    R/W      |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |
    Init Val |   0   |   0   |   0   |   0   |   0   |   0   |  0    |   0   |
              ---------------------------------------------------------------

    TCCR1B - Timer/Counter 1 Control Register B (Pg.156)
              _____________________________________________________________
    Bit      |   7   |   6   |   5   |   4   |   3   |   2  |   1  |   0   |
             |-------+-------+-------+-------+-------+------+------+-------|
    (0x81)   | ICNC1 | ICNC1 |   -   | WGM13 | WGM13 | CS12 | CS11 | CS10  |
             |-------+-------+-------+-------+-------+------+------+-------|
    R/W      |  R/W  |  R/W  |   R   |  R/W  |  R/W  |  R/W |  R/W |  R/W  |
    Init Val |   0   |   0   |   0   |   0   |   0   |   0  |  0   |   0   |
              -------------------------------------------------------------
    Note:
    (TCCR1A) Timer/Counter 1 Control Register A
    TCCR1A only handles the WGM10, WGM11 Bits
    and 
    TCCR1B only handles the WGM12, WGM13 Bits
    *code acordingly*

    Initial Value
    Setting timer 1 in CTC mode 
    (Mode 4 see table 17-2)
    WGMnx bits need to be specified
    Mode | WGM13 | WGM12 | WGM11 | WGM10 |
      4  |   0   |   1   |   0   |   0   | 
    
     TCCR1B-Prescaler = 256 see table 17-6 pg.157) CS1x bits need to be specified
    | CS12 | CS11 | CS10 | Prescaler |
    |   1  |  0   |   0  |    256    | 
    Prescaler of 256 (62 counts is approximately 1 ms)

    Requirements for 1 milisecond (ms)
    TimeDelay (TD) = 1 ms
    Frequency (F) = 16MHz
    Prescaler (PS) = 256
    Fromula: OCR = (TD x F)/PS -1
    OCR = 62
    if we want to pass a value called "delay" then we can set OCR1A = 62 * delay
    and that should allow values in ms to be delayed by the right time up to 1000 ms.   
*/

#include <Arduino.h>
#include "timer.h"

void initTimer1(){

    TCCR1B &= ~(1 << WGM13);    // Set Timer1 CTC mode 0100
    TCCR1B |=  (1 << WGM12);
    TCCR1A &= ~(1 << WGM11);
    TCCR1A &= ~(1 << WGM10);
}

void delay_ms(unsigned int delay){

    TCNT1 = 0;               // Set the Timer/Counter-Register-1 to zero (0)
    OCR1A = 62 * delay;      // Set the Output-Compare-Register-1A to desired delay
    TIFR1 |= (1 << OCR1A);   // Set the flag down in Timer/Counter1 Interrupt Flag Register by writting a logic one
    
    // Turn clock ON
    TCCR1B |=  (1 << CS12);   // Set Prescaler = 256 with CS1# bits 100
    TCCR1B &= ~(1 << CS11);
    TCCR1B &= ~(1 << CS10);
    
    // poll the flag OCF1A bit to see when it is raised
    while (( TIFR1 & ( 1 << OCF1A)) == 0);    // while the flag bit OCF1A is down, do nothing
    
    // turn clock OFF
    TCCR1B  &= ~( (1 << CS10) | (1 << CS11) | ( 1 << CS12) );
}