#include <reg51.h>
#include <absacc.h>
#include <math.h>
#include "LCD_lib.c"
/*
klikniecie:
65536 -921600/100
*/
#define ENTER 0x01
#define ESC 0x02
#define T0L_RELOAD 0x00
#define T0H_RELOAD 0xDC
#define T1L_RELOAD 0xFE
#define T1H_RELOAD 0xFF
#define TM 0x03 // tekst na morse'a
#define MT 0x04 //morse na tekst

sbit key=P3^5;          //podswietlenie przy wlaczeniu
sbit display=P1^6;
sbit P1_7=P1^7;


int klikniecie;
float dlugosc_wcisniecia=0,dlugosc_przerwy=0;
char litera[4],litera_lcd,napis[]= "S O S SOS";
 char znak=-1,i=0,j=0,h=0,k,z,wybor=0,lycznyk=0,potega;

void timerISR_T0(void) interrupt 1   //Funkcja reaalizujaca przerwanie.
{
    TL0=T0L_RELOAD;
    TH0=T0H_RELOAD;
    klikniecie++;
}
void delay(int czas)

{
	klikniecie=0;
	while(klikniecie<czas);
}

void inicjalizacja()
{
     TMOD = TMOD | 0x01;
    TR0 = 1;
    ET0 = 1;
    TL0 = T0L_RELOAD;
    TH0 = T0H_RELOAD;
    EA = 1;
	lcd_init();
}

float odczyt_czasu()
{
    float time =0;
		ET0=0;   //zatrzymaj timer
    time=klikniecie;
    ET0=1;   //zalacz timer
		
    return time/100;
}

void wypisz()
{
potega=0;
				for(j=3;j>=0;j--)
					{
						litera_lcd=litera_lcd+litera[j]*(pow(3,potega));
						potega++;
					}
					
				switch(litera_lcd)
				{
					case 45:
						lcd('A');
						break;
					
					case 67:
						lcd('B');
						break;
					
					case 70:
						lcd('C');
					
						break;
					
					case 66:
						lcd('D');
						break;
					
					case 27:
						lcd('E');
						break;
					
					case 43:
						lcd('F');
						break;
					
					case 75:
						lcd('G');
						break;
					
					case 40:
						lcd('H');
						break;
					
					case 36:
						lcd('I');
						break;
					
					case 53:
						lcd('J');
						break;
					
					case 69:
						lcd('K');
						break;
					
					case 49:
						lcd('L');
						break;
					
					case 72:
						lcd('M');
						break;
					
					case 63:
						lcd('N');
						break;
					
					case 78:
						lcd('O');
						break;
					
					case 52:
						lcd('P');
						break;
					
					case 77:
						lcd('Q');
						break;
					
					case 48:
						lcd('R');
						break;
					
					case 39:
						lcd('S');
						break;
					
					case 54:
						lcd('T');
						break;
					
					case 42:
						lcd('U');
						break;
					
					case 41:
						lcd('V');
						break;
					
					case 51:
						lcd('W');
						break;
					
					case 68:
						lcd('X');
						break;
					
					case 71:
						lcd('Y');
						break;
					
					case 76:
						lcd('Z');
						break;
					
				}
				for(k=0;k<4;k++)
			litera[k]=0;
			h=0;
			i=0;
			litera_lcd=0;
}




