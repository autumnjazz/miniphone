
float temperature;    // 온도 센서로부터 받는 전압값을 섭씨로 변경
int reading;      // 온도 센서로부터 받는 전압값
int lm35Pin = A0; // 온도 센서 연결 핀

void setup()  
{
    analogReference(DEFAULT);   // 온도 센서 초기화
    Serial.begin(9600);         // 시리얼 통신
}

void loop()  
{
    reading = analogRead(lm35Pin);    // 전압값을 받음
    temperature = (5.0 * analogRead(lm35Pin) * 100.0) / 1024;   // 섭씨로 변경


    Serial.println(temperature);      // 시리얼 모니터에 출력
    delay(3000);
}
