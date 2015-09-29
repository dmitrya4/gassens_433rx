#include <io.h>
#include <tiny13.h>
#include <tiny13_bits.h>
#include <delay.h>
#include <sleep.h>
#include <string.h>
#include <stdio.h>

#define BitIsClear(reg, bit)    ((reg & (1<<bit)) == 0)
#define SetBit(reg, bit)          reg |= (1<<bit)           
#define ClearBit(reg, bit)       reg &= (~(1<<bit))
#define InvBit(reg, bit)          reg ^= (1<<bit)
#define BitIsSet(reg, bit)       ((reg & (1<<bit)) != 0)

int a,k,j;
char txbit1[8]={1,0,1,1,0,0,1,1};
char txbit2[8]={1,1,1,1,0,0,0,1};
char txbit3[8]={1,0,0,0,1,1,1,1};
char rxdata1[];
char rxdata2[];
char rxdata3[];
unsigned char n = 8;
int result1, result2, result3;
     
       
void main(void){
//Направление работы порта.
    DDRB |= (1<<PORTB4)|(1<<PORTB1)|(1<<PORTB0); 
    
//Выкл. аналог.компаратора    
    ACSR=0x80;
              
	while(1){
     
               //Видимо ждем старт-бита?   
      if(BitIsSet(PINB, 2)){ 
	   // while(BitIsSet(PINB, 2)){
	        delay_us(4800);//1ms
		//}           
        
       //Приём битов
           for(a=0;a<8;a++){
		      if(BitIsSet(PINB, 2)){
			    rxdata1[a] = 1;
			   }
			    else{
				   rxdata1[a] = 0;
				}   
                delay_us(300);//5ms   
		   }           
            result1=memcmp(rxdata1, txbit1, n);                          
            
            for(a=0;a<8;a++){
		      if(BitIsSet(PINB, 2)){
			    rxdata2[a] = 1;
			   }
			    else{
				   rxdata2[a] = 0;
				}   
                delay_us(300);//5ms   
		   }       
             result2=memcmp(rxdata2, txbit2, n); 
             
             for(a=0;a<8;a++){
		      if(BitIsSet(PINB, 2)){
			    rxdata3[a] = 1;
			   }
			    else{
				   rxdata3[a] = 0;
				}   
                delay_us(300);//5ms   
		   }       
             result3=memcmp(rxdata3, txbit3, n);               
            
            if(result1==0 && result2==0 && result3==0){  
                    PORTB |= (1<<PINB1);//Команда на сервер
                    delay_ms(2000);
                    PORTB &= ~(1<<PINB1);//Команда на сервер  
                    PORTB |= (1<<PINB4);//LED ON                  
               for(k=0;k<10;k++){  
                  for(j=0;j<10000;j++){
                    PORTB |= (1<<PINB0); //Пищалка вкл. 
                    delay_us(145);
                    PORTB &= ~(1<<PINB0); //Пищалка выкл. 
                    delay_us(145);
                  }
                } 


           }   

        }
        PORTB &= ~(1<<PINB4);//LED Off
       delay_ms(15);
    
   }
}