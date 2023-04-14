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
    Setting timer3 in "Fast PWM" mode 14 
     _________________________________________________________________________________
    | Mode # | WGM#3 | WGM#2 | WGM#2 | WGM#0 |   Mode   |  TOP | Update at | TOV# flag |
    |--------+-------+-------+-------+-------+----------+------+-----------+-----------|
    |   14   |   1   |   1   |   1   |   0   | Fast PWM | ICR# |  BOTTOM   |    TOP    |
    |----------------------------------------------------------------------------------|
    
     TCCR3B-Prescaler = 8 see table 17-6 pg.157) 
     ________________________________
    | CS32 | CS31 | CS30 | Prescaler |
    |   0  |  1   |   0  |     8     | 
    ---------------------------------

    PWM frequency calculation for FAST PWM mode (Pg. 148)
    frequency of PWM = (F_clk)/((Prescaler)* (1 +TOP))
    frequency of PWM = 16Mhz
    Prescaler = 256
    TOP value = ICRN = 999
    PWM frequency from calculation = 1 kHz

    PIN #5 => PE3 => OC3A (includes timer 3A)
*/

#include "pwm.h"
#include <avr/io.h>

void initPWM() {

    // Set Data Direction register E on PE3 as output
    DDRE |= (1 << 3);

    // Set WGM## bits for "Fast PWM" 
    TCCR3A &= ~(1 << WGM30);
    TCCR3A |= (1 << WGM31); 
    TCCR3B |= (1 << WGM32);
    TCCR3B |= (1 << WGM33); 

    // set non-inverting mode - output starts high and then is low, 
    TCCR3A |= (1 << COM3A1);   
    TCCR3A &= ~(1 << COM3A0); 

    // set prescalar CSBits
    TCCR3B &= ~(1 << CS32);
    TCCR3B |=  (1 << CS31);
    TCCR3B &= ~(1 << CS30);

    // set Input Capture Register3 to 999
    ICR3 = 999;   

    // Set Duty Cycle
    OCR3A =  500;
}

void buzzer_ON(){

    
}
