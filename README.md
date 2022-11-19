## 청각장애인을 위한 위험 상황 알림 장치 
### (Hazardous Situation Notification System for Hearing Impaired Persons)
### 


> **<개발 이유>**
 
  일반인들에게는 일상처럼 피할 수 있는 사소하고 반복적인 위험 상황이 청각장애인들에게는 큰 사고로 이어질 수 있는 거대한 위험으로 다가오게 됩니다. 주변의 소리를 감지하여 사용자에게 알림을 주어 위험을 회피할 수 있게 해주는 전자기기가 있다면 청각을 통한 정보의 부재를 어느 정도 보완해줄 수 있지 않을까 하는 생각에 청각장애인들을 위한 위험 상황 알림 장치에 대하여 구상해 보기로 하였습니다. 
  
  ###   
  
  ### 구현 회로도
  
  ###
  ![구현회로도](https://github.com/yelunar/Hazardous-Notifi-System/blob/main/%EA%B5%AC%ED%98%84%ED%9A%8C%EB%A1%9C%EB%8F%84.png?raw=true)
  
  ### 구현 HW 
  ![구현HW앞](https://github.com/yelunar/Hazardous-Notifi-System/blob/main/%EA%B5%AC%ED%98%84%20HW%20%EC%95%9E.png?raw=true)
  ![구현HW측면](https://github.com/yelunar/Hazardous-Notifi-System/blob/main/%EA%B5%AC%ED%98%84%20HW%20%EC%B8%A1%EB%A9%B4.png?raw=true)
   
  ### 구현 HW 착용
  
  ###
  ![구현HW착용1](https://github.com/yelunar/Hazardous-Notifi-System/blob/main/%EA%B5%AC%ED%98%84%20HW%20%EC%B0%A9%EC%9A%A91.png?raw=true)
  ![구현HW착용2](https://github.com/yelunar/Hazardous-Notifi-System/blob/main/%EA%B5%AC%ED%98%84%20HW%20%EC%B0%A9%EC%9A%A92.png?raw=true)
  
  ### 구현 사진
  1) 소음 크기가 보통일 때
  
  ![소음보통](https://github.com/yelunar/Hazardous-Notifi-System/blob/main/%EC%86%8C%EC%9D%8C%20%ED%81%AC%EA%B8%B0%EA%B0%80%20%EB%B3%B4%ED%86%B5%EC%9D%BC%20%EB%95%8C.png?raw=true)
  
  2) 소음 크기가 강할 때
  
  ![소음강](https://github.com/yelunar/Hazardous-Notifi-System/blob/main/%EC%86%8C%EC%9D%8C%20%ED%81%AC%EA%B8%B0%EA%B0%80%20%EA%B0%95%ED%95%A0%20%EB%95%8C.png?raw=true)

소스코드는 다음과 같이 작성할 수 있습니다.

``` C++

#include <DS1302.h>
#include <SPI.h>
#include <TFT.h>

#define cs 10
#define dc 9
#define rst 8
#define SOUND_SENSOR_1  A3 // 사운드 센서1 핀
#define SOUND_SENSOR_2  A1 // 사운드 센서2 핀
#define vib 3
#define RED 2             // led R핀 
#define GREEN 4           // led G핀

int a; //센서1 상태 저장 변수
int b; //센서2 상태 저장 변수

TFT TFTscreen=TFT(cs,dc,rst);

DS1302 RTC(7,6,5);

void setup()  {      
  Serial.begin(9600);
  RTC.halt(false);
  RTC.writeProtect(false);
  RTC.setDOW(THURSDAY);		// RTC 모듈 요일 설정
  RTC.setTime(16, 26, 00);		// RTC 모듈 시간 설정
  RTC.setDate(31,5,2022);		// RTC 모듈 날짜 설정
  
  TFTscreen.begin();			// TFT LCD 시작
  TFTscreen.setRotation(0);		// TFT LCD 화면 회전
  TFTscreen.background(0,0,0);		// TFT LCD 뒷배경 색 설정 (검정색)
  TFTscreen.stroke(255,255,255);	// TFT LCD 글자 색 설정 (흰색)
  
  pinMode(A3,INPUT);       // 사운드 센서1 입력으로 설정
  pinMode(A1,INPUT);       // 사운드 센서2 입력으로 설정
  pinMode(vib,OUTPUT);     // 진동 센서 출력으로 설정
  pinMode(RED,OUTPUT);     // led R핀 출력으로 설정
  pinMode(GREEN,OUTPUT);  	// led G핀 출력으로 설정
}
  
void loop()  {
  a = analogRead(SOUND_SENSOR_1);  //센서1 상태변수 지정
  b = analogRead(SOUND_SENSOR_2);  //센서2 상태변수 지정
  Serial.print("a=");              //시리얼 모니터 출력
  Serial.print(a);
  Serial.print(" b=");
  Serial.println(b);
  
  analogWrite(GREEN,500); // LED GREEN 출력
  
  TFTscreen.stroke(255,255,255); 
  Time now=RTC.getTime();		// RTC 모듈의 현재 시각 변수로 설정
  TFTscreen.setTextSize(1); 		// TFT LCD 글자 크기 설정
  TFTscreen.setCursor(30,50);		// TFT LCD 출력 커서 설정
  TFTscreen.print(now.year);		// LCD에 날짜(년) 출력                                                                       
  TFTscreen.print("/");                                                                                     
  TFTscreen.print(now.mon);		// LCD에 날짜(월) 출력                                                                             
  TFTscreen.print("/");                                                                                    
  TFTscreen.print(now.date);		// LCD에 날짜(일) 출력                                                                          
  TFTscreen.print("  ");
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(15,80);
  if(now.hour<10){
    TFTscreen.print("0"); 
  }
  TFTscreen.print(now.hour);		// LCD에 시간(시) 출력                                                                             
  TFTscreen.print(":");
   if(now.min<10){
    TFTscreen.print("0"); 
  }
  TFTscreen.print(now.min);		// LCD에 시간(분) 출력                                                                          
  TFTscreen.print(":");
   if(now.sec<10){
    TFTscreen.print("0"); 
  }//| 
  TFTscreen.println(now.sec);		// LCD에 시간(초) 출력

  delay(500);
  
  TFTscreen.stroke(0,0,0);
  TFTscreen.setTextSize(1); 
  TFTscreen.setCursor(35,50);
  TFTscreen.print(now.year);                                                                        
  TFTscreen.print("/");                                                                                    
  TFTscreen.print(now.mon);                                                                             
  TFTscreen.print("/");                                                                                     
  TFTscreen.print(now.date);                                                                               
  TFTscreen.print("  ");
  TFTscreen.setTextSize(2);
  TFTscreen.setCursor(15,80);
  if(now.hour<10){
    TFTscreen.print("0"); 
  }
  TFTscreen.print(now.hour);                                                                             
  TFTscreen.print(":");
   if(now.min<10){
    TFTscreen.print("0"); 
  }
  TFTscreen.print(now.min);                                                                         
  TFTscreen.print(":");
   if(now.sec<10){
    TFTscreen.print("0"); 
  }// 
  TFTscreen.println(now.sec);

  if(a>600||b>600){ //소음수준 감지

     TFTscreen.stroke(0,0,0);
      TFTscreen.setTextSize(1); 
  TFTscreen.setCursor(30,50);
    TFTscreen.print(now.year);                                                                        
  TFTscreen.print("/");                                                                                    
  TFTscreen.print(now.mon);                                                                             
  TFTscreen.print("/");                                                                                     
  TFTscreen.print(now.date);                                                                               
  TFTscreen.print("  ");
    int i;
    analogWrite(GREEN,0);		// LED GREEN 출력
    for(i=0;i<10;i++){
    analogWrite(vib,1000); 		// 진동 출력
    analogWrite(RED,200); 		// LED RED 출력
    TFTscreen.setTextSize(2); 
    TFTscreen.stroke(0,0,255);		// LCD 글자 색 설정(빨강)
    TFTscreen.text("Warning ! ",15,80);	// 소음 수준이 일정 치 초과할 시 문구 출력
    delay(300);
    analogWrite(vib,0);
    analogWrite(RED,0);
    TFTscreen.stroke(0,0,0);
    TFTscreen.text("Warning ! ",15,80);
   
    delay(100);
    a = analogRead(SOUND_SENSOR_1);  //센서1 상태변수 지정
    b = analogRead(SOUND_SENSOR_2);  //센서2 상태변수 지정
  
  
   Serial.print("a=");              //시리얼 모니터 출력
   Serial.print(a);
   Serial.print(" b=");
   Serial.println(b);
   }   }  }
   
   ```

 
