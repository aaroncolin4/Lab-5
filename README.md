Team Members: Aaron Colin Del Angel, Tyler Wilson, Jasiah Jospeh
Date:03/20/2023
Assignment:  Lab 5 

You will need to create a circuit using a breadboard, jumper wires,
accelerometer, 8x8 led matrix, piezo speaker and a push button switch.

  - Arduino libraries for Serial.println can be used for printing
    x,y, and z accelerometer data and also debugging. 
  - You will need to build your own timer function for delays when needed.
  - Read the MPU 6050 accelerometer datasheets. You will use the WHO_AM_I
    register (pg. 46 of register map) as the SLA. 
  - The register that you will be reading from are the ACCEL_nOUT registers
    (pg. 30 of register map). There are two 8-bit registers for X, Y, and Z.
    These registers will need to be read and combined to gather the necessary 
    information.
  - Obtain the power management register information (pg. 41 of register map).
 
Before developing your threshold values, you should verify that data changes 
in all orthogonal x,y and z directions.

You will need to determine your accelerometer threshold tilt value
(approximately 45degrees from rest position) based on actual readings
that you obtain.
Read the 8x8 LED Matrix display datasheet (MAX7221 on how to interface
the LED matrix using SPI protocol.
Use the passive piezo buzzer device. The alarm sound should be a chirping sound.
