#include "scDIFUSO.h"
#include "PWM.h"


#define POCO    0.2
#define REGULAR 0.7
#define MUCHO   1

float d1=0;
float d2=0;

void SCDifuso(float R,float E)
{

    float u=0;
    float numN=0; // u(kn)*kn
    float numP=0; // u(kn)*kn
    float denN=0; // u(kn)
    float denP=0; // u(kn)

    /* Salidas (PWM__N y PWM__P) */

    //   Mucho   = 100%
    //   Regular =  70%
    //   Poco    =  40%
    //   Nada    =  10%

    /*    Referencia (R)    */

    // Bajo  ->    0<= R <=150
    // Medio ->   75<= R <=225
    // Alto  ->  150<= R <=275

    /*      Error (E)       */
    // MuchoN   ->  -275<= E <= -150
    // RegularN ->  -250<= E <=  -50
    // PocoN    ->  -150<= E <     0
    // Cero     ->       E = 0
    // PocoP    ->     0<  E <=  150
    // Regularn ->    50<= E <=  250
    // MuchoP   ->   150<= E <=  275

            /*_____Reglas_____*/

    // 1. R(Bajo) & E(MedioN)->PWM__N(Regular)
    if(R<=150 && ( E >= -250 && E <= -50 ))
    {
        if(E>=-250 && E<=-150 )
        {u=min(-0.0066*R+1,0.01*E+2.5);}
        if(E>=-150 && E<=-50)
        {u=min(-0.0066*R+1,-0.01*E-0.5);}

        numN+=u*REGULAR;
        denN+=u;
    }

    // 2. R(Bajo) & E(MuchoN)->PWM__N(Mucho)
    if(R<=150 && ( E<=-150 ))
    {
        if(E<=-225)
        {u=min(-0.0066*R+1,1.0);}
        if(E>=-225 && E<=-150)
        {u=min(-0.0066*R+1,-0.0133*E-2);}

        numN+=u*MUCHO;
        denN+=u;
    }

    // 3. R(Bajo) & E(PocoN)->PWM__N(Poco)
    if(R<=150 && ( E>=-150 && E < 0 ))
    {
        if((-150<=E) && (E<=-75))
        {
            u=min(-0.0066*R+1,0.0133*E+2);
        }
        if(-75<=E && E < 0)
        {u=min(-0.0066*R+1,-0.0133*E);}

        numN+=u*POCO;
        denN+=u;
    }

    // 4. R(Bajo) & E(PocoP)->PWM__P(Poco)
    if(R<=150 && ( E>=0 && E<=150 ))
    {
        if( E>0 && 75>=E)
        {u=min(-0.0066*R+1,0.0133*E);}
        if( 75<E && E<=150)
        {u=min(-0.0066*R+1,-0.0133*E+2);}

        numP+=u*POCO;
        denP+=u;
    }

    // 5. R(Medio) & E(MedioP)->PWM__P(Regular)
    if((75<=R && R<=225) && ( 50<=E && E<=250))
    {
        if((75<=R && R<=150) && (50<=E && E<=150))
        {u=min(0.0133*R-1,0.01*E-0.5);}
        if((75<=R && R<=150) && (150<=E && E<=250))
        {u=min(0.0133*R-1,-0.01*E+2.5);}
        if((150<=R && R<=225) && (50<=E && E<=150))
        {u=min(-0.0133*R+3,0.01*E-0.5);}
        if((150<=R && R<=225 )&& (150<=E && E<=250))
        {u=min(-0.0133*R+3,-0.01*E+2.5);}

        numP+=u*REGULAR;
        denP+=u;
    }

    // 6. R(Medio) & E(MedioN)->PWM__N(Regular)
    if((75<=R && R<=225) && (-250<=E && E<=-50))
    {
        if((75<=R && R<=150) && (-250<=E && E<=-150))
        {u=min(0.0133*R-1,0.01*E+2.5);}
        if((75<=R && R<=150) && (-150<=E && E<=-50))
        {u=min(0.0133*R-1,-0.01*E-0.5);}
        if((150<=R && R<=225) && (-250<=E && E<=-150))
        {u=min(-0.0133*R+3,0.01*E+2.5);}
        if((150<=R && R<=225 )&& (-150<=E && E<=-50))
        {u=min(-0.0133*R+3,-0.01*E-0.5);}

        numN+=u*REGULAR;
        denN+=u;
    }

    // 7. R(Medio) & E(PocoN)->PWM__N(Poco)
    if((75<=R && R<=225) && (-150<=E && E<0))
    {
        if((75<=R && R<=150) && (-150<=E && E<=-75))
        {u=min(0.0133*R-1,0.01333*E+2);}
        if((75<=R && R<=150) && (-75<=E && E<0))
        {u=min(0.0133*R-1,-0.0133*E);}
        if((150<=R && R<=225) && (-150<=E && E<=-75))
        {u=min(-0.0133*R+3,0.0133*E+2);}
        if((150<=R && R<=225 )&& (-75<=E && E<0))
        {u=min(-0.0133*R+3,-0.0133*E);}

        numN+=u*POCO;
        denN+=u;
    }

    // 8. R(Medio) & E(PocoP)->PWM__P(Poco)
    if((75<=R && R<=225) && (0<E && E<=150))
    {
        if((75<=R && R<=150) && (0<E && E<=75))
        {u=min(0.0133*R-1,0.0133*E);}
        if((75<=R && R<=150) && (75<=E && E<150))
        {u=min(0.0133*R-1,-0.0133*E+2);}
        if((150<=R && R<=225) && (0<E && E<=75))
        {u=min(-0.0133*R+3,0.0133*E);}
        if((150<=R && R<=225 )&& (75<=E && E<=150))
        {u=min(-0.0133*R+3,-0.0133*E+2);}

        numP+=u*POCO;
        denP+=u;
    }

    // 9. R(Alto) & E(MedioP)->PWM__P(Regular)
    if((150<=R) && (50<=E && E<=250))
    {
        if(50<=E && E<=150)
        {u=min(0.0066*R-1,0.01*E-0.5);}
        if(150<=E && E<=250)
        {u=min(0.0066*R-1,-0.01*E+2.5);}

        numP+=u*REGULAR;
        denP+=u;
    }

    // 10. R(Alto) & E(PocoN)->PWM__N(Poco)
    if((150<=R) && (-150<=E && E<0))
    {
        if(-150<=E && E<=-75)
        {u=min(0.0066*R-1,0.0133*E+2);}
        if(-75<=E && E<0)
        {u=min(0.0066*R-1,-0.0133*E);}

        numN+=u*POCO;
        denN+=u;
    }

    // 11. R(Alto) & E(PocoP)->PWM__P(Poco)
    if((150<=R) && (0<E && E<=150))
    {
        if(0<E && E<=75)
        {u=min(0.0066*R-1,0.0133*E);}
        if(75<=E && E<=150)
        {u=min(0.0066*R-1,-0.0133*E+2);}

        numP+=u*POCO;
        denP+=u;
    }

    // 12. R(Alto) & E(MuchoP)->PWM__P(Mucho)
    if((150<=R) && (150<E))
    {
        if(150<E && E<=225)
        {u=min(0.0066*R-1,0.0133-2);}
        if(E<=225)
        {u=min(0.0066*R-1,1);}

        numP+=u*MUCHO;
        denP+=u;
    }

    d1=numN/denN;
    d2=numP/denP;

    // 13. E(Cero) -> PWM__P(Nada) && PWM__N(Nada)
    if(-5<=E && E<=5)
    {
        d1=0;
        d2=0;
    }

    PWM(d1,d2);
}

float min(float x, float y)
{
    if(x<=0 || x<=0.001){x=0;}
    if(y<=0 || y<=0.001){y=0;}

    if(x>0.98){x=1;}
    if(y>0.98){y=1;}

    if(x>=y){return(y);}
    else{return(x);}
}
