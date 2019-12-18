//TODO 부분에 함수 따로 만들어서 호출시켜주세요

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  

int moveButton = 4;
int okButton = 5;

uint8_t arrow[8] = {0x00,0x04,0x02,0x1F,0x02,0x04,0x00,0x00};
uint8_t clockicon[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0, 0x00};
uint8_t tempicon[8] = {0x04,0x0A,0x0A,0x0E,0x0E,0x0E,0x04,0x00};
uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4, 0x00};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0, 0x00};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0, 0x00};

long timesec;
int pre_pos = 0;
int pos = 0;
int message_cnt = 0;
int isOff = 0;
int isRead = 0; //isRead 가 1 이면 LED 끄기. 0이고 message_cnt 가 1이상이면 LED 켜기
int pos_time = 0;
int pos_message = 0;
int pos_text = 0;
const char * customText[5];
const char * message[5];
void setup() {
  Serial.begin(9600);
  //button
  pinMode(moveButton, INPUT_PULLUP);
  pinMode(okButton, INPUT_PULLUP);
  //lcd
  lcd.init();
  lcd.setCursor(5,0);
  lcd.backlight();
  lcd.setBacklight(200);
  lcd.print("Hello!");
  lcd.createChar(0, arrow);
  lcd.createChar(1, clockicon);
  lcd.createChar(2, tempicon);
  lcd.createChar(3, bell);
  lcd.createChar(4, heart);
  lcd.createChar(5, cross);
  lcd.home();
  delay(500);
  lcd.clear();
  lcdMenu(pos);
  //customtext
  customText[0] = "The most important things in life aren't things.";
  customText[1] = "The world is full of beautiful things, including you.";
  customText[2] = "Be yourself. Everyone else is taken.";
  customText[3] = "Try not to become a man of success but a man of value.";
  customText[4] = "I can accept failure, but I can't accept not trying.";
  //message
  message[0] = "where r u?";
  message[1] = "you'll be great";
  message[2] = "idk..";
  message[3] = "cu later";
  message[4] = "miss ya";
}


void loop() {
  //random message
  if(message_cnt < 4){
    timesec++;
    if(timesec % 30 == 0){ //TODO: LED 켜기. 약 30초마다 한번 메세지 도착.
      message_cnt ++; 
      Serial.print(message_cnt);
    }
  }
  int r = rand()%20;
  //btn
  int movebtn ; int okbtn;
  movebtn = digitalRead(moveButton);
  okbtn = digitalRead(okButton);
    
  if(movebtn == 0 && okbtn == 1){ //movebutton
    if(pos == 5) pos = 0;
    else pos++;
    lcdMenu(pos);
  }
  else if(movebtn == 1 && okbtn == 0){ //okbutton
    if(pos != 0) pre_pos = pos;
    lcdClick(pos);
  }
  else if(movebtn == 0 && okbtn == 0 && isOff == 1){
    isOff = 0;
    pos = 0;
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.backlight();
    lcd.setBacklight(200);
    lcd.print("Hello!");
    delay(500);
    lcd.clear();
    lcdMenu(pos);
  }
  delay(300);
}

void lcdMenu(int pos){
  char poschar[6] = {'N', 'C', 'T','M', 'H', 'E'};
  lcd.setCursor(0,0);
  if(pos == 0) lcd.print(poschar[0]);
  else lcd.write(0);
  lcd.print("    ");
  for(int i =1 ; i < 5; i++){
    lcd.setCursor(i+5,0);
    if(pos == i) lcd.print(poschar[i]);
    else lcd.write(i);
  }
  lcd.print("     ");
  lcd.setCursor(15,0);
  if(pos == 5) lcd.print(poschar[5]);
  else lcd.write(5);
}

void lcdClick(int pos){
  int x;
  if(pos == 0) x = pre_pos;
  else x = pos;
  switch (x){
    case 1: //clock
      showTime();
      break;
    case 2: //temperature
      showTemperature();
      break;  
    case 3: //alarm
      showAlarm();
      break;
    case 4: //heart
      showText();
      break;
    case 5: //exit
      lcdOff();
      break;
  }
}

void showTime(){ //time_data 에 시간, date_data에 날짜

  ///TODO: 시간, 날짜 가져오는 코드 작성
    
  if (pos == 0){
    if (pos_time == 1) pos_time = 0;
    else pos_time = 1;
  }
  String time_data = "10:07 pm"; // 8칸 개수 맞춰야 해요. 또는 밑에 빈칸 포함 16칸
  String date_data = "2019.12.18"; //10칸
  lcd.setCursor(0,1);
  if(pos_time == 0)  {
    lcd.print("    ");
    lcd.print(time_data);
    lcd.print("    ");
  }
  else {
    lcd.print("   ");
    lcd.print(date_data);
    lcd.print("   ");
  }
  
}
void showTemperature(){

  ///TODO: 시간, 날짜 가져오는 코드 작성
  
  String temp_data = "23.5 C"; // 6칸 개수 맞춰야 해요. 또는 밑에 빈칸 포함 16칸
  lcd.setCursor(0,1);
  lcd.print("     ");
  lcd.print(temp_data);
  lcd.print("     ");
}

void showAlarm(){
  lcd.setCursor(0,1);
  lcd.print(" ");
  lcd.print(message_cnt);
  lcd.print(" message to u ");
  if (pos == 0){
    if (pos_message == message_cnt-1) pos_message = 0;  
    else if(pos_message<message_cnt-1)  pos_message += 1;
    if(message_cnt != 0){
      int size_msg = strlen(message[pos_message]);
      lcd.setCursor(0,1);
      for(int i = 0; i<16; i++){
        if(i< size_msg){
          lcd.print(message[pos_message][i]);
        }
        else{
          lcd.print(" ");
        }
      }
    }
    if(pos_message == message_cnt-1){
      isRead = 1; //TODO: LED 끄기. 메세지 읽음
      
    }
  }
  
}

void showText(){
  if (pos == 0){
    if (pos_text == 4) pos_text = 0;
    else pos_text += 1;
  }
  int size_text = strlen(customText[pos_text]);
  int cnt = size_text / 3;
  for (int j = 0; j < cnt; j++){
    lcd.setCursor(0,1);
    for(int i = j*3; i<j*3+16; i++){
      if(i < size_text){
        lcd.print(customText[pos_text][i]);
      }else{
        lcd.print(" ");
      }
    }
    delay(750);
  }
}
void lcdOff(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    Goodbye!    ");
  delay(1300);
  lcd.clear();
  lcd.noBacklight();
  isOff = 1;
}
