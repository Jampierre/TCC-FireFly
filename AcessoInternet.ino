//Programa: Arduino GSM Shield SIM900 - Acesso internet
//Autor: Arduino e Cia

#include "SIM900.h"
#include <SoftwareSerial.h>
#include "inetGSM.h"
#include "sms.h"

SMSGSM sms;
InetGSM inet;

boolean started = false;
char smsbuffer[160];
char n[20];

byte valor;

void setup()
{
  Serial.begin(9600);
  powerUpOrDown();
  Serial.println(F("Testando GSM Shield SIM900"));
  if (gsm.begin(2400))
  {
    Serial.println(F("\nstatus=READY"));
    started = true;
  }
  else Serial.println(F("\nstatus=IDLE"));
}

void loop()
{
  if (started) {
    //Aguarda novo SMS e envia para o servidor web
//    Metodo depreciado
    if (gsm.readSMS(smsbuffer, 160, n, 20)) {
//    if(sms.SendSMS("+5527981493334", "Teste Arduino GSM Internet + Servidor PHP")){
      String str(smsbuffer);
      envia_GSM(smsbuffer);
      delay(10000);
    }
    sms.GetSMS(1,n,20,smsbuffer,160);
    delay(1000);
  }
}

void powerUpOrDown()
{
  //Liga o GSM Shield
  Serial.print(F("Liga GSM..."));
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  delay(1000);
  digitalWrite(6, HIGH);
  delay(1000);
  Serial.println(F("OK!"));
  digitalWrite(6, LOW);
  delay(500);
}

void envia_GSM(String texto)
{
  char temp_string[55];
  char msg[10];
  int numdata;
  
  //TIM: inet.attachGPRS("timbrasil.br", "tim", "tim")
  //Vivo: inet.attachGPRS("zap.vivo.com.br", "vivo", "vivo")
  //Claro: inet.attachGPRS("claro.com.br", "claro", "claro")
  //Oi: inet.attachGPRS("gprs.oi.com.br", "oi", "oi")
  if (inet.attachGPRS("claro.com.br", "claro", "claro"))
    Serial.println(F("status=Conectado..."));
  else Serial.println(F("status=Nao conectado !!"));
  delay(100);
  String valor = "MSG_Texto1=" + texto;
  valor.toCharArray(temp_string, 55);
  Serial.println(">>>>>>>>>>>>>>>>>AQUI!!!");
  Serial.println(valor);
  Serial.println(temp_string);
  Serial.println(msg);
//  Serial.println(sms);
  numdata = inet.httpPOST("padariajl.com.br/arduino", 80, "/add.php", temp_string, msg, 50);
  delay(5000);
}
