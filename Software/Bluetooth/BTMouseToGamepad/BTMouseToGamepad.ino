/**
 * BTMouseToGamepad.ino
 * Written by: Milador
 * Version 1.0 (12/4/2020)
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

#define X_MOUSE_MAX 9
#define Y_MOUSE_MAX 5

#define X_MOUSE_MIN 2
#define Y_MOUSE_MIN 2

#define XY_MOUSE_DELTA_RATIO 1.5
#define YX_MOUSE_DELTA_RATIO 1.5

#define X_JOY_MAX 1023
#define Y_JOY_MAX 1023
//

typedef struct { 
  int actionNumber;
  String actionName;
  int actionButton;
} actionStruct;

int xMouseValue = 0;
int yMouseValue = 0;
int bMouseValue = 0;


int pollCounter = 0; 


//Action structure 
const actionStruct xacProperty[] {
    {0,"LEFT CLICK",1},                                      
    {1,"RIGHT CLICK",2},
    {2,"WHEEL UP",3},
    {3,"WHEEL DOWN",4}
 };

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHIDParser hid1(myusb);
USBHIDParser hid2(myusb);
USBHIDParser hid3(myusb);
USBHIDParser hid4(myusb);
USBHIDParser hid5(myusb);
MouseController mouse1(myusb);

BluetoothController bluet(myusb, true, "0000");   // Version does pairing to device
//BluetoothController bluet(myusb);   // version assumes it already was paired

RawHIDController rawhid1(myusb);
RawHIDController rawhid2(myusb, 0xffc90004);

USBDriver *drivers[] = {&hub1, &hub2,&bluet, &hid1, &hid2, &hid3, &hid4, &hid5};
#define CNT_DEVICES (sizeof(drivers)/sizeof(drivers[0]))
const char * driver_names[CNT_DEVICES] = {"Hub1","Hub2", "Bluet", "HID1" , "HID2", "HID3", "HID4", "HID5"};
bool driver_active[CNT_DEVICES] = {false, false, false, false};

// Lets also look at HID Input devices
USBHIDInput *hiddrivers[] = {&mouse1, &rawhid1, &rawhid2};
#define CNT_HIDDEVICES (sizeof(hiddrivers)/sizeof(hiddrivers[0]))
const char * hid_driver_names[CNT_DEVICES] = {"Mouse1", "RawHid1", "RawHid2"};
bool hid_driver_active[CNT_DEVICES] = {false, false};

void setup()
{
  delay(5000);
  //while (!Serial) ; // wait for Arduino Serial Monitor

  Serial.begin(115200);
  Serial1.begin(115200);
  
  Serial.println("\n\nXAC-Input-Converter");
  Serial.println("\n\nBTMouseToGamepad");
  Serial.println(sizeof(USBHub), DEC);
  myusb.begin();
  Joystick.BEGIN();
}


void loop()
{
  myusb.Task();

  for (uint8_t i = 0; i < CNT_DEVICES; i++) {
    if (*drivers[i] != driver_active[i]) {
      if (driver_active[i]) {
        Serial.printf("*** Device %s - disconnected ***\n", driver_names[i]);
        driver_active[i] = false;
      } else {
        Serial.printf("*** Device %s %x:%x - connected ***\n", driver_names[i], drivers[i]->idVendor(), drivers[i]->idProduct());
        driver_active[i] = true;

        const uint8_t *psz = drivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = drivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = drivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);


      }
    }
  }

  for (uint8_t i = 0; i < CNT_HIDDEVICES; i++) {
    if (*hiddrivers[i] != hid_driver_active[i]) {
      if (hid_driver_active[i]) {
        Serial.printf("*** HID Device %s - disconnected ***\n", hid_driver_names[i]);
        hid_driver_active[i] = false;
      } else {
        Serial.printf("*** HID Device %s %x:%x - connected ***\n", hid_driver_names[i], hiddrivers[i]->idVendor(), hiddrivers[i]->idProduct());
        hid_driver_active[i] = true;

        const uint8_t *psz = hiddrivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = hiddrivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = hiddrivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);
      }
    }
  }

  if (mouse1.available()) {
    bMouseValue = mouse1.getButtons();
    xMouseValue = mouse1.getMouseX();
    yMouseValue = mouse1.getMouseY();
    if ((abs(xMouseValue) > X_MOUSE_MIN) || (abs(yMouseValue) > Y_MOUSE_MIN)) {         //Check if mouse move is larger than minimum or threshold 
      pollCounter++;
      delay(10);
      if (pollCounter >= 3) {                                                           //Check if it has repeated and not false positive 
        moveGamepadStick(xMouseValue,yMouseValue);                         //Move stick
        if(bMouseValue>0){                                                              //Check if mouse buttons are pressed 
          if(DEBUG_MODE) { printDebug(4); }
          pressGamepadButton(bMouseValue,1);                                            //Press mapped button 
        } 
        pollCounter=0;
        delay(100);
        Joystick.SENDSTATE();
      }
    } else if (bMouseValue>0) {                                                         //Check if mouse buttons are pressed 
        if(DEBUG_MODE) { printDebug(4); }
        pressGamepadButton(bMouseValue,1);
        delay(100);
        Joystick.SENDSTATE();     
    }else {
      if(DEBUG_MODE) { printDebug(5); }
      releaseGamepad();
    }
    mouse1.mouseDataClear();
  }
  
}

//***GET SIGN FUNCTION***//

