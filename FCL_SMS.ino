// Example 55.7

#include <SoftwareSerial.h> 
char inchar; // Will hold the incoming character from the GSM shield
SoftwareSerial SIM900(2, 3);

int powerBotao = 9;

int Botao = 4;
int EstadoBotao = 0;

//int led1 = 10;
//int led2 = 11;
//int led3 = 12;
//int led4 = 13;

void setup()
{
  Serial.begin(19200);
  // set up the digital pins to control
 // pinMode(powerBotao, OUTPUT);
 // pinMode(led1, OUTPUT);
 // pinMode(led2, OUTPUT);
//  pinMode(led3, OUTPUT);
//  pinMode(led4, OUTPUT);
 // digitalWrite(led1, LOW);
 // digitalWrite(led2, LOW);
 // digitalWrite(led3, LOW);
 // digitalWrite(led4, LOW);

  // wake up the GSM shield
  SIM900power(); 
  SIM900.begin(19200);
  delay(20000);  // give time to log on to network.
  SIM900.print("AT+CMGF=1\r");  // set SMS mode to text
  delay(100);
  SIM900.println("AT+CMGD=1,4"); // delete all SMS
  delay(100);
  Serial.println("Mensagens antigas apagadas...");
  Serial.println();
  SIM900.print("AT+CNMI=2,2,0,0,0\r"); 
  delay(100);
  // blurt out contents of new SMS upon receipt to the GSM shield's serial out
  delay(100);
  Serial.println("Ready...");
}

void SIM900power()
// software equivalent of pressing the GSM shield "power" button
{
  digitalWrite(powerBotao, HIGH);
  //digitalWrite(9, HIGH);
  delay(1000);
  digitalWrite(powerBotao, LOW);
  //digitalWrite(9, LOW);
  delay(7000);
}

void sendSMSF() //Falta de energia
{
  Serial.println("Enviando SMS");
  Serial.println();
  SIM900.print("AT+CMGF=1\r");                    // AT command to send SMS message
  delay(100);
  SIM900.println("AT + CMGS = \"+554399814100\""); // recipient's mobile number, in international format
  delay(100);
  SIM900.println("CH 8480003565 com falta de fase"); // message to send
  delay(100);
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
 // SIM900power();                                   // turn off module
  Serial.println("SMS Enviado");
  Serial.println();
}

void sendSMST() //Status de temperatura
{
  Serial.println("Enviando SMS");
  Serial.println();
  SIM900.print("AT+CMGF=1\r");                    // AT command to send SMS message
  delay(100);
  SIM900.println("AT + CMGS = \"+554399814100\""); // recipient's mobile number, in international format
  delay(100);
  SIM900.println("Temperatura 42 graus"); // message to send
  delay(100);
  SIM900.println((char)26);                       // End AT command with a ^Z, ASCII code 26
  delay(100); 
  SIM900.println();
  delay(5000);                                     // give module time to send SMS
 // SIM900power();                                   // turn off module
  Serial.println("SMS Enviado");
  Serial.println();
 // SIM900.println("AT+CMGD=1,4"); // delete all SMS
 // delay(2000);
 // Serial.println("Mensagem apagada");
 // Serial.println();
 // Serial.println("*******SIM900 Desligado*******");
 // Serial.println();
}

void loop() 
{
  //SMS Falta de fase
  EstadoBotao = digitalRead(Botao);
  if(EstadoBotao == HIGH)
     {
      delay(5000);
      EstadoBotao = digitalRead(Botao);
      if(EstadoBotao == HIGH)
        {
         sendSMSF();
         Serial.println("Falta de fase");
         Serial.println();
        }
      }
  
  
  //If a character comes in from the cellular module...
  if(SIM900.available() >0)
  {
    inchar=SIM900.read(); 
    if (inchar=='t')//||inchar=='T')
    {
      delay(1000);
      Serial.println("T OK");
      inchar=SIM900.read(); 
      if (inchar=='e')//||inchar=='E')
      {
        delay(1000);
        Serial.println("E OK");
        inchar=SIM900.read();
        if (inchar=='m')//||inchar=='M')
        {
          delay(1000);
          Serial.println("M OK");
          inchar=SIM900.read();
          if (inchar=='p')//||inchar=='P')
            {
             delay(1000);
             Serial.println("P OK");
             sendSMST();
             delay(5000);
             Serial.println("5S");
             Serial.println();
             SIM900.println("AT+CMGD=1,4"); // delete all SMS
             Serial.println("Mensagem apagada");
             Serial.println();
            }
         }
         
         
        // inchar=SIM900.read();
      }
    }
  }
  
}
