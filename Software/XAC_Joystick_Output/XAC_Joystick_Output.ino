#define BEGIN()     useManualSend(true)
#define SETXAXIS(x) X(x)
#define SETYAXIS(x) Y(x)
#define SETBUTTON(button_num, value)    button(((button_num)+1), (value))
#define SENDSTATE() send_now()
    
void setup() {
  //Serial.begin(115200);
  //Serial.println("Joystick to XAC Testing");
  Joystick.BEGIN();
}

void loop() {
  Joystick.SETXAXIS(1023);
  Joystick.SENDSTATE();
  delay(500);
  Joystick.SETYAXIS(1023);
  Joystick.SENDSTATE();
  delay(500);
  Joystick.SETXAXIS(0);
  Joystick.SENDSTATE();
  delay(500);
  Joystick.SETYAXIS(0);
  Joystick.SENDSTATE();
  delay(500);
  Joystick.SETBUTTON(4,1);
  Joystick.SENDSTATE();
  delay(500);
  Joystick.SETBUTTON(4,0);
  Joystick.SENDSTATE();
  delay(500);
  /*
        Joystick.X(1023);
        Joystick.Y(0);
        Joystick.button(1,0);
        Joystick.send_now();
        delay(500);
        Joystick.X(0);
        Joystick.Y(0);
        Joystick.button(1,1);
        delay(500);
        Joystick.send_now();
        Wheelchair.X(1023);
        Wheelchair.Y(0);
        Wheelchair.button(1,0);
        Wheelchair.send_now();
        delay(1000);
        Wheelchair.X(0);
        Wheelchair.Y(0);
        Wheelchair.button(1,1);
        delay(1000);
        Wheelchair.send_now();
        */
        
}