int main()
{
    inicjalizacja();
    
			while(!wybor)
			{
				XBYTE[0xF030]=TM; // tekst na morse'a
        if(key)
				{wybor=1;
					break;}
				XBYTE[0xF030]=MT; //morse na tekst
        if(key)
				{wybor=2;
					break;}	
			}
			
				if(wybor==1)
				{
					while(1){

	int h=0,lycznyk=0;
while(napis[h])
{
				switch(napis[h])
				{
					case 'A':
						lycznyk=45;
						break;
					
					case 'B':
						lycznyk=67;
						break;
					
					case 'C':
						lycznyk=70;
					
						break;
					
					case 'D':
						lycznyk=66;
						break;
					
					case 'E':
						lycznyk=27;
						break;
					
					case 'F':
						lycznyk=43;
						break;
					
					case 'G':
						lycznyk=75;
						break;
					
					case 'H':
						lycznyk=40;
						break;
					
					case 'I':
						lycznyk=36;
						break;
					
					case 'J':
						lycznyk=53;
						break;
					
					case 'K':
						lycznyk=69;
						break;
					
					case 'L':
						lycznyk=49;
						break;
					
					case 'M':
						lycznyk=72;
						break;
					
					case 'N':
						lycznyk=63;
						break;
					
					case 'O':
						lycznyk=78;
						break;
					
					case 'P':
						lycznyk=52;
						break;
					
					case 'Q':
						lycznyk=77;
						break;
					
					case 'R':
						lycznyk=48;
						break;
					
					case 'S':
						lycznyk=39;
						break;
					
					case 'T':
						lycznyk=54;
						break;
					
					case 'U':
						lycznyk=42;
						break;
					
					case 'V':
						lycznyk=41;
						break;
					
					case 'W':
						lycznyk=51;
						break;
					
					case 'X':
						lycznyk=68;
						break;
					
					case 'Y':
						lycznyk=71;
						break;
					
					case 'Z':
						lycznyk=76;
						break;
					case ' ':
						lycznyk=0;
						delay(280);
					break;
					
				
			}
			
z=3;
			
for(i=0;i<4;i++)
			{
				litera[z]=lycznyk%3;
				lycznyk=lycznyk/3;
				z--;
			
			}
			for(i=0;i<4;i++)
			{
			if(litera[i]==1)
			{
				P1_7=0;
				delay(40);
				P1_7=1;}
			else if(litera[i]==2)
			{P1_7=0;
				delay(120);
				P1_7=1;}
delay(40);}
			
				
			delay(120);
h++;			
}
			
									//tekst na morse'a
				}}				
			else if(wybor==2)
				{
					while(1)
					{
					for(k=0;k<4;k++)
			litera[k]=0;
			h=0;
			i=0;
			litera_lcd=0;
			
				do{
					
					
        XBYTE[0xF030]=ENTER;   // Zalaczenie timer'a przy wcisnieciu klawisza enter.
        if(key)
				{
					if(h!=0)
					dlugosc_przerwy=odczyt_czasu();
					
					if(dlugosc_przerwy>=0.2 && dlugosc_przerwy<0.6) // odstep pomiedzy znakami
				{ i++;
					}
					
					if(dlugosc_przerwy>=0.6 && dlugosc_przerwy<3) // odstep pomiedzy znakami
				{wypisz();
					}
				if(dlugosc_przerwy>3) // odstep pomiedzy grupa znakow
				{wypisz();
					lcd('_');
					}
				
					klikniecie=0;
					do{
					while(key)
					
					{P1_7 = 0;}
					
					P1_7 = 1;
					dlugosc_wcisniecia=odczyt_czasu();}
					while(dlugosc_wcisniecia<0.1);
					
					if(dlugosc_wcisniecia>0.1 && dlugosc_wcisniecia<0.6)
				{
					litera[i]=1;//kropka
					display=1;
								XBYTE[0xF030]=0x01;   // Wybór pierwszego wskaznika.
								XBYTE[0xF038]=128;  //Zalaczanie odpowiednich segmentów danego wskaznika.
								display=0;    // Wlaczenie wywietlacza.
							
				}
				
				if(dlugosc_wcisniecia>=0.6)
				{
					litera[i]=2;//kreska
					display=1;
					XBYTE[0xF030]=0x01;   // Wybór pierwszego wskaznika.
								XBYTE[0xF038]=64;  //Zalaczanie odpowiednich segmentów danego wskaznika.
								display=0;    // Wlaczenie wywietlacza.
								
				}
				
					
					
				h=1;
				//i++;
				klikniecie=0;
				}
    }while(i<4);
	

				wypisz();
		
				
	}}
			}
			
		
				
		
	
	


