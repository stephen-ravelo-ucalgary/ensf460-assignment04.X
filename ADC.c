#include "ADC.h"

uint16_t do_ADC(void) {
    uint16_t ADCvalue ; // 16 bit register used to hold ADC converted digital output ADC1BUF0
    /* ------------- ADC INITIALIZATION ------------------*/
    ..... // Configure ADC by setting bits in AD1CON1 register
    .....
            
    AD1CON2bits.VCFG = 0b000; // Selects AVDD, AVSS (supply voltage to PIC) as Vref
    ..... // Configure ADC by setting bits in AD1CON2
            
    AD1CON3bits.ADRC = 0; // Use system clock
    ..... //Configure the ADC?s sample time by setting bits in AD1CON3
    ..... // Ensure sample time is 1/10th of signal being sampled
            
    ..... // Select and configure ADC input
            
    /* ------------- ADC SAMPLING AND CONVERSION ------------------*/
    AD1CON1bits.ADON = 1; // turn on ADC module
    AD1CON1bits.SAMP=1; //Start Sampling, Conversion starts automatically after SSRC and SAMC settings
    
    while(AD1CON1bits.DONE==0) {}
    ADCvalue = ADC1BUF0; // ADC output is stored in ADC1BUF0 as this point
    AD1CON1bits.SAMP=0; //Stop sampling
    AD1CON1bits.ADON=0; //Turn off ADC, ADC value stored in ADC1BUF0;
    return (ADCvalue); //returns 10 bit ADC output stored in ADC1BIF0 to calling function
}
