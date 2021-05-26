//--> librerias
#include <msp430G2553.h>
//--> estados
#define ESTADO_A 0;
#define ESTADO_B 1;
//--> eventos
#define EV1 BIT0
#define SET(ev)(eventos |= (ev))
#define RESET(ev)(eventos &= ~(ev))
#define TEST(ev)(eventos &= (ev))

int main(void)
{
    unsigned char estado;
    WDTCTL=WDTPW | WDTHOLD;

/*--> "SMCLK" 1MHz calibrado
    DCOCTL=0;
    BCSTL1=CALBC1_1MHz;
    DCOTL=CALDC0_1MHz; */

//--> pulsador P1.3
    P1DIR &= ~(BIT3);
    P1REN |= (BIT3);
    P1OUT |= (BIT3);
    P1IES |= (BIT3);

//--> led 1 | led 2
    P1DIR |= (BIT6+BIT0);
    P1OUT &= ~(BIT6+BIT0);

//--> evento | estado
    estado=ESTADO_A;
    // error  eventos=0;

//--> comienzo while
    while(1){
        __low_power_mode_0();
        while(eventos){
            switch(estado){
            case(ESTADO_A):
    {
                break;
    } // fin estado A
            case(ESTADO_B):
    {
                break;
    }// fin estado B

            }// switch
        }//while /eventos
    }//while 1




}//--> fin main

#pragma vector=POR1_VECTOR
__interrupt void RTI_P1(void)
{
    if((P1IE & P1IFG & BIT3) !=0){
        //--> antirrebotes 32ms
        P1IFG &= ~(BIT3);
        P1IE &= ~(BIT3);
        WDTCTL=WDT_MDLY_32;
        IFG1 &= ~ (WDTIFG);
        IE1 |= WDTIE;

        //--> "flanco bajada"
        if((P1IES & BIT3) != 0){

        }// x] if ((P1IES & BIT3) != 0)
        else { // flanco subida
             } // else: if ((P1IES & BIT3) != 0)
        P1IES ^=(BIT3);
    } // if((P1IE & P1IFG & BIT3) !=0)

    if(eventos){
        __low_power_mode_of_on_exit();
    }// if (eventos)
}



