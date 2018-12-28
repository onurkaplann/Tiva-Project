#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "inc/tm4c123gh6pm.h"
#include "LCD1602.h"
#include "SYSTICK.h"
#include "PLL_80MHZ.h"

void PLL_Init80MHZ(void);

unsigned char msg1[] ="Girilen:";
unsigned char *msg[] = {msg1};

unsigned char nokta[] =".";
unsigned char *nn[] = {nokta};
void init_port_E() {
	   volatile unsigned long tmp;
	   tmp = SYSCTL_RCGCGPIO_R;
	   SYSCTL_RCGC2_R |= 0x10;
	   GPIO_PORTE_LOCK_R = 0x4C4F434B;
	   GPIO_PORTE_DIR_R = 0xC0;
	   GPIO_PORTE_PUR_R = 0x3F;
	   GPIO_PORTE_DEN_R = 0x3F;
	}
int duzenle(int hane){
	hane = hane+1;
	hane = hane%10;
	return hane;
}
void bozdur( int *dizi,double *banknotlar,double para){
    banknotlar[0]=20.000;
    banknotlar[1]=10.000;
    banknotlar[2]=5.000;
    banknotlar[3]=1.000;
    banknotlar[4]=0.500;
    banknotlar[5]=0.2500;
    banknotlar[6]=0.1000;
    banknotlar[7]=0.0500;
    banknotlar[8]=0.0100;

int i;

    for(i=0;i<9;i++){
        while( para>=banknotlar[i]){
            para -= banknotlar[i];
            dizi[i]++;
        }
    }
}
int main(void){

	    PLL_Init80MHZ();
	    SysTick_Init();
	    LCD1602_Init();
  	init_port_E();
  	double *banknotlar;
  		int dizi[9];
  		int i;
  		double para;

  			    for(i=0;i<9;i++){
  			        dizi[i]=0;
  			    }
  	int button1 ,button2, button3, button4, button5, button6;
  	int birler=0,onlar=0,ondabir=0,yuzdebir=0;
  	while(1){

  		button6 = GPIO_PORTE_DATA_R & 0b0100000;
  		button5 = GPIO_PORTE_DATA_R & 0b0010000;
  		button4 = GPIO_PORTE_DATA_R & 0b0001000;
  		button3 = GPIO_PORTE_DATA_R & 0b0000100;
  		button2 = GPIO_PORTE_DATA_R & 0b0000010;
  		button1 = GPIO_PORTE_DATA_R & 0b0000001;

  		LCD1602_DisplayPosition(LINE1,0);
  		LCD1602_DisplayString("Alinan:");

  			LCD1602_DisplayPosition(LINE1,10);
  			LCD1602_DisplayDec(yuzdebir);
  			LCD1602_DisplayDec(ondabir);
  			LCD1602_DisplayString(nn[0]);
  			LCD1602_DisplayDec(birler);
  			LCD1602_DisplayDec(onlar);


  		if(button1==0){
  			yuzdebir = duzenle(yuzdebir);
  			LCD1602_DisplayPosition(LINE2,0);
  			LCD1602_DisplayString("bir");
  			 SysTick_Delay1ms(1000);
  			 LCD1602_Clear();
  		}
  		else if(button2==0){

  			ondabir = duzenle(ondabir);
  			LCD1602_DisplayPosition(LINE2,0);
  			LCD1602_DisplayString("iki");
  			SysTick_Delay1ms(1000);
  			  			  LCD1602_Clear();

  		}
  		else if(button3 == 0){
  			birler = duzenle(birler);
  			LCD1602_DisplayPosition(LINE2,0);
  			LCD1602_DisplayString("uc");
  			SysTick_Delay1ms(1000);
  			  			  LCD1602_Clear();
  		}
  		else if(button4 == 0){
  			onlar = duzenle(onlar);
  			LCD1602_DisplayPosition(LINE2,0);
  			LCD1602_DisplayString("dort");
  			SysTick_Delay1ms(1000);
  			  			  LCD1602_Clear();
  		}
  		else if(button5 == 0){//RESET
  			birler=0;
  			onlar=0;
  			ondabir=0;
  			yuzdebir=0;
  			LCD1602_DisplayPosition(LINE2,0);
  			LCD1602_DisplayString("bes");
  			SysTick_Delay1ms(1000);
  			  			  LCD1602_Clear();
  		}else if(button6 == 0){
  			para = onlar*10 + birler + ondabir/10 + yuzdebir/100;
  			bozdur(dizi,banknotlar,para);
  			LCD1602_DisplayPosition(LINE2,7);
  			LCD1602_DisplayString("HESAPLA");
  			for(i=0;i<9;i++){
  				if(dizi[i] != 0){
  					LCD1602_DisplayPosition(LINE2,7);
  					LCD1602_DisplayDec(dizi[i]);
  					LCD1602_DisplayPosition(LINE2,8);
  					LCD1602_DisplayString("X");
  					LCD1602_DisplayPosition(LINE2,9);
  					LCD1602_DisplayDec(banknotlar[i]);
  				    SysTick_Delay1ms(1000);
  				    SysTick_Delay1ms(1000);
  				}
  			}
  			birler=0;
  			onlar=0;
  			ondabir=0;
  			yuzdebir=0;
  			LCD1602_Clear();
  		}

  	}

}
