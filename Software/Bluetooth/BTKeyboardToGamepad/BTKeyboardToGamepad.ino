/**
 * BTKeyboardToGamepad.ino
 * Written by: Milador
 * Version 1.0 (13/2/2021)
 * Github Link: https://github.com/milador/Teensy-XAC-Converter/
 * 
 * Copyright (c) 2021 milador.ca
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, and distribute copies of the Software, 
 * for non-commercial purposes and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
**/

#include "USBHost_t36.h"


#define BEGIN()     useManualSend(true)
#define SETXAXIS(x) X(x)
#define SETYAXIS(x) Y(x)
#define SETBUTTON(button_num, value)    button(((button_num)), (value))
#define SENDSTATE() send_now()

//Can be customized 

#define DEBUG_MODE true

//


//Keyboard Action structure 
typedef struct { 
  long int keyboardNum;
  const char* keyboardAction;
  int keyboardCode;
  long int keyboardGamepadAction;
} keyboardStruct;

//Special Keyboard Action structure 
typedef struct { 
  long int specKeyboardNum;
  long int specKeyboardCode;
  String specKeyboardName;
  long int specKeyboardGamepadAction;
} specKeyboardStruct;


//Can be customized 
const keyboardStruct keyboardDictionary[] {
    {0," ",32,5},                        //Space
    {1,"!",33,1},                        //!
    {2,"\"",34,2},                       //"
    {3,"#",35,3},                        //#
    {4,"$",36,4},                        //$
    {5,"%",37,5},                        //%
    {6,"&",38,6},                        //&
    {7,"'",39,7},                        //'
    {8,"(",40,8},                        //(
    {9,")",41,0},                        //)
    {10,"*",42,0},                       //*
    {11,"+",43,0},                       //+
    {12,",",44,0},                       //
    {13,"-",45,0},                       //-
    {14,".",46,0},                       //.
    {15,"/",47,0},                       ///
    {16,"0",48,0},                       //0
    {17,"1",49,0},                       //1
    {18,"2",50,0},                       //2
    {19,"3",51,0},                       //3
    {20,"4",52,0},                       //4
    {21,"5",53,0},                       //5
    {22,"6",54,0},                       //6
    {23,"7",55,0},                       //7
    {24,"8",56,0},                       //8
    {25,"9",57,0},                       //9
    {26,":",58,0},                       //:
    {27,";",59,0},                       //;
    {28,"<",60,0},                       //<
    {29,"=",61,0},                       //=
    {30,">",62,0},                       //>
    {31,"?",63,0},                       //?
    {32,"a",97,5},                         //a                                      
    {33,"b",98,0},                         //b
    {34,"c",99,0},                         //c
    {35,"d",100,0},                        //d
    {36,"e",101,0},                         //e
    {37,"f",102,0},                         //f
    {38,"g",103,0},                         //g
    {39,"h",104,0},                         //h
    {40,"i",105,0},                         //i
    {41,"j",106,0},                         //j
    {42,"k",107,0},                         //k
    {43,"l",108,0},                         //l
    {44,"m",109,0},                         //m
    {45,"n",110,0},                         //n
    {46,"o",111,0},                         //o
    {47,"p",112,0},                         //p
    {48,"q",113,0},                         //q
    {49,"r",114,0},                         //r
    {50,"s",115,6},                         //s
    {51,"t",116,0},                         //t
    {52,"u",117,0},                         //u
    {53,"v",118,0},                         //v
    {54,"w",119,0},                         //w
    {55,"x",120,2},                         //x
    {56,"y",121,0},                         //y
    {57,"z",122,1},                         //z
    {58,"{",123,0},                         //{
    {59,"|",124,0},                         //|
    {60,"}",125,0},                         //}
    {61,"~",126,0},                         //~
    {62," ",128,0},                         //LCRTL
    {63," ",129,0},                         //LSHIFT
    {64," ",130,0},                         //LALT
    {65," ",131,0},                         //LGUI
    {66," ",132,0},                         //RCRTL
    {67," ",133,0},                         //RSHIFT
    {68," ",134,0},                         //RALT
    {69," ",135,0},                         //RGUI
    {70," ",178,0},                         //BACKSPACE
    {71," ",179,0},                         //TAB
    {72," ",176,0},                         //RETURN
    {73," ",177,0},                         //ESC
    {74," ",193,0},                         //CAPSLOCK
    {75," ",KEYD_UP,9},                         //UP
    {76," ",KEYD_DOWN,10},                         //DN
    {77," ",KEYD_LEFT,11},                         //LEFT
    {78," ",KEYD_RIGHT,12},                         //RIGHT
    {79," ",KEYD_INSERT,0},                         //INS
    {80," ",KEYD_DELETE,0},                         //DEL
    {81," ",KEYD_PAGE_UP,0},                         //PUP
    {82," ",KEYD_PAGE_DOWN,0},                         //PDN
    {83," ",KEYD_HOME,0},                         //HOME
    {84," ",KEYD_END,0},                         //END
    {85," ",KEYD_F1,0},                         //F1
    {86," ",KEYD_F2,0},                         //F2
    {87," ",KEYD_F3,0},                         //F3
    {88," ",KEYD_F4,0},                         //F4
    {89," ",KEYD_F5,0},                         //F5
    {90," ",KEYD_F6,0},                         //F6
    {91," ",KEYD_F7,0},                         //F7
    {92," ",KEYD_F8,0},                         //F8
    {93," ",KEYD_F9,0},                         //F9
    {94," ",KEYD_F10,0},                         //F10
    {95," ",KEYD_F11,0},                         //F11
    {96," ",KEYD_F12,0}                         //F12
 };

