#include <Adafruit_NeoPixel.h>
#include <KosmoBits_Pins.h>
#include <KosmoBits_Pixel.h>

const int TIMEOUT_ANSWER=2000;
const int TIMEOUT_STEP=50;

const int BUTTON_1 = KOSMOBITS_TASTE_1_PIN;
const int BUTTON_2 = KOSMOBITS_TASTE_2_PIN;

const KosmoBits_Pixel LED;

int count=0;

void setup() {
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  randomSeed(analogRead(12));
}

void loop(){
	int color=random(3);
	int expectedButton;

	switch(color){
	case 0:
		/* blue: button1 */
		setColor(0,0,255);
		expectedButton=calcButton(LOW,HIGH);
		break;
	case 1:
		/* green: button2 */
		setColor(0,255,0);
		expectedButton=calcButton(HIGH,LOW);
		break;
	case 2:
		/* yellow: both */
		setColor(255,255,0);
		expectedButton=calcButton(LOW,LOW);
		break;
	}

	delay(TIMEOUT_ANSWER-TIMEOUT_STEP*count);

	int actualButton1=digitalRead(BUTTON_1);
	int actualButton2=digitalRead(BUTTON_2);
	boolean correct=expectedButton==calcButton(actualButton1,actualButton2);

	if (correct){
		count++;
		playTone(true);
		LED.setColor(0,0,0,0);
	}else{
		if(LOW==actualButton1||LOW==actualButton2){
			playTone(false);
		}
		setColor(255,0,0);
	}
	  
  delay(3000);
}

void setColor(int r, int g, int b){
	LED.setColor(r,g,b,20);
}

int calcButton(int button1, int button2){
	return button1*10+button2;
}

void playTone(boolean correct){
	for(int i=1;i<5;i++){
		int frequency=correct?i:5-i;
		tone(KOSMOBITS_BUZZER_PIN, 200*frequency, 500);
		delay(100);
	}
}
