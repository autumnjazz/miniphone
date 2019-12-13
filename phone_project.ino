//LCD & 버튼 : 장다래 
//2 digit 7SegDisplay : 강민철
//적외선 센서 : 김도이
 
// LEDDisplay Library 설치
// https://github.com/rastating/LEDDisplay/tree/master/LEDDisplay
#include <LEDDisplay.h>

//https://github.com/johnrickman/LiquidCrystal_I2C
#include <LiquidCrystal_I2C.h>


LEDDisplay *led;
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int btnleft = 9; // 왼쪽 버튼 핀
const int btnright = 8; //오른쪽 버튼 핀
int left = 0; //왼쪽 플래그
int right  =0; //오른쪽 플래그

int Led = 12; // LED에 연결된 12(데이터핀)을 led변수에 저장.
// 번호는 임의로 설정가능.
int sensor = 12; //적외선 센서에 연결된 12(데이터핀)을 sensor변수에 저장
int data; //센서의 입력값을 담을 변수

int led = 8;  // led 연결 
int outputpin= A5; // 센서와 연결된 아날로그 핀 설정

void setup() {

//버튼, LCD 설정
  pinMode(btnleft,INPUT);
  pinMode(btnright,INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("btn test");
//end
pinMode (Led, OUTPUT); // LED 단자를 출력으로 설정
 pinMode (sensor, INPUT); // 센서값을 입력으로 설정

  pinMode(8, OUTPUT);
    Serial.begin(9600); // 시리얼 통신을 열고 속도를 9600bps 로 사용한다.
    int digitFlagPins[] = {10, 11};
    int segmentPins[] = {2, 3, 4, 5 ,6 ,7 ,8, 9};
    int decimalPointPin = 9;
    led = new LEDDisplay(2, digitFlagPins, segmentPins, decimalPointPin);


}

void loop(){
//
  left = digitalRead(btnleft);
  right = digitalRead(btnright);
  if(left == HIGH && right == LOW){
    leftOn();
  }
  else if (left == HIGH && right == LOW){
    rightOn();
  }
  else if(left == HIGH && right == HIGH){
    bothOn();
  }
  else{
    bothOff();
  }
data = digitalRead (sensor); //적외선 센서의 입력값(읽어온 센서값)을 변수에 저장
   if (data == LOW) { 
      while(1){
        int i=0;
        if(i%2==0) digitalWrite (Led, HIGH); //LED 켬(5V 출력)
        else digitalWrite(Led,LOW);
        i++;
}


led->displayNumber(2, 1);
led->displayNumber(4, 0);
}
