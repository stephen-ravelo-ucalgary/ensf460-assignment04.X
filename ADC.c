/*
 * File Name: ADC.c
 * Assignment: Assignment 4
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: November 7, 2025
 */

#include <p24F16KA101.h>

#include "ADC.h"

/*
 * Configures ADC and returns buffer
 */
uint16_t do_ADC(void) {
    uint16_t ADCvalue; // 16 bit register used to hold ADC converted digital output ADC1BUF0
    /* ------------- ADC INITIALIZATION ------------------*/
    // Configure ADC by setting bits in AD1CON1 register
    AD1CON1bits.ADSIDL = 0;
    AD1CON1bits.FORM = 0b00;
    AD1CON1bits.SSRC = 0b111;
    AD1CON1bits.ASAM = 0;
            
    AD1CON2bits.VCFG = 0b000; // Selects AVDD, AVSS (supply voltage to PIC) as Vref
    // Configure ADC by setting bits in AD1CON2
    AD1CON2bits.CSCNA = 0;        
//    AD1CON2bits.SMPI = 0b000;        
    AD1CON2bits.BUFM = 0;        
    AD1CON2bits.ALTS = 0;        
            
    AD1CON3bits.ADRC = 0; // Use system clock
    //Configure the ADC?s sample time by setting bits in AD1CON3
    // Ensure sample time is 1/10th of signal being sampled
    AD1CON3bits.SAMC = 0b11111;       
    // Select and configure ADC input
    AD1CHSbits.CH0NA = 0;
    AD1CHSbits.CH0SA = 0b1100;
    AD1PCFGbits.PCFG12 = 0;
    AD1CSSLbits.CSSL12 = 0;
            
    /* ------------- ADC SAMPLING AND CONVERSION ------------------*/
    AD1CON1bits.ADON = 1; // turn on ADC module
    AD1CON1bits.SAMP=1; //Start Sampling, Conversion starts automatically after SSRC and SAMC settings
    
    while(AD1CON1bits.DONE==0) {}
    ADCvalue = ADC1BUF0; // ADC output is stored in ADC1BUF0 as this point
    AD1CON1bits.SAMP=0; //Stop sampling
    AD1CON1bits.ADON=0; //Turn off ADC, ADC value stored in ADC1BUF0;
    return (ADCvalue); //returns 10 bit ADC output stored in ADC1BIF0 to calling function
}

/*
 * Samples ADC buffer values for approximately 10 seconds.
 * Uses START_READING and STOP_READING messages to trigger sampling in
 * python program.
 * REQUIRES: samples < 100
 */
void read_ADC(uint16_t samples) {
    uint16_t delay_time = 10000/samples - samples;
    Disp2String("START_READING\n");
    for (int i = 0; i < samples; i++) {
        Disp2Dec(do_ADC());
        delay_ms(delay_time);
    }
    Disp2String("STOP_READING\n");
}