int8_t sgn(int val) {
 if (val < 0) return -1;
 if (val==0) return 0;
 return 1;
}

//***CONVERT MOUSE X-Y VALUES TO JOYSTICK X-Y VALUES FUNCTION***//

int xyConvert(int inputVal,int inputMax ,int outputMax) {
   int outputVal = map(inputVal, 0, inputMax, 0, outputMax); 
   outputVal = constrain(outputVal,0,outputMax);
   outputVal = outputVal * sgn(inputVal);
   return outputVal;
}

//***MOVE GAMEPAD STICK FUNCTION***//

void moveGamepadStick(int xMouseVal,int yMouseVal)
{
    int xJoyVal = (X_JOY_MAX+1)/2;
    int yJoyVal = (Y_JOY_MAX+1)/2;
    if(abs(xMouseVal/yMouseVal)>XY_MOUSE_DELTA_RATIO) {                          //Ignore Y movement if movement on X is larger
      if(DEBUG_MODE) { printDebug(1); }
      xJoyVal = xyConvert(xMouseVal,X_MOUSE_MAX,X_JOY_MAX);
      Joystick.SETXAXIS(xJoyVal);
    } else if(abs(yMouseVal/xMouseVal)>YX_MOUSE_DELTA_RATIO) {                   //Ignore X movement if movement on Y is larger
      if(DEBUG_MODE) { printDebug(2); }
      yJoyVal = xyConvert(yMouseVal,Y_MOUSE_MAX,Y_JOY_MAX);
      Joystick.SETYAXIS(yJoyVal); 
    } else if (xMouseVal !=0 && yMouseVal !=0) {
      if(DEBUG_MODE) { printDebug(3); }
      xJoyVal = xyConvert(xMouseVal,X_MOUSE_MAX,X_JOY_MAX);
      yJoyVal = xyConvert(yMouseVal,Y_MOUSE_MAX,Y_JOY_MAX);  
      Joystick.SETXAXIS(xJoyVal);
      Joystick.SETYAXIS(yJoyVal);       
    } else {
      
    }
}

//***PRESS GAMEPAD BUTTON FUNCTION***//

void pressGamepadButton(int buttonNum,int buttonVal)
{
    if(buttonNum==1){
      Joystick.SETBUTTON(xacProperty[0].actionButton,buttonVal);
      
    } else if(buttonNum==2){
      Joystick.SETBUTTON(xacProperty[1].actionButton,buttonVal);
    } 
    Joystick.SENDSTATE();
}

//***CLEAR OR RELEASE GAMEPAD ACTION FUNCTION***//

void releaseGamepad()
{
    for (int i = 1; i <= 8; i++) {
      Joystick.SETBUTTON(i,0);
    }
    Joystick.SETXAXIS((X_JOY_MAX+1)/2);
    Joystick.SETYAXIS((X_JOY_MAX+1)/2);
    Joystick.SENDSTATE();
}

//***PRINT DEBUG FUNCTION***//

void printDebug(int debugNum)
{
    if(debugNum==1){
        Serial.print("mouseX = ");
        Serial.print(mouse1.getMouseX());
        Serial.println();      
    } else if(debugNum==2){
        Serial.print("mouseY = ");
        Serial.print(mouse1.getMouseY());
        Serial.println();
    } else if(debugNum==3){
        Serial.print("mouseX = ");
        Serial.print(mouse1.getMouseX());
        Serial.print(" ,mouseY = ");
        Serial.print(mouse1.getMouseY());
        Serial.println();
    } else if(debugNum==4){
        Serial.print("Mouse: buttons = ");
        Serial.print(mouse1.getButtons());
        Serial.println();
    } else if(debugNum==5){
        Serial.println("Clear");
    } 
}

bool OnReceiveHidData(uint32_t usage, const uint8_t *data, uint32_t len) {
  // Called for maybe both HIDS for rawhid basic test.  One is for the Teensy
  // to output to Serial. while still having Raw Hid...
  if (usage == 0xffc90004) {
    // Lets trim off trailing null characters.
    while ((len > 0) && (data[len - 1] == 0)) {
      len--;
    }
    if (len) {
      Serial.print("RawHid Serial: ");
      Serial.write(data, len);
    }
  } else {
    Serial.print("RawHID data: ");
    Serial.println(usage, HEX);
    while (len) {
      uint8_t cb = (len > 16) ? 16 : len;
      const uint8_t *p = data;
      uint8_t i;
      for (i = 0; i < cb; i++) {
        Serial.printf("%02x ", *p++);
      }
      Serial.print(": ");
      for (i = 0; i < cb; i++) {
        Serial.write(((*data >= ' ') && (*data <= '~')) ? *data : '.');
        data++;
      }
      len -= cb;
      Serial.println();
    }
  }

  return true;
}
