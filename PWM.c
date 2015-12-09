#include"PWM.h"

#define T 1566
void initPWM(void)
{
    P2DIR|= 0xff; // Salida
    P2SEL|= 0xff; // Función PWM del Timer_A1


    TA1CCR0  = T;                  // Periodos = 16.6us (60Khz)->261
    TA1CCR1  = T*0;                // D -> P2.1,P2.2
    TA1CCR2  = T*0.5 ;             // D -> P2.4,P2.5
    TA1CCTL1 = OUTMOD_7;           // Modo7 reset/set                          (TACCTLx)
    TA1CCTL2 = OUTMOD_7;           // Modo7 reset/set
    TA1CTL   = TASSEL_2 + MC_1;    // Timer SMCLK Modo UP                      (TACTL)
}

void PWM(float D1,float D2)
{
    if (D1>D2)
    { D2=0; }
    if (D2>D1)
    { D1=0; }
    TA1CCR1  =(D1*T);    // D -> P2.1,P2.2
    TA1CCR2  =(D2*T);    // D -> P2.4,P2.5
}