const specKeyboardStruct specKeyboardDictionary[] {
    {0,128,"LCRTL",0},                                      
    {1,129,"LSHIFT",1},
    {2,130,"LALT",0},
    {3,131,"LGUI",0},
    {4,132,"RCRTL",0},                                      
    {5,133,"RSHIFT",1},
    {6,134,"RALT",0},
    {7,135,"RGUI",0},
    {8,178,"BACKSPACE",0},                                      
    {9,179,"TAB",0},
    {10,176,"RETURN",0},
    {11,177,"ESC",0},
    {12,193,"CAPSLOCK",0},
    {13,KEYD_UP,"UP",0},                                      
    {14,KEYD_DOWN,"DN",1},
    {15,KEYD_LEFT,"LEFT",0},
    {16,KEYD_RIGHT,"RIGHT",0},
    {17,KEYD_INSERT,"INS",0},
    {18,KEYD_DELETE,"DEL",0},                                      
    {19,KEYD_PAGE_UP,"PUP",0},
    {20,KEYD_PAGE_DOWN,"PDN",0},
    {21,KEYD_HOME,"HOME",0},
    {22,KEYD_END,"END",0},
    {23,KEYD_F1,"F1",0},
    {24,KEYD_F2,"F2",0},
    {25,KEYD_F3,"F3",0},
    {26,KEYD_F4,"F4",0},
    {27,KEYD_F5,"F5",0},
    {28,KEYD_F6,"F6",0},
    {29,KEYD_F7,"F7",0},
    {30,KEYD_F8,"F8",0},
    {31,KEYD_F9,"F9",0},
    {32,KEYD_F10,"F10",0},
    {33,KEYD_F11,"F11",0},
    {34,KEYD_F12,"F12",0}
 };


USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
KeyboardController keyboard1(myusb);
USBHIDParser hid1(myusb);
USBHIDParser hid2(myusb);
USBHIDParser hid3(myusb);
USBHIDParser hid4(myusb);
USBHIDParser hid5(myusb);
MouseController mouse1(myusb);


BluetoothController bluet(myusb, true, "0000");   // Version does pairing to device
//BluetoothController bluet(myusb);   // version assumes it already was paired

USBDriver *drivers[] = {&hub1, &hub2, &keyboard1, &bluet, &hid1, &hid2, &hid3, &hid4, &hid5};

#define CNT_DEVICES (sizeof(drivers)/sizeof(drivers[0]))
const char * driver_names[CNT_DEVICES] = {"Hub1", "Hub2", "KB1", "Bluet", "HID1" , "HID2", "HID3", "HID4", "HID5"};

