/*
 * File Name: timer.h
 * Assignment: Assignment 4
 * Lab Section: B02
 * Completed by: Stephen Ravelo, Aaron Lauang, Alexa Gonzalez
 * Submission Date: November 7, 2025
 */

#ifndef TIMER_H
#define	TIMER_H

#include <xc.h>
#include "IOs.h"

extern uint16_t _skip_delay;

void timerInit();
void delay_ms();

#endif	/* TIMER_H */

