#include "Mouse.h"
#include "./src/Encoder/Encoder.h"
//thanks my hero :)
//https://github.com/Reyn-Mukai/SDVX-DIY/tree/Standard
//from SDVX-DIY CODE
#include "Keyboard.h"
#include "Mouse.h"
#include <Adafruit_NeoPixel.h>



/*WS2812*/

/*Pot*/
int Sensor=A0;//将A0引脚取名为Sensor/ A0 pin Named Sensor
int SensorRead=0;
int newdata=0;
int inputValue=0;
int a;

/* button pin */
const int buttonPin1 = 9;          // Key left 1
const int buttonPin2 = 8;          // Key left 2
const int buttonPin3 = 7;          // Key left 3

const int buttonPin4 = 6;          // Key Right 4
const int buttonPin5 = 5;          // Key Right 5
const int buttonPin6 = 4;          // Key Right 6


const int FunctionL = 15;          // FKey left 
const int FunctionR = 10;          // FKey right

const int SideL = 16;          // SKey left 
const int SideR = 14;          // SKey right

/* Encoder pin */
/* 如果发现转动方向是反的就把3和2的位置调换一下*/
/*Switch "3" and "2" if the spin way was wrong*/
#define ENC_1_PIN_A 2
#define ENC_1_PIN_B 3


/* Encoder */
Encoder encLeft(ENC_1_PIN_A, ENC_1_PIN_B);


void setup() {
  Serial.begin(9600);
  // 初始化按键引脚，如果没有上拉电阻，需要使用INPUT_PULLUP/Pin Mode.
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(FunctionL, INPUT_PULLUP);
  pinMode(FunctionR, INPUT_PULLUP);
  pinMode(SideL, INPUT_PULLUP);
  pinMode(SideR, INPUT_PULLUP);
  // 初始化模拟键盘功能/Begin keyboard
  Keyboard.begin();
  Keyboard.releaseAll(); //所有键盘按键松开/Releasekeyboard
  //初始化鼠标/Begin Mousemove
  Mouse.begin();
  //归零编码器/encoder write 0
  encLeft.write(0);
  }

void Keys(){
   if (digitalRead(buttonPin1) == LOW){ //按键1/Key1
    Keyboard.press('a');
   }
   else {
    Keyboard.release('a');
}

   if (digitalRead(buttonPin2) == LOW){ //按键2/Key2
    Keyboard.press('s');
   }
   else {
    Keyboard.release('s');
}

   if (digitalRead(buttonPin3) == LOW){ //按键3/Key3
    Keyboard.press('d');
   }
   else {
    Keyboard.release('d');
}
if (digitalRead(buttonPin4) == LOW){ //按键4/Key 4
    Keyboard.press('j');
   }
   else {
    Keyboard.release('j');
}

   if (digitalRead(buttonPin5) == LOW){ //按键5/Key 5
    Keyboard.press('k');
   }
   else {
    Keyboard.release('k');
}

   if (digitalRead(buttonPin6) == LOW){ //按键6/Key 6
    Keyboard.press('l');
   }
   else {
    Keyboard.release('l');
}
}
void Function(){
  if (digitalRead(FunctionL) == LOW){ //功能键左/Menu L
    Keyboard.press('r');
   }
   else {
    Keyboard.release('r');
}
  if (digitalRead(FunctionR) == LOW){ //功能键右/Menu R
    Keyboard.press('u');
   }
   else {
    Keyboard.release('u');
}
}
void Side()
{
    if (digitalRead(SideL) == LOW){ //侧键1/Side 1
    Keyboard.press('p');
   }
   else {
    Keyboard.release('p');
}
  if (digitalRead(SideR) == LOW){ //侧键2/Side 2
    Keyboard.press('q');
   }
   else {
    Keyboard.release('q');
}
}
void Card(){
    if (digitalRead(FunctionL) == LOW && digitalRead(FunctionR) == LOW){ //回车键刷卡/hold Enter to load card
    Keyboard.press(0xB0);
   }
   else {
    Keyboard.release(0xB0);
}
}
void encFuncLeft(){
  updateMousePositionLeft();
}

void updateMousePositionLeft()
{
  static int prev_value = 0;
  int a;
  a = encLeft.read();
  Mouse.move((prev_value - a), 0, 0);
  prev_value = a;
}


void lever() 
{
    SensorRead=analogRead(Sensor);//读出Sensor的值并将它赋给SensorRead/Read Sensor and wirte for SensorRead
    newdata=map(SensorRead,0,1023,0,255);
    if (newdata >= 255)
    {
      newdata=(newdata - 128);
      Serial.println(newdata);
      }
    else if (newdata <= 255)
     {
      newdata=(newdata - 127);
      Serial.println(newdata);
      }
    }


void move()
{
  static int prev_value = 0;
  a = newdata;
  Mouse.move((prev_value - a), 0, 0);
  prev_value = a;
  
}


void loop()
  {
  Keys();
  Function();
  Side();
  Card();
  encFuncLeft();
  updateMousePositionLeft();
  move();
  }
