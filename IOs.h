/*
 * File Name: IOs.h
 * Assignment: Project 1
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: October 26, 2025
 */

#ifndef IOS_H
#define	IOS_H

#include <xc.h>
#include "clkChange.h"
#include "UART2.h"
#include "timer.h"

typedef enum {
    STATE_MODE_0,
    STATE_MODE_1,     
    STATE_READ_ADC        
} state_t;

extern state_t _state;

void IOinit();
uint16_t IOcheck();

#endif
