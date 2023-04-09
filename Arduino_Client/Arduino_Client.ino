#include <Kits4me_SimpleBtn.h>
#include <ASCIIDic.h>
#include <NX7Seg.h>

//---- Btns and Leds------
#define pinBtnR D2
#define pinBtnG D1
#define pinBtnB D1
#define pinLed  D4
#define pinLedY D3

Kits4me_SimpleBtn  btnR(pinBtnR);
Kits4me_SimpleBtn  btnG(pinBtnG);
Kits4me_SimpleBtn  btnB(pinBtnB);

//---- MUX -------
#define pinMuxA D5
#define pinMuxB D6
#define pinMuxC D7
#define pinMuxInOut A0

int ReadMuxChannel(byte chnl) {

    int a = (bitRead(chnl, 0) > 0) ? HIGH : LOW;
    int b = (bitRead(chnl, 1) > 0) ? HIGH : LOW;
    int c = (bitRead(chnl, 2) > 0) ? HIGH : LOW;

    digitalWrite(pinMuxA, a);
    digitalWrite(pinMuxB, b);
    digitalWrite(pinMuxC, c);

    int ret = analogRead(pinMuxInOut);

    return map(ret,0,1023,1,50);
}

//----- Display card 7 segments PINS-----
#define CLK_DIO   D5   // sclk
#define LATCH_DIO D6 //rclk
#define DATA_DIO  D7  // dio
nx7seg my4x7seg = nx7seg(LATCH_DIO, CLK_DIO, DATA_DIO, false); 

void showMux(int numberc) {
  my4x7seg.writeDigit((numberc > 9)?numberc%10:numberc,0,false);
  my4x7seg.writeDigit((numberc > 9)?numberc/10 : 0,1,false);
  my4x7seg.refresh(200);
}


// --- for server ---
unsigned long TimeForResponse;
int CH; // Room number
int DEV; // Bed number
// ---------------------

void setup_PinMode() {
  // Set DIO pins to outputs 
  pinMode(LATCH_DIO, OUTPUT);
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);

  //MUX SETUP
  pinMode(pinMuxA, OUTPUT);
  pinMode(pinMuxB, OUTPUT);
  pinMode(pinMuxC, OUTPUT);

  //Leds
  pinMode(pinLed,OUTPUT);
  pinMode(pinLedY,OUTPUT);
}


void setup() {
   Serial.begin(9600);  
   Serial.println("...started...");
   setup_PinMode();
   wifi_Setup();
   Serial.println("Started Setup");
   TimeForResponse = millis(); 

// Definition of bed number and room number
    while(btnB.isUp()){
      CH = ReadMuxChannel(3);
      showMux(CH);
    }
    delay(300);
    DEV = (btnB.isDown())? 2 : 1;
}

void loop() {
  if(btnG.isDown()){
        SendData(1);
    }
    
  if(btnR.isDown()){
       SendData(2);
    }
   
   if((millis() - TimeForResponse) > 1000){
      /*int res = GetData();
      digitalWrite(pinLed,(res == 1)? HIGH : LOW);*/
     TimeForResponse = millis();
    }
}
