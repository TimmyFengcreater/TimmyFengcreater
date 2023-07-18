#include<avr/sleep.h>
#include <avr/interrupt.h>
#include<avr/wdt.h>
#include<DS1307RTC.h>
#include<time.h>
extern const int sensor = A0;
extern const int relay = 4;
extern const int SDA  = A4;
extern const int SCL = A5;

int getdata();
void detection();
void time();
void sleep();
void wakeup();

void setup() {
  Serial.begin(9600);
  analogReference(DEFAULT);
  pinMode(sensor,INPUT);
  pinMode(relay,OUTPUT);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  attachInterrupt(0,wakeup,RISING);
  // put your setup code here, to run once:

}

void loop() {
  detection();
  time();
 if(millis() >= 3600000){
   sleep();
 }
  // put your main code here, to run repeatedly:

}

int getdata(){
  int analogdata = analogRead(sensor);
  Serial.print("土壤湿度：");
  Serial.print(analogdata);
  Serial.println(" ");
  delay(500);
  return analogdata;
}
void detection(){
  int detectdata = getdata();
if(detectdata <= 50){ //50为最低阈值
    digitalWrite(relay,LOW);
    delay(200); //暂未定，以毫秒为延时单位
  }
  else{
    digitalWrite(relay,HIGH);
  }
}
void sleep(){
  sleep_bod_disable();
  sleep_enable();
  sleep_cpu();
}
void time(){
tmElements_t tm;
if(RTC.read(tm)){
  Serial.print(tmYearToCalendar(tm.Year));
  Serial.print("/");
  Serial.print(tm.Month);
  Serial.print("/");
  Serial.print(tm.Day);
  Serial.println(" ");
  Serial.print(tm.Hour);
  Serial.print(":"); 
  Serial.print(tm.Minute);
  Serial.print(":"); 
  Serial.print(tm.Second);
  Serial.println(" ");
}
else{
  Serial.print("error, please check your crucuit");
}
}

void wakeup(){
    sleep_disable();
}
