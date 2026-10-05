#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Khoi tao LCD voi dia chi I2C 0x27, 16 cot x 2 dong
LiquidCrystal_I2C lcd(0x27, 16, 2);

int relay = 2; // Chan kich Relay dieu khien may bom
int sen = A0;  // Chan tin hieu Analog tu cam bien FC-28

void setup() {
  Serial.begin(9600);
  
  // Khoi tao LCD
  lcd.init();
  lcd.backlight();
  
  // Cau hinh che do chan I/O
  pinMode(relay, OUTPUT);
  pinMode(sen, INPUT);
  
  // Mac dinh tat may bom khi khoi dong
  digitalWrite(relay, LOW);
}

void loop() {
  int sum = 0;
  
  // Lay mau 10 lan lien tiep de khu nhieu
  for (int i = 1; i <= 10; i++) {
    int n = analogRead(sen);
    Serial.println(n);
    delay(50);
    
    int m = map(n, 0, 1023, 0, 100);
    m = 100 - m; 
    sum += m;
  }
  
  // Tinh trung binh do am (%)
  sum /= 10;
  Serial.println(sum);
  
  // Hien thi len LCD 16x2
  lcd.setCursor(3, 0);
  lcd.print("GROUP 16");
  lcd.setCursor(0, 1);
  lcd.print("soil moisture");
  lcd.setCursor(14, 1);
  lcd.print(sum);
  Serial.print(sum);
  
  // Logic tu dong bat/tat bom
  if (sum <= 30) {
    digitalWrite(relay, HIGH); // Do am <= 30%: Bat bom
  } else {
    digitalWrite(relay, LOW);  // Do am > 30%: Tat bom
  }
  
  delay(500);
}
