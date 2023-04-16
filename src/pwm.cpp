/*
Team Members: Aaron Colin Del Angel, Tyler Wilson, Jasiah Jospeh
Date:03/20/2023
Assignment:  Lab 5 


Description: This file implements the initialization of pwm on pin
----------------------------------------------------------------------//
*/

/*

TCCR3A - Timer/Counter 3 Control Register A (Pg.154)
              _______________________________________________________________
    Bit      |   7   |   6   |   5   |   4   |   3   |   2   |   1   |   0   |
             |-------+-------+-------+-------+-------+-------+-------+-------|
    (0x90)   |COM3A1 |COM3A0 |COM3B1 |COM3B0 |COM3C1 |COM3C0 | WGM31 | WGM30 |
             |-------+-------+-------+-------+-------+-------+-------+-------|
    R/W      |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |  R/W  |
    Init Val |   0   |   0   |   0   |   0   |   0   |   0   |  0    |   0   |
              ---------------------------------------------------------------

TCCR3B - Timer/Counter 3 Control Register B (Pg.156)
              _____________________________________________________________
    Bit      |   7   |   6   |   5   |   4   |   3   |   2  |   1  |   0   |
             |-------+-------+-------+-------+-------+------+------+-------|
    (0x91)   | ICNC3 | ICNC3 |   -   | WGM33 | WGM32 | CS32 | CS31 | CS30  |
             |-------+-------+-------+-------+-------+------+------+-------|
    R/W      |  R/W  |  R/W  |   R   |  R/W  |  R/W  |  R/W |  R/W |  R/W  |
    Init Val |   0   |   0   |   0   |   0   |   0   |   0  |  0   |   0   |
              -------------------------------------------------------------
    Note:
    (TCCR3A) Timer/Counter 1 Control Register A
    TCCR3A only handles the WGM30, WGM31 Bits
    and 
    TCCR3B only handles the WGM32, WGM33 Bits
    *code acordingly*

    Table 17-2 Waveform Generation Mode Bit Description (Pg. 145)
    Setting timer3 in "Fast PWM" mode 15 
     ____________________________________________________________________________________
    | Mode # | WGM#3 | WGM#2 | WGM#2 | WGM#0 |   Mode   |   TOP  | Update at | TOV# flag |
    |--------+-------+-------+-------+-------+----------+--------+-----------+-----------|
    |   15   |   1   |   1   |   1   |   1    | Fast PWM | OCRnA |  BOTTOM   |    TOP    |
    |------------------------------------------------------------------------------------|
    
     TCCR3B-Prescaler = 1 see table 17-6 pg.157) 
     ________________________________
    | CS32 | CS31 | CS30 | Prescaler |
    |   0  |  0   |   1  |     1     | 
    ---------------------------------

    OCR3B = f(CPU) / ( f(PWM) x PS ) - 1 
    OCR3B = 16MHz / (100 Hz x 8) -1 = 19,999

    PWM output pin = PIN #2 => PE4 => OC3B 
    
*/

#include "pwm.h"
#include <avr/io.h>
#include "timer.h"

void initPWM() {

    // Set Data Direction on PE4 as output (Duty cycle pin)
    DDRE |= (1 << DDB4);

    // Set WGM bits (1111) for "Fast PWM" mode 15  
    TCCR3B |= (1 << WGM33); 
    TCCR3B |= (1 << WGM32);    
    TCCR3A |= (1 << WGM31); 
    TCCR3A |= (1 << WGM30);

    // set COM Bits (10) to non-inverting mode - output  
    // starts high and then is low, 
    TCCR3A |= (1 << COM3B1);   
    TCCR3A &= ~(1 << COM3B0);

    // set prescalar CSBits 010 Prescaler = 8
    TCCR3B &= ~(1 << CS32);
    TCCR3B |=  (1 << CS31);
    TCCR3B &= ~(1 << CS30);

    // Set frequency using OCR3A
    //OCR3A =  19999;

    // Set Duty Cycle 50%
    // OCR3B = TOP x 0.5 = 19999 x 0.5 = 999
    
    //OCR3B = 999;
}


void alarmON(){

    for (int i=4999; i>3333; i--){
      OCR3A =  i;
      delay_ms(1);
    } 
    
}

void alarmOFF(){
    OCR3A = 0;
}

