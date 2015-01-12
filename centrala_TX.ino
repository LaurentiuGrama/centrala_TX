
#include "DHT.h"


unsigned char      sendPin=5;
String Heat="1111111121001110011";
float MaxT=25;
float Interval=0.5;
boolean Isworking=false;
String signal ; 
float Temp;
unsigned long time;

#define receicePin 4
#define DHTTYPE DHT22
DHT dht(receicePin, DHTTYPE);


void setup() {
  Serial.begin(9600);
  Serial.println("Started;Centrala_TX.;;");
  pinMode(sendPin, OUTPUT);
  dht.begin();

}


void Send_1(){
  digitalWrite(sendPin, HIGH);   
  delayMicroseconds(750);             
  digitalWrite(sendPin, LOW);    
  delayMicroseconds(1850);   
}
void Send_2(){
  digitalWrite(sendPin, HIGH);   
  delayMicroseconds(7000);             
  digitalWrite(sendPin, LOW);    
  delayMicroseconds(10700);   
}

void Send_0(){
  digitalWrite(sendPin, HIGH);   
  delayMicroseconds(1800);             
  digitalWrite(sendPin, LOW);    
  delayMicroseconds(800);   
}


void  SendData(){
   
  for (int i = 0; i< Heat.length(); i++ ) {
     if       (Heat[i]=='1') Send_1(); 
     else if  (Heat[i]=='0') Send_0();
     else if  (Heat[i]=='2') Send_2();
  }
  digitalWrite(sendPin, LOW);    
  delay(220);
}

String SerialData(){
  char str;
  char c;
  if (Serial.available() > 0) {
    str=Serial.read();
    while(Serial.available()){
      c = Serial.read();
    }
    //Serial.print("I received: ");
    //Serial.println(str);
  }
  if ((str=='y') || (str=='Y')) return "True";
  else return "False"; 
}


void loop(){
 
  
  signal = SerialData();
  Temp= dht.readTemperature();
  if (Temp <(MaxT-Interval)) Isworking=true;
  else if (Temp >(MaxT+Interval)) Isworking=false;
  
  //Serial.print (Isworking);
  DebugF( signal + ";",Temp);
  if(Isworking && signal=="True" ) {
  //if (Isworking  ) {
    time=millis();
    while ((millis()-time)<30000){
      SendData();
      //Serial.print("Send Data !");
    }
  } 
  if (( signal=="False") || (!Isworking)) delay (30000); 
  
  
}

void DebugF(String te,float t){
  Serial.print(millis());
  Serial.print(";");
  Serial.print(te);
  Serial.print("");
  Serial.print(t,2);
  Serial.println("");
}


