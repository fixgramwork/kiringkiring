#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <I2C_RTC.h>

static DS1307 RTC;
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 columns and 2 rows

void setup()
{
  Serial.begin(9600);
  RTC.begin();

  lcd.init();
  lcd.backlight();

  RTC.setHourMode(CLOCK_H12);
  // RTC.setHourMode(CLOCK_H24);

  if (RTC.getHourMode() == CLOCK_H12)
  {
     RTC.setMeridiem(HOUR_PM);
  }

  // Initialize RTC time and date
  RTC.setWeek(1);
  RTC.setDate(22, 07, 21);
  RTC.setTime(23, 00, 00);

  // Set pin modes
  pinMode(5, INPUT); // 날짜
  pinMode(6, INPUT); // 시간표
  pinMode(7, INPUT); // 캘린더
}

void loop()
{
  // Read pin states
  int readDate = digitalRead(5);
  int readSchedule = digitalRead(6);
  int readCalendar = digitalRead(7);

  if (readDate == HIGH) {
    displayDate();
  } else if (readSchedule == HIGH) {
    displaySchedule();
  } else if (readCalendar == HIGH) {
    displayCalendar();
  }

  delay(1000); // Delay to avoid bouncing
}

void displayDate() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Date: ");
  lcd.print(RTC.getYear());
  lcd.print("/");
  lcd.print(RTC.getMonth());
  lcd.print("/");
  lcd.print(RTC.getDay());

  lcd.setCursor(0, 1);
  lcd.print("Time: ");
  lcd.print(RTC.getHours());
  lcd.print(":");
  lcd.print(RTC.getMinutes());
  lcd.print(":");
  lcd.print(RTC.getSeconds());
  lcd.print(" ");
  if (RTC.getHourMode() == CLOCK_H12) {
    switch (RTC.getMeridiem()) {
      case HOUR_AM :
        lcd.print("AM");
        break;
      case HOUR_PM :
        lcd.print("PM");
        break;
    }
  }
}

void displaySchedule() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (RTC.getWeek()) {
    case 2: // MONDAY
      lcd.print("MON: 국|수|사|과|영|프|전|체");
      break;
    case 3: // TUESDAY
      lcd.print("TUE: 국|수|사|과|영|프|전|체");
      break;
    case 4: // WEDNESDAY
      lcd.print("WED: 국|수|사|과|영|프|전");
      break;
    case 5: // THURSDAY
      lcd.print("THU: 국|수|사|과|영|프|전|체");
      break;
    case 6: // FRIDAY
      lcd.print("FRI: 국|수|사|과|영|프|전|체");
      break;
    case 7: // SATURDAY
    case 1: // SUNDAY
      lcd.print("WEEKEND: 쉬는날");
      break;
  }
}

void displayCalendar() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Year: ");
  lcd.print(RTC.getYear());
  lcd.setCursor(0, 1);
  lcd.print("Calendar Function");
  // Implement calendar display function if needed
}
