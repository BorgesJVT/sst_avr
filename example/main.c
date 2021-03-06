/*****************************************************************************
* Product: SST example, 80x86, Turbo C++ 1.01
*
* Copyright (C) 2006 Miro Samek and Robert Ward. All rights reserved.
*
* This software may be distributed and modified under the terms of the GNU
* General Public License version 2 (GPL) as published by the Free Software
* Foundation and appearing in the file GPL.TXT included in the packaging of
* this file. Please note that GPL Section 2[b] requires that all works based
* on this software must also be made publicly available under the terms of
* the GPL ("Copyleft").
*
* Contact information:
* Email:    miro@quantum-leaps.com
* Internet: www.quantum-leaps.com
*****************************************************************************/
#include "sst_port.h"
#include "sst_exa.h"

//#include "bsp.h"

// #include <stdlib.h>                                           /* for atol() */

//static void setupScreen(void);
static SSTEvent tickTaskAQueue[2];
static SSTEvent tickTaskBQueue[2];
// static SSTEvent kbdTaskQueue[2];

// static uint32_t l_delayCtr = 0UL;

// ********************************************************************************
// Interrupt Routines
// ********************************************************************************
// http://www.atmel.com/Images/Atmel-2505-Setup-and-Use-of-AVR-Timers_ApplicationNote_AVR130.pdf

// timer0 overflow
ISR(TIMER0_OVF_vect) {
    /* Toggle a pin on timer overflow */
    // PORTB ^= (1 << PORTB5);
    uint8_t pin;
    SST_ISR_ENTRY(pin, TICK_ISR_PRIO);
    SST_post(TICK_TASK_A_PRIO, TICK_SIG, 0);     /* post the Tick to Task A */
    SST_ISR_EXIT(pin,pin);
}


// static void interrupt timerISR() {  
//     SST_ISR_ENTRY(pin, TICK_ISR_PRIO);

//     SST_post(TICK_TASK_A_PRIO, TICK_SIG, 0);      post the Tick to Task A 
//     // SST_post(TICK_TASK_B_PRIO, TICK_SIG, 0);     /* post the Tick to Task B */

//      SST_INT_LOCK();
// }

/*..........................................................................*/
int main(int argc, char *argv[]) {
   
    /* Timer clock = I/O clock / 1024 */
     TCCR0B = (1<<CS02)|(1<<CS00);
     /* Clear overflow flag */
     TIFR0 = 1<<TOV0;
     /* Enable Overflow Interrupt */
     TIMSK0 = 1<<TOIE0;

    /* set pin 5 of PORTB for output*/
    DDRB |= _BV(DDB5);

    // SST_init();                                       /* initialize the SST */

    SST_task(&tickTaskA, TICK_TASK_A_PRIO,
            tickTaskAQueue, sizeof(tickTaskAQueue)/sizeof(tickTaskAQueue[0]),
            INIT_SIG, 0);

    // SST_task(&tickTaskB, TICK_TASK_B_PRIO,
    //         tickTaskBQueue, sizeof(tickTaskBQueue)/sizeof(tickTaskBQueue[0]),
    //         INIT_SIG, 0);

    // SST_task(&kbdTask, KBD_TASK_PRIO,
    //          kbdTaskQueue, sizeof(kbdTaskQueue)/sizeof(kbdTaskQueue[0]),
    //          INIT_SIG, 0);

    SST_run();                                   /* run the SST application */
    return 0;
}

void SST_onIdle(){

}
