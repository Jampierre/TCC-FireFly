//Progama : Comandos AT no GSM Shield
//Alteracoes e adaptacoes : FILIPEFLOP

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"

int numdata;
char inSerial[40];
int i=0;

void setup()
{
     //Inicializa a serial
     Serial.begin(9600);
     Serial.println("Testando GSM Shield...");
     //Inicia a configuracao do Shield
     if (gsm.begin(9600))
          Serial.println("nstatus=Pronto, digite os comandos AT");
     else Serial.println("nstatus=IDLE");
}

void loop()
{
   //Le um novo byte na serial por hardware, e
   //o escreve na NewSoftSerial
   serialhwread();
   //Le um novo byte na NewSoftSerial
   serialswread();
}

void serialhwread()
{
     i=0;
     if (Serial.available() > 0) 
     {
       while (Serial.available() > 0) 
       {
         inSerial[i]=(Serial.read());
         delay(10);
         i++;
       }
       
       inSerial[i]='\0';
       if(!strcmp(inSerial,"/END")) 
       {
         Serial.println("_");
         inSerial[0]=0x1a;
         inSerial[1]='\0';
         gsm.SimpleWriteln(inSerial);
        }
        //Envia um comando AT utilizando a serial
        if(!strcmp(inSerial,"TEST")) 
        {
          Serial.println("SIGNAL QUALITY");
          gsm.SimpleWriteln("AT+CSQ");
        } 
        else 
        {
          Serial.println(inSerial);
          gsm.SimpleWriteln(inSerial);
         }
         inSerial[0]='\0';
     }
}

void serialswread()
{
   gsm.SimpleRead();
}
