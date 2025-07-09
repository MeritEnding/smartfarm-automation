#include <LiquidCrystal.h>
#include <SHT1x.h>

#define dataPin 22
#define clockPin 23
SHT1x sht1x(dataPin, clockPin);

const int ledPin1 = 24;
const int ledPin2 = 25;
const int ledPin3 = 26;
const int ledPin4 = 27;

#define MOT1DIR1 2
#define MOT1DIR2 3
#define MOT1PWM 4

const int ledsw1 = 28; // 스위치 모듈 1번 입력 핀
const int ledsw2 = 29; // 스위치 모듈 2번 입력 핀
const int ledsw3 = 30; // 스위치 모듈 3번 입력 핀
const int ledsw4 = 31; // 스위치 모듈 4번 입력 핀

LiquidCrystal lcd(40,54,41,42,43,44,45);

void setup() {
  Serial.begin(9600);
  Serial.println("Starting up");
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  
  pinMode(MOT1DIR1, OUTPUT);
  pinMode(MOT1DIR2, OUTPUT);
  pinMode(MOT1PWM, OUTPUT);
  pinMode(ledsw1, INPUT);
  pinMode(ledsw2, INPUT);
  pinMode(ledsw3, INPUT);
  pinMode(ledsw4, INPUT);
  
  digitalWrite(MOT1DIR1, HIGH);
  digitalWrite(MOT1DIR2, HIGH);

  lcd.begin(16, 2);
}

void loop() {
  float temp_c, humi_pct;
  
  temp_c = sht1x.readTemperatureC();
  humi_pct = sht1x.readHumidity();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp_c, 1);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humi: ");
  lcd.print(humi_pct, 1);
  lcd.print("%");

  if (temp_c <= 17) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);

    Serial.println("Coooool! (o.o)");
    delay(1000);
  } else if (17 <= temp_c && temp_c <= 22) {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    digitalWrite(ledPin4, LOW);

    Serial.println("Cool! (^.^)");
    delay(1000);
  } else if (22 <= temp_c && temp_c <= 26) {
    

    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    digitalWrite(ledPin4, LOW);
    Serial.println("Warm! (^v^)");
    delay(1000);
  } else if (26 <= temp_c && temp_c<=30)
     {
       digitalWrite(MOT1DIR1,HIGH);
       digitalWrite(MOT1DIR2, LOW);
       digitalWrite(MOT1PWM,HIGH);

       digitalWrite(ledPin1, LOW);
       digitalWrite(ledPin2, LOW);
       digitalWrite(ledPin3, LOW);
      Serial.println("Hot! (T.T)");
       delay(2000);
     }
     else
     {
       Serial.println("Hoooot! (TT.TT)");
       digitalWrite(MOT1DIR1, LOW);
       digitalWrite(MOT1DIR2, HIGH);
       digitalWrite(MOT1PWM, HIGH);

       digitalWrite(ledPin1, LOW);
       digitalWrite(ledPin2, LOW);
       digitalWrite(ledPin3, LOW);
       digitalWrite(ledPin4, LOW);
       delay(5000);
     }
}