bool driver_active[CNT_DEVICES] = {false, false, false, false};

// Lets also look at HID Input devices
USBHIDInput *hiddrivers[] = {&mouse1};

#define CNT_HIDDEVICES (sizeof(hiddrivers)/sizeof(hiddrivers[0]))
const char * hid_driver_names[CNT_HIDDEVICES] = {"Mouse1"};

bool hid_driver_active[CNT_HIDDEVICES] = {false};

BTHIDInput *bthiddrivers[] = {&keyboard1, &mouse1};
#define CNT_BTHIDDEVICES (sizeof(bthiddrivers)/sizeof(bthiddrivers[0]))
const char * bthid_driver_names[CNT_BTHIDDEVICES] = {"Keyboard(BT)", "Mouse(BT)"};
bool bthid_driver_active[CNT_BTHIDDEVICES] = {false};

void setup()
{
  delay(5000);
  //while (!Serial) ; // wait for Arduino Serial Monitor
  
  Serial.begin(115200);
  Serial1.begin(115200);
  
  Serial.println("\n\nXAC-Input-Converter");
  Serial.println("\n\nBTKeyboardToGamepad");
  Serial.println(sizeof(USBHub), DEC);
  myusb.begin();
  keyboard1.attachPress(OnPress);
  keyboard1.attachRelease(OnRelease);
  Joystick.BEGIN();
}


void loop()
{
  myusb.Task();

}

void OnPress(int key)
{
  int keyCode = getGamepadButton(key);
  if(DEBUG_MODE) { printDebug(key,keyCode); }
  pressGamepadButton(keyCode);
}

void OnRelease(int key)
{
   releaseGamepad();
}

//***GET GAMEPAD ACTION BUTTONS FUNCTION***//

int getGamepadButton(int code) {  
  int gamepadOut = 0;
  //Search for Ascii code based on character number
  for(uint8_t j = 0; j < sizeof(keyboardDictionary)/sizeof(keyboardStruct); ++j) {
    if(code == keyboardDictionary[j].keyboardCode)
    {
      gamepadOut= keyboardDictionary[j].keyboardGamepadAction;
    }
  }
  return gamepadOut;
}

//***GET SPEC GAMEPAD ACTION BUTTONS FUNCTION***//

int getSpecGamepadButton(int code) {  
  int gamepadOut = 0;
  //Search for Ascii code based on character number
  for(uint8_t j = 0; j < sizeof(specKeyboardDictionary)/sizeof(specKeyboardStruct); ++j) {
    if(code == specKeyboardDictionary[j].specKeyboardCode)
    {
      gamepadOut= specKeyboardDictionary[j].specKeyboardGamepadAction;
    }
  }
  return gamepadOut;
}

//***PRESS GAMEPAD BUTTON FUNCTION***//

void pressGamepadButton(int key)
{
  if(key==9){ //UP
    Joystick.SETYAXIS(1023);
    Joystick.SENDSTATE();
  } else if(key==10){ //DN
    Joystick.SETYAXIS(0);
    Joystick.SENDSTATE();    
  } else if(key==11){ //LEFT
    Joystick.SETXAXIS(0);
    Joystick.SENDSTATE();    
  } else if(key==12){  //RIGHT
    Joystick.SETXAXIS(1023);
    Joystick.SENDSTATE();    
  } else if(key<=8 && key>=1){  //RIGHT
    Joystick.SETBUTTON(key,1);
    Joystick.SENDSTATE();    
  } 
}

//***CLEAR OR RELEASE GAMEPAD ACTION FUNCTION***//

void releaseGamepad()
{
    for (int i = 1; i <= 8; i++) {
      Joystick.SETBUTTON(i,0);
    }
    Joystick.SETXAXIS(512);
    Joystick.SETYAXIS(512);
    Joystick.SENDSTATE();
}


//***PRINT DEBUG FUNCTION***//

void printDebug(int key, int code)
{
    Serial.print("key = ");
    Serial.print(key);
    Serial.print("keyCode = ");
    Serial.print(code);
    Serial.println();      

}
