/* Kosmoduino Test Code for 
KosmoBits GameController */

/***********************************/
/** Base coode: Kosmoduino077 ******/
/************ Bobby Mod ************/
/***********************************/

/************************************/
/**********************************
** Modifizierung Scrollrad ********
** built 20151222 *****************
** Steffen Rothweiler *************
** Kosmos Product Development *****
** Version: KD77_8_ ***************
***********************************
** incl. Wheel_4_2 ****************
*********************************** 
*/

/***************************************
 *  Changes: Anpassung der Sensoren ****
 *  Licht, Beschleunigung, Temperatur **
 *  ************************************
 *   Die Sensoren Licht und Temperatur *
 *  * passen sich den Umgebungswerten **
 *  *** beim Einstecken an *************
 *  ************************************
 *  ***** App Version: 19_01_2016 ****** 
 ***************************************/

/***************************************
 * v 81x: different versions of ********
 * Kelvins reaction ********************
 * v 810: multiple hit while Kelvin ****
 * gets hoter **************************
 ***************************************
 * erneutes Ausl?sen [reset] sobald ****
 * Seonsor über 50 erw?rmt wird ********
 * Anpassung bei Abkuehlung ************
 ***************************************
 *** ohne var [thigh] & [tlow] *********/

/*************************************
*** Encoder.lib **********************
*** by Paul Stoffregen ***************
**************************************
**************************************/



int L0 = 0;         // Licht-Ausgangsvariable L0

int T0 = 0;
// int tlow = 0;
// int thigh = 0;
// int grenz = 0;  //Variable fuer Temp-Ausloesewert

int f = 15;     // Variable fuer Grenze [T0+f]

boolean bol = false;  // Schalter für Licht-Ausgangsvariable L0
boolean bot = false;  // Schalter für Temperatur-Ausgangsvariable T0



int sig = 0;
int Signal = 0;
int id = 0;
#define button1 8
#define button2 7
int a = 1;
int r = 0;
int g = 0;
int b = 0;
int b1 = HIGH;
int b2 = HIGH;
char* Button1[] = {"pressed", "off"};
int x = 1;
char* Button2[] = {"pressed", "off"};
int y = 1;
char* character[] = {"nothing", "movement", "light", "volume", "temperature"};
int k = 0;
boolean test = false;
#include <Adafruit_NeoPixel.h>
#include <Encoder.h>                    //refer to Encoder.Lib
#define PIN 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

const int sampleWindow = 50; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;

volatile unsigned int Position = 0;
volatile unsigned int PositionLast = 0;
volatile unsigned int encoder0Pos = 0;

Encoder encoder(3, 2);                    //refer to Encoder.Lib

void setup() {

encoder.write(0);                         // Encoder zurück setzen
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);
pinMode(A5,INPUT);
pinMode(A6,INPUT);
pinMode(A7,INPUT);

