#include <DS1302.h>
#include <SPI.h>
#include <TFT.h>

#define cs 10
#define dc 9
#define rst 8
#define SOUND_SENSOR_1  A3 // ���� ����1 ��
#define SOUND_SENSOR_2  A1 // ���� ����2 ��
#define vib 3
#define RED 2             // led R�� 
#define GREEN 4           // led G��

int a; //����1 ���� ���� ����
int b; //����2 ���� ���� ����

TFT TFTscreen = TFT(cs, dc, rst);

DS1302 RTC(7, 6, 5);

void setup() {
	Serial.begin(9600);
	RTC.halt(false);
	RTC.writeProtect(false);
	RTC.setDOW(THURSDAY);		// RTC ��� ���� ����
	RTC.setTime(16, 26, 00);		// RTC ��� �ð� ����
	RTC.setDate(31, 5, 2022);		// RTC ��� ��¥ ����

	TFTscreen.begin();			// TFT LCD ����
	TFTscreen.setRotation(0);		// TFT LCD ȭ�� ȸ��
	TFTscreen.background(0, 0, 0);		// TFT LCD �޹�� �� ���� (������)
	TFTscreen.stroke(255, 255, 255);	// TFT LCD ���� �� ���� (���)

	pinMode(A3, INPUT);       // ���� ����1 �Է����� ����
	pinMode(A1, INPUT);       // ���� ����2 �Է����� ����
	pinMode(vib, OUTPUT);     // ���� ���� ������� ����
	pinMode(RED, OUTPUT);     // led R�� ������� ����
	pinMode(GREEN, OUTPUT);  	// led G�� ������� ����
}

void loop() {
	a = analogRead(SOUND_SENSOR_1);  //����1 ���º��� ����
	b = analogRead(SOUND_SENSOR_2);  //����2 ���º��� ����
	Serial.print("a=");              //�ø��� ����� ���
	Serial.print(a);
	Serial.print(" b=");
	Serial.println(b);

	analogWrite(GREEN, 500); // LED GREEN ���

	TFTscreen.stroke(255, 255, 255);
	Time now = RTC.getTime();		// RTC ����� ���� �ð� ������ ����
	TFTscreen.setTextSize(1); 		// TFT LCD ���� ũ�� ����
	TFTscreen.setCursor(30, 50);		// TFT LCD ��� Ŀ�� ����
	TFTscreen.print(now.year);		// LCD�� ��¥(��) ���                                                                       
	TFTscreen.print("/");
	TFTscreen.print(now.mon);		// LCD�� ��¥(��) ���                                                                             
	TFTscreen.print("/");
	TFTscreen.print(now.date);		// LCD�� ��¥(��) ���                                                                          
	TFTscreen.print("  ");
	TFTscreen.setTextSize(2);
	TFTscreen.setCursor(15, 80);
	if (now.hour < 10) {
		TFTscreen.print("0");
	}
	TFTscreen.print(now.hour);		// LCD�� �ð�(��) ���                                                                             
	TFTscreen.print(":");
	if (now.min < 10) {
		TFTscreen.print("0");
	}
	TFTscreen.print(now.min);		// LCD�� �ð�(��) ���                                                                          
	TFTscreen.print(":");
	if (now.sec < 10) {
		TFTscreen.print("0");
	}//| 
	TFTscreen.println(now.sec);		// LCD�� �ð�(��) ���

	delay(500);

	TFTscreen.stroke(0, 0, 0);
	TFTscreen.setTextSize(1);
	TFTscreen.setCursor(35, 50);
	TFTscreen.print(now.year);
	TFTscreen.print("/");
	TFTscreen.print(now.mon);
	TFTscreen.print("/");
	TFTscreen.print(now.date);
	TFTscreen.print("  ");
	TFTscreen.setTextSize(2);
	TFTscreen.setCursor(15, 80);
	if (now.hour < 10) {
		TFTscreen.print("0");
	}
	TFTscreen.print(now.hour);
	TFTscreen.print(":");
	if (now.min < 10) {
		TFTscreen.print("0");
	}
	TFTscreen.print(now.min);
	TFTscreen.print(":");
	if (now.sec < 10) {
		TFTscreen.print("0");
	}// 
	TFTscreen.println(now.sec);

	if (a > 600 || b > 600) { //�������� ����

		TFTscreen.stroke(0, 0, 0);
		TFTscreen.setTextSize(1);
		TFTscreen.setCursor(30, 50);
		TFTscreen.print(now.year);
		TFTscreen.print("/");
		TFTscreen.print(now.mon);
		TFTscreen.print("/");
		TFTscreen.print(now.date);
		TFTscreen.print("  ");
		int i;
		analogWrite(GREEN, 0);		// LED GREEN ���
		for (i = 0; i < 10; i++) {
			analogWrite(vib, 1000); 		// ���� ���
			analogWrite(RED, 200); 		// LED RED ���
			TFTscreen.setTextSize(2);
			TFTscreen.stroke(0, 0, 255);		// LCD ���� �� ����(����)
			TFTscreen.text("Warning ! ", 15, 80);	// ���� ������ ���� ġ �ʰ��� �� ���� ���
			delay(300);
			analogWrite(vib, 0);
			analogWrite(RED, 0);
			TFTscreen.stroke(0, 0, 0);
			TFTscreen.text("Warning ! ", 15, 80);

			delay(100);
			a = analogRead(SOUND_SENSOR_1);  //����1 ���º��� ����
			b = analogRead(SOUND_SENSOR_2);  //����2 ���º��� ����


			Serial.print("a=");              //�ø��� ����� ���
			Serial.print(a);
			Serial.print(" b=");
			Serial.println(b);
		}
	}
}