//Progama : Envio SMS com o GSM Shield + Sensor de Gas MQ-2
//Alteracoes e adaptacoes : Jampierre V. Rocha
 
#include "SIM900.h"
#include <SoftwareSerial.h>
//Carrega a biblioteca SMS
#include "sms.h"
 
SMSGSM sms;

// Definicoes dos pinos ligados ao sensor
int pin_d0 = 7;
int pin_a0 = A2;

int nivel_sensor = 250;
 
int numdata;
boolean started=false;
char smsbuffer[160];
char n[20];

// Corpo do texto da mensagem SMS
char charBuf[50];
// Numeração da Foto
int i = 0;
void setup()
{
     // Define os pinos de leitura do sensor como entrada
     pinMode(pin_d0, INPUT);
     pinMode(pin_a0, INPUT);
     
     //Inicializa a serial 
     Serial.begin(9600);
     Serial.println("Testando GSM shield...");
     //Inicia a configuracao do Shield
     if (gsm.begin(2400)) 
     {
       Serial.println("nstatus=READY");
       started=true;
     } 
     else Serial.println("nstatus=IDLE");
}
 
void loop()
{
     // Le os dados do pino digital D0 do sensor
     int valor_digital = digitalRead(pin_d0);
     // Le os dados do pino analogico A0 do sensor
     int valor_analogico = analogRead(pin_a0);

     // Mostra os dados no serial monitor
     Serial.print("Pino D0 : ");
     Serial.print(valor_digital);
     Serial.print(" Pino A0 : ");
     Serial.println(valor_analogico);
    
     if(valor_analogico > nivel_sensor && started) 
     {
       String temp = String("Alto nivel de gas!\n A0(ppm): " 
                        + String(valor_analogico) + "\n"
                        + "Foto: GOPR00" + String(i/5) + "\n"
                        + "Localização GPS: -20.3611173,-40.3007353");
       temp.toCharArray(charBuf, 50);
       //Aguarda SMS e mostra o texto no serial monitor
       if (sms.SendSMS("+5527981493334", charBuf)){
          Serial.println("nSMS sent OK"); 
       }else{
          Serial.println("nSMS sent ERROR"); 
       }

       sms.GetSMS(1,n,20,smsbuffer,160);
       Serial.println(n);
       Serial.println(smsbuffer);
       delay(1000);
       i++;
     }
     delay(1000);
     i++;
}
