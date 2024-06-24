#include <Wire.h>
#include <LiquiCrystal_I2C.h>
#include <DS1302.h>
#include <string.h>

LiquiCrystal_I2C lcd(0x27,20,4); //A4, A5

void setup() {
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(115200);
  rtc.setDOW(TUESDAY); //요일
  rtc.setTime(14,10,0); //시간
  rtc.setDate(11,6,2024); //날짜

  pidMode(0,INPUT);//위
  pidMode(1,INPUT);//아래
  pinMode(2,INPUT);//좌
  pinMode(3,INPUT);//우

  lcd.init(); //초기화
  lcd.backlight(); //불 켜기

  lcd.setCursor(0,0); //1번째 줄
  lcd.serCursor(0,1); //2번째 줄
  lcd.setCursor(0,2); //3번째 줄
  lcd.setCursor(0,3); //4번째 줄
  
}
void loop() {
  int readhome = digitalRead(0);
  int readcale = digitalRead(1);
  int readtime = digitalRead(2);

  //날짜
  if(readhome == 1){
    lcd.setCursor(0,0);
    lcd.print(rtc.getDateStr());
    lcd.print(rtc.getDOWStr());
    lcd.setCursor(0,1);
    lcd.print(rtc.getTime());
    lcd.setCursor(0,2);
    lcd.print("TYPE : Date");
    lcd.setCursor(0,3);
    delay(1000);
  }
//캘린터
  if(readcale == 1){

  }

//시간표
  if(readtime == 1){
    lcd.setCursor(0,0);
    if(strcmp(rtc.getDOWStr == "MONDAY"))
      lcd.print("국|수|사|과|영|프|전|체");
    else if(strcmp(rtc.getDOWStr == "TUESDAY"))
      lcd.print("국|수|사|과|영|프|전|체");
    else if(strcmp(rtc.getDOWStr == "WENSDAY"))
      lcd.print("국|수|사|과|영|프|전|체");
    else if(strcmp(rtc.getDOWStr == "TURSDAY"))
      lcd.print("국|수|사|과|영|프|전|체");
    else if(strcmp(rtc.getDOWStr == "FRIDAY"))
      lcd.print("국|수|사|과|영|프|전|체");
    else if(strcmp(rtc.getDOWStr == "SATURDAY"))
      lcd.print("쉬는날");
    else
      lcd.print("쉬는날");
  }


  /*Serial.print(rtc.getDOWStr());
  Serial.print(" ");

  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  Serial.println(rtc.getTimeStr());

  delay(1000);*/

  //날짜가 되었을때 초기화
  if(!strcmp(rtc.getDateStr(),"01,01,2000"))
    rtc.writeProtect(false);
  else
    rtc.writeProtet(true);
}