Serial.begin(115200);
strip.begin();
strip.show(); // Initialize all pixels to 'off'
}
void writehigh()
{
  for(char i=2;i<14;i++)
  digitalWrite(i,HIGH);
}
void writelow()
{
  for(char i=2;i<14;i++)
  digitalWrite(i,LOW);
}
char inputString[20];         // a string to hold incoming data
char byte_num=0;
boolean stringComplete = false;  // whether the string is complete
#define AT_OK "AT+TEST=OK"
char output_flag=1;
#define check_none 0
#define check_high 1
#define check_low  2
#define check_ble  3
char check_state=check_none;
int time_value=0;
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString[byte_num] = inChar;
    byte_num++;
    if (inChar == 'K') {
      byte_num=0;
      stringComplete = true;
    }
  }
}
void loop() {

//Test Code
//**** 
//if(0)
  if(analogRead(A0)>900&&analogRead(A1)>900&&analogRead(A2)>900&&analogRead(A3)>900
  &&analogRead(A4)>900&&analogRead(A5)>900&&analogRead(A6)>900&&analogRead(A7)>900)
  {
    ///*
    switch(check_state)
    {
    case check_none:
      for(char i=2;i<14;i++)
      pinMode(i,OUTPUT);
      writehigh();
      check_state=check_high;
    break;
    case check_high:    
      delay(1500);
      check_state=check_low;
    break;
    case check_low:
      writelow();
      delay(1000);    
      check_state=check_ble;
      Serial.print("AT+TEST=OK");
    break;
    case check_ble:
      serialEvent();
      delay(10);   
      if (stringComplete) {
        if(!memcmp(inputString,AT_OK,10))
        {
      writehigh();
      delay(2000);
      writelow();
        }
        memset(inputString,0,20);
        stringComplete = false;
        }
        else 
        {
          time_value++;
          if(time_value%100==0)
          Serial.print("AT+TEST=OK");
          if(time_value>1000)
          time_value=0;
        }
    break;
     }    
  }
  else
  {   
    check_state=check_none;
//**** 
//Test Code End
  
sig = analogRead(1);
id = analogRead(2);
b1 = digitalRead(button1);
b2 = digitalRead(button2);

if (id < 491 || id >515)    //zu Anfang jedes Schleifendurchgangs wird 
{bol = false;};              //der Schalter für den Licht-Sensor zurückgesetzt

if (id < 991 || id > 1014)    //zu Anfang jedes Schleifendurchgangs wird 
{bot = false;};              //der Schalter für den Temp-Sensor zurückgesetzt




if(b1 == LOW){
  x = 0;} else {x=1;};
if(b2 == LOW){
  y = 0;} else {y=1;};

//**********************************
//*** Encoder **********************
//**********************************

 Position =  (encoder.read()/2)  ;     // 3 verschiedene Einstelliungen

//**********************************
//*** Bewegungssensor **************
//**********************************

if (id > 720 && id < 790){   
 k=1;
 
  r=22;
  g=10;
  b=3;
  
  Signal = map(sig, 325, 725, 0, 100);
  if (sig > 625){
    r = 200;};

}

else 

//**********************************
//*** Lichtsensor ******************
//**********************************


 

if (id > 490 && id < 515){  
k=2;



//**********************************
//*** Lichtsensor mit Ausgangswert * 
//*** der beim Einstecken des ******
//*** Sensorsgelesen wird **********
//**********************************



if (bol == false) {L0 = sig;};                    // Wert des Lichtsensors zum Zeitpunkt des Einsteckens

bol = true;                                      // Schalter für Licht-Ausgangsvariable L0

int llow = L0;                              // TRange des Lichtsensors von Ausgangswert 
int lhigh = L0 + 200;                       // beim Einstecken plus x



if (sig > lhigh){
  sig = lhigh;} else
  if (sig < llow) { 
    sig = llow;};
    
 r = map(sig, llow, lhigh, 5, 80);
  g = map(sig, llow, lhigh, 5, 80);
  b = map(sig, llow, lhigh, 5, 80);

  
  Signal = map(sig, llow, lhigh, 0, 100);


 
  } else 


//**********************************
//*** Lautst?rkesensor *************
//**********************************

if (id > 920 && id < 940){   
k=3;



unsigned long startMillis= millis(); // Start of sample window
    unsigned int peakToPeak = 0; // peak-to-peak level
     
    unsigned int signalMax = 0;
    unsigned int signalMin = 1024;
     
    // collect data for 50 mS
    while (millis() - startMillis < sampleWindow)
    {
    sample = analogRead(1);
    if (sample < 1024) // toss out spurious readings
    {
    if (sample > signalMax)
    {
    signalMax = sample; // save just the max levels
    }
    else if (sample < signalMin)
    {
    signalMin = sample; // save just the min levels
    }    }
    }
    peakToPeak = signalMax - signalMin; // max - min = peak-peak amplitude
    if (peakToPeak > 670){
   peakToPeak = 670;} else
   if (peakToPeak < 400){
   peakToPeak = 400;}; 
    g = map(peakToPeak, 400, 670, 30, 255);
    r = 0;
    b = 0;
    Signal = map(peakToPeak, 400, 670, 0, 100);

}else  

//**********************************
//*** Temperatursensor *************
//**********************************

if(id >990 && id < 1015){    
k=4;

if (bot == false) {T0 = sig;};                   // setzt den beim Einstecken aktuellen Sensorwert [sig]
                                                 // als Null-Ausgangswert [T0] des Sensors

  bot = true;                                    // Schalter für Temp-Ausgangsvariable L0
  
  
  if (r = map(sig, T0, T0 + f, 0, 100) <= 0) {r =0;} 
    else {r = map(sig, T0, T0 + f, 0, 100);};                                // streut die m?glichen Sensorwerte zwischen [tlow]
  b = map(sig, T0, (T0+13), 30, 0);           // und [thigh] auf Farbwerte [r]ot und [b]lau
  g=0;                                            // der [g]ruene Farbanteil bleibt aus  
 
 Signal = map(sig, T0, T0+f, 0, 100);          // streut die m?glichen Sensorwerte 
                                                  // zwischen [tlow] und [thigh] auf Signal-Werte 
                                                  // zwischen 0 und 100. 0 <= Signal <= 100
   
  if (sig > (T0 + f)){    r = 150;};               // erreicht oder übersteigt das [Signal] einen Wert 
                                                 // [thigh] leuchtet [r]ot am hellsten, hier max. [150]
                                              
  if (b<0) {b = 0; };                             // diese zewile verhindert, dass der Wert fuer [b]lau
                                                  // nicht unter 0 sinkt und somit wieder bei ganz hell 
                                                  // (250) begnnt 

//  *** changes for 81x to 807 ***
  
if (Signal >= 51)  {T0 = sig;};                
  
if (sig <= T0) {T0 = sig;};
       
}else

/*****************************
 *** Temperatursensor Ende ***
 ****************************/
 

{g=g+a;
Signal = 0;
k=0;

if( g > 20 || g < 0){
      g = 0;}
if (g == 0 || g >= 20) {
    a = -a ;}
    r = g;
    b = g;}
    
colorWipe(strip.Color(r, g, b), 1);

/********************************************************************
 *************** Programmteil Serial.print **************************
 ********************************************************************
 *** Achtung: dieser Code muss zum Spielen der App im ***************
 *** Originalzustand bleiben. Jegliche Aenderung fuehrt zu **********
 *** einem Versagen der Encodersteuerung ****************************
 ********************************************************************
 *******************************************************************/

Serial.println ("{");
Serial.print ("\"left button\" : ");
Serial.print("\""); Serial.print(Button1[x]); Serial.print("\"");
Serial.println(",");
Serial.print("\"right button\" : ");
Serial.print("\""); Serial.print(Button2[y]); Serial.print("\"");
Serial.println(",");
Serial.print("\"Sensor\" : ");
Serial.print(Signal);
Serial.println(",");
Serial.print("\"Encoder\" : ");
Serial.print(Position);
Serial.println(",");
Serial.print("\"ID\" : ");
Serial.print("\""); Serial.print(character[k]); Serial.println("\"");
 Serial.println("}");
 
/********************** ENDE ****************************************
 *************** Programmteil Serial.print **************************
 ********************************************************************
 ********************************************************************
 *** Achtung: dieser Code muss zum Spielen der App im ***************
 *** Originalzustand bleiben. Jegliche Aenderung fuehrt zu **********
 *** einem Versagen der Encodersteuerung ****************************
 *******************************************************************/
 

  // tabbed lines for debugginig mode only!
  // auskommentieren fuer Spielmodus!
/*
  Serial.print("sig:  ");   Serial.println(sig);
  Serial.print("T0:  ");   Serial.println(T0);
  Serial.print("T0 + f: ");   Serial.println(T0 + f);
  
  Serial.print("rot:  ");   Serial.println(r);
*/
//  Serial.print("gruen:  ");   Serial.println(g);
// Serial.print("blau:  ");   Serial.println(b);

strip.show();

delay(120);
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

//**********************************
//******** Code-Ende ***************
//**********************************








