#include "USBHost_t36.h"


typedef struct { 
  long int keyboardNum;
  const char* keyboardAction;
  int keyboardCode;
  long int keyboardJoystickAction;
} keyboardStruct;


typedef struct { 
  long int specKeyboardNum;
  long int specKeyboardCode;
  String specKeyboardName;
  //const char* lowerChar;
  long int specKeyboardJoystickAction;
} specKeyboardStruct;

typedef struct { 
  long int miceAction;
  long int miceJoystickAction;
} miceActionStruct;


const keyboardStruct keyboardDictionary[] {
    {0," ",32,0},                        //Space
    {1,"!",33,0},                        //!
    {2,"\"",34,0},                       //"
    {3,"#",35,0},                        //#
    {4,"$",36,0},                        //$
    {5,"%",37,0},                        //%
    {6,"&",38,0},                        //&
    {7,"'",39,0},                        //'
    {8,"(",40,0},                        //(
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
    {32,"a",97,0},                         //a                                      
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
    {44,"m",109,5},                         //m
    {45,"n",110,0},                         //n
    {46,"o",111,0},                         //o
    {47,"p",112,0},                         //p
    {48,"q",113,0},                         //q
    {49,"r",114,0},                         //r
    {50,"s",115,0},                         //s
    {51,"t",116,0},                         //t
    {52,"u",117,0},                         //u
    {53,"v",118,0},                         //v
    {54,"w",119,0},                         //w
    {55,"x",120,0},                         //x
    {56,"y",121,0},                         //y
    {57,"z",122,0},                         //z
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
    {75," ",KEYD_UP,0},                         //UP
    {76," ",KEYD_DOWN,0},                         //DN
    {77," ",KEYD_LEFT,0},                         //LEFT
    {78," ",KEYD_RIGHT,0},                         //RIGHT
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
//KeyboardController keyboard2(myusb);
USBHIDParser hid1(myusb);
USBHIDParser hid2(myusb);
USBHIDParser hid3(myusb);
USBHIDParser hid4(myusb);
USBHIDParser hid5(myusb);
MouseController mouse1(myusb);
//JoystickController joystick1(myusb);
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



bool show_changed_only = false;

uint8_t joystick_left_trigger_value = 0;
uint8_t joystick_right_trigger_value = 0;
uint64_t joystick_full_notify_mask = (uint64_t) - 1;

int getJoystickButton(int code) {  
  int joystickOut = 0;
  //Search for Ascii code based on character number
  for(uint8_t j = 0; j < sizeof(keyboardDictionary)/sizeof(keyboardStruct); ++j) {
    if(code == keyboardDictionary[j].keyboardCode)
    {
      joystickOut= keyboardDictionary[j].keyboardJoystickAction;
    }
  }
  return joystickOut;
}

int getSpecJoystickButton(int code) {  
  int joystickOut = 0;
  //Search for Ascii code based on character number
  for(uint8_t j = 0; j < sizeof(specKeyboardDictionary)/sizeof(specKeyboardStruct); ++j) {
    if(code == specKeyboardDictionary[j].specKeyboardCode)
    {
      joystickOut= specKeyboardDictionary[j].specKeyboardJoystickAction;
    }
  }
  return joystickOut;
}

void setup()
{
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial.println("\n\nUSB Host Testing");
  Serial.println(sizeof(USBHub), DEC);
  myusb.begin();
  keyboard1.attachPress(OnPress);
  //keyboard2.attachPress(OnPress);
}


void loop()
{
  // check to see if the device list has changed:
  UpdateActiveDeviceInfo();

  myusb.Task();

  if (mouse1.available()) {
    Serial.print("Mouse: buttons = ");
    Serial.print(mouse1.getButtons());
    Serial.print(",  mouseX = ");
    Serial.print(mouse1.getMouseX());
    Serial.print(",  mouseY = ");
    Serial.print(mouse1.getMouseY());
    Serial.print(",  wheel = ");
    Serial.print(mouse1.getWheel());
    Serial.print(",  wheelH = ");
    Serial.print(mouse1.getWheelH());
    Serial.println();
    mouse1.mouseDataClear();
  }
}

void OnPress(int key)
{
  Serial.print("key: '");
  Serial.print(key); 
  Serial.print(" ,char key: '");
  Serial.print((char)key); 
  Serial.print(" ,XAC key: "); 
  Serial.print(getJoystickButton(key));
  Serial.print(" ,MOD: ");
  if (keyboard1) {
    Serial.print(keyboard1.getModifiers(), HEX);
    Serial.print(" OEM: ");
    Serial.print(keyboard1.getOemKey(), HEX);
    Serial.print(" LEDS: ");
    Serial.println(keyboard1.LEDS(), HEX);
    //} else {
    //Serial.print(keyboard2.getModifiers(), HEX);
    //Serial.print(" OEM: ");
    //Serial.print(keyboard2.getOemKey(), HEX);
    //Serial.print(" LEDS: ");
    //Serial.println(keyboard2.LEDS(), HEX);
  }

  //Serial.print("key ");
  //Serial.print((char)keyboard1.getKey());
  //Serial.print("  ");
  //Serial.print((char)keyboard2.getKey());
  //Serial.println();
}

//=============================================================================
// UpdateActiveDeviceInfo
//=============================================================================
void UpdateActiveDeviceInfo() {
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

        if (drivers[i] == &bluet) {
          const uint8_t *bdaddr = bluet.myBDAddr();
          // remember it...
          Serial.printf("  BDADDR: %x:%x:%x:%x:%x:%x\n", bdaddr[0], bdaddr[1], bdaddr[2], bdaddr[3], bdaddr[4], bdaddr[5]);
        }
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
  // Then Bluetooth devices
  for (uint8_t i = 0; i < CNT_BTHIDDEVICES; i++) {
    if (*bthiddrivers[i] != bthid_driver_active[i]) {
      if (bthid_driver_active[i]) {
        Serial.printf("*** BTHID Device %s - disconnected ***\n", bthid_driver_names[i]);
        bthid_driver_active[i] = false;
      } else {
        Serial.printf("*** BTHID Device %s - connected ***\n", bthid_driver_names[i]); Serial.flush();
        bthid_driver_active[i] = true;
        #if 0

        const uint8_t *psz = bthiddrivers[i]->manufacturer();
        if (psz && *psz) Serial.printf("  manufacturer: %s\n", psz);
        psz = bthiddrivers[i]->product();
        if (psz && *psz) Serial.printf("  product: %s\n", psz);
        psz = bthiddrivers[i]->serialNumber();
        if (psz && *psz) Serial.printf("  Serial: %s\n", psz);
    #endif  
      }
    }
  }
}
