

#include "DHT.h"
#define DHTPIN A1 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);

#include <SoftwareSerial.h>
SoftwareSerial mySerial(6,7);

#include <LiquidCrystal.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

                              
float t;
int val,val1;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
mySerial.begin(9600);
 lcd.begin(16, 2);
 pinMode(2,OUTPUT);
 pinMode(A0,INPUT);
 
 
dht.begin();

 analogWrite(6,255);  
}

void loop() {

 
   
 
  t = dht.readTemperature();
  float h = dht.readHumidity();
   //Serial.print(F("%  Temperature: "));
 // Serial.println(t);
      lcd.setCursor(0,0);
      lcd.print("T:");
      lcd.print(t);
        lcd.print(" ");
           
  if(t > 36)   
  {
   digitalWrite(4,HIGH);
    digitalWrite(7,HIGH);
   delay(200); 
    lcd.print("HT");
        lcd.print(" ");   
  }
  else
  {
        digitalWrite(4,LOW);
         digitalWrite(7,LOW);
       lcd.print("  ");
        lcd.print(" ");      
  }
  

 val1 = digitalRead(A0);

 Serial.println(val1);
 if(val1 ==  LOW){
 digitalWrite(4,HIGH);
 lcd.setCursor(0,1);
      lcd.print("AL detected.......");

       
        analogWrite(6,100);
        sms1();          
  }
 else
 {
   
 digitalWrite(4,LOW);
 
 } 
 delay(500);
      
  }
        

void sms1()
{
lcd.setCursor(0, 1);
  lcd.print("SENDING SMS...............");
 mySerial.println("AT\r");
  delay(1000);
  mySerial.println("AT+CMGF=1\r");
  delay(1000);
  mySerial.println("AT+CMGS=\"+919487392030\"\r");
  delay(1000);
  mySerial.println("Alcohol detected..");
  delay(1000);
  mySerial.println((char)26);
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("SMS SENT...............");
  d:goto d;
}