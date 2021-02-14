#  Teensy-XAC-Converter 
The goal of this project is to create a device which converts variety of intputs as of Bluetooth/USB HID profiles to USB HID joystick profile.  This will allow end users use other inputs such as keyboard and mouse in addition to joystick with their Xbox Adaptive Controller. 

This project is in development process at the moment.

We now go over the hardware and software requirements.

## Hardware Requirements

### Bluetooth Wheelchair Joystick Hardware 

  1. [Teensy 3.6](https://www.pjrc.com/store/teensy36.html) x 1
  2. [USB Host Cable For Teensy 3.6](https://www.pjrc.com/store/cable_usb_host_t36.html) x 1
  3. [Kinivo BTD-400 Bluetooth 4.0](https://www.amazon.com/gp/product/B007Q45EF4) or [TechKey 4.0 EDR](https://www.amazon.com/gp/product/B07J5WFPXX/) or [ZEXMTE Bluetooth USB Adapter CSR 4.0](https://www.amazon.com/gp/product/B0775YF36R) x 1
  4. Micro SD card x 1 (optional)
  5. [SparkFun Qwiic Shield for Teensy](https://www.sparkfun.com/products/17156) x 1 (optional)
  6. [SparkFun Qwiic Button](https://www.sparkfun.com/products/15932) x 1 (optional)
  7. [SparkFun Micro OLED Breakout (Qwiic)](https://www.sparkfun.com/products/14532) x 1 (optional)

# Hardware Assembly Instructions   

  1. Solder a 5 pin male connector to Teensy 3.6 board.

  2. Connect the USB Host Cable to Teensy 3.6 board via 5 pin header.
  
  3. Plug the Bluetooth USB Dongle to the USB plug connector of USB Host cable.
  
  4. Solder the SparkFun Qwiic Shield for Teensy and connect SparkFun Qwiic Button if you need to manually connect or disconnect the bluetooth connection 
  
  
# Software requirements  

  1. Install latest version of Arduino IDE according to the official documents on [arduino.cc](https://www.arduino.cc/en/software).
  
  2. Install latest version of Teensyduino software add-on for the Arduino according to the official documents on [pjrc.com/teensy/teensyduino.html](https://www.pjrc.com/teensy/teensyduino.html).
  
  3. Make sure you check "USBHost_t36" library is checked and installed during Teensyduino installation 
  
 # Software installation 
 
1.	Make Core changes to Arduino Teensy core file. This can be done manually using following instructions or simply replacing the files with those included in [joystick_teensy_2.0_20201230.zip](https://github.com/milador/XAC-Input-Converter/raw/main/Software/Library/joystick_teensy_2.0_20201230.zip).

  1.1. Add "Joystick" and "Joystick + Serial" USB types to boards.txt
    
   1.1.1 Open boards.txt file under your Arduino installation path with your favorite text editor (example path: C:\Program Files (x86)\Arduino\hardware\teensy\avr)
  
   1.1.2 Add following lines after teensy36.menu.usb.everything.build.usbtype=USB_EVERYTHING:
   
    teensy36.menu.usb.joystick=Joystick
    teensy36.menu.usb.joystick.build.usbtype=USB_JOYSTICK
    teensy36.menu.usb.joystick.fake_serial=teensy_gateway
    teensy36.menu.usb.joystickserial=Joystick + Serial
    teensy36.menu.usb.joystickserial.build.usbtype=USB_SERIAL_JOYSTICK

   so it will be:
   
    teensy36.menu.usb.joystick=Joystick
    teensy36.menu.usb.joystick.build.usbtype=USB_JOYSTICK
    teensy36.menu.usb.joystick.fake_serial=teensy_gateway
    teensy36.menu.usb.joystickserial=Joystick + Serial
    teensy36.menu.usb.joystickserial.build.usbtype=USB_SERIAL_JOYSTICK   

  1.2.	Update teensy 3.6 core files under your Arduino installation path with your favorite text editor (example path: C:\Program Files (x86)\Arduino\hardware\teensy\avr\cores\teensy3)

   1.2.1 Update yield.cpp file under your Arduino installation path with your favorite text editor (example path: C:\Program Files (x86)\Arduino\hardware\teensy\avr\cores\teensy3)
   
    	// USB Serail - Add hack to minimize impact...
      if (yield_active_check_flags & YIELD_CHECK_USB_SERIAL) {
        if (Serial.available()) serialEvent();
        if (_serialEvent_default) yield_active_check_flags &= ~YIELD_CHECK_USB_SERIAL;
      }
      // Current workaround until integrate with EventResponder.
      
   to
      
    		// USB Serail - Add hack to minimize impact...
	      if (yield_active_check_flags & YIELD_CHECK_USB_SERIAL) {
        #if !defined(USB_JOYSTICK)
          if (Serial.available()) serialEvent();
        #endif
          if (Serial1.available()) serialEvent1();
          if (Serial2.available()) serialEvent2();
          if (Serial3.available()) serialEvent3();
        #ifdef HAS_KINETISK_UART3
          if (Serial4.available()) serialEvent4();
        #endif
        #ifdef HAS_KINETISK_UART4
          if (Serial5.available()) serialEvent5();
        #endif
        #if defined(HAS_KINETISK_UART5) || defined (HAS_KINETISK_LPUART0)
          if (Serial6.available()) serialEvent6();
        #endif
            if (_serialEvent_default) yield_active_check_flags &= ~YIELD_CHECK_USB_SERIAL;
          }
          // Current workaround until integrate with EventResponder.   
  
   1.2.2 Add USB_JOYSTICK and USB_SERIAL_JOYSTICK descriptors to usb_desc.h file after USB_KEYBOARDONLY under your Arduino installation path with your favorite text editor (example path: C:\Program Files (x86)\Arduino\hardware\teensy\avr\cores\teensy3)
   
        #elif defined(USB_JOYSTICK)
          #define VENDOR_ID		0x16C0
          #define PRODUCT_ID		0x048B
          #define MANUFACTURER_NAME	{'T','e','e','n','s','y','d','u','i','n','o'}
          #define MANUFACTURER_NAME_LEN	11
          #define PRODUCT_NAME		{'J','o','y','s','t','i','c','k'}
          #define PRODUCT_NAME_LEN	8
          #define EP0_SIZE		64
          #define NUM_ENDPOINTS         1
          #define NUM_USB_BUFFERS	14
          #define NUM_INTERFACE         1
          #define JOYSTICK_INTERFACE    0	// Joystick
          #define JOYSTICK_ENDPOINT     1
          #define JOYSTICK_SIZE         12
          #define JOYSTICK_INTERVAL     1
          #define ENDPOINT1_CONFIG      ENDPOINT_TRANSMIT_ONLY

        #elif defined(USB_SERIAL_JOYSTICK)
          #define VENDOR_ID		0x16C0
          #define PRODUCT_ID		0x048C
          #define MANUFACTURER_NAME	{'T','e','e','n','s','y','d','u','i','n','o'}
          #define MANUFACTURER_NAME_LEN	11
          #define PRODUCT_NAME		{'S','e','r','i','a','l','/','J','o','y','s','t','i','c','k'}
          #define PRODUCT_NAME_LEN	15
          #define EP0_SIZE		64
          #define NUM_ENDPOINTS         5
          #define NUM_USB_BUFFERS	14
          #define NUM_INTERFACE         3
          #define CDC_IAD_DESCRIPTOR	1
          #define CDC_STATUS_INTERFACE	0
          #define CDC_DATA_INTERFACE	1
          #define CDC_ACM_ENDPOINT	2
          #define CDC_RX_ENDPOINT       3
          #define CDC_TX_ENDPOINT       4
          #define CDC_ACM_SIZE          16
          #define CDC_RX_SIZE           64
          #define CDC_TX_SIZE           64
          #define JOYSTICK_INTERFACE    2	// Joystick
          #define JOYSTICK_ENDPOINT     1
          #define JOYSTICK_SIZE         12
          #define JOYSTICK_INTERVAL     1
          #define ENDPOINT1_CONFIG      ENDPOINT_TRANSMIT_ONLY
          #define ENDPOINT2_CONFIG	ENDPOINT_TRANSMIT_ONLY
          #define ENDPOINT3_CONFIG	ENDPOINT_RECEIVE_ONLY
          #define ENDPOINT4_CONFIG	ENDPOINT_TRANSMIT_ONLY
          
   1.2.3 Add JOYSTICK_INTERFACE case to usb_dev.c file under your Arduino installation path with your favorite text editor. (example path: C:\Program Files (x86)\Arduino\hardware\teensy\avr\cores\teensy3) Change following:
   
    // TODO: this does not work... why?
      #if defined(SEREMU_INTERFACE) || defined(KEYBOARD_INTERFACE)
          case 0x0921: // HID SET_REPORT
          //serial_print(":)\n");
          return;
          case 0x0A21: // HID SET_IDLE
          break;
          // case 0xC940:
      #endif
      
   to 
   
    // TODO: this does not work... why?
    #if defined(SEREMU_INTERFACE) || defined(KEYBOARD_INTERFACE) || defined(JOYSTICK_INTERFACE)
        case 0x0921: // HID SET_REPORT
        //serial_print(":)\n");
        return;
        case 0x0A21: // HID SET_IDLE
        break;
        // case 0xC940:
    #endif
    
2.	Comment out serial prints which is on by default in keyboard.cpp file (line 558) from USBHost_t36 Teensy library. This can be done manually using following instructions or simply replacing the keyboard.cpp file with following [keyboard.cpp](https://raw.githubusercontent.com/milador/XAC-Input-Converter/main/Software/Library/USBHost_t36/keyboard.cpp?token=ABFGPIOBQELNONIQXOIFGC276KIE6) file. This file can be found in USBHost_t36 Teensy library installation path. (example path: C:\Program Files (x86)\Arduino\hardware\teensy\avr\libraries\USBHost_t36) 

        //USBHDBGSerial.printf("KeyboardController::process_bluetooth_HID_data\n");
        
 3.	Upload main software to your Teensy 3.6 board. The following software are available:
 
  3.1 [BTKeyboardToGamepad.ino](https://raw.githubusercontent.com/milador/Teensy-XAC-Converter/main/Software/Bluetooth/BTKeyboardToGamepad/BTKeyboardToGamepad.ino?token=ABFGPIOZUL4IACG56LDRMBLAFC7Y2) : Bluetooth Keyboard to USB Gamepad 
  
  3.2 [BTMouseToGamepad.ino](https://raw.githubusercontent.com/milador/Teensy-XAC-Converter/main/Software/Bluetooth/BTMouseToGamepad/BTMouseToGamepad.ino?token=ABFGPIJNWXBODMVGF6PHIL3AFC76G) : Bluetooth Mouse to USB Gamepad 

# Usage

1. Open [BTKeyboardToGamepad.ino](https://raw.githubusercontent.com/milador/Teensy-XAC-Converter/main/Software/Bluetooth/BTKeyboardToGamepad/BTKeyboardToGamepad.ino?token=ABFGPIOZUL4IACG56LDRMBLAFC7Y2) or [BTMouseToGamepad.ino](https://raw.githubusercontent.com/milador/Teensy-XAC-Converter/main/Software/Bluetooth/BTMouseToGamepad/BTMouseToGamepad.ino?token=ABFGPIJNWXBODMVGF6PHIL3AFC76G) with Arduino IDE.

2. Select Tools > Boards > Teensy 3.6

3. Select Tools > USB Type > Joystick + Serial

4. Verify and Upload the code to Teensy 3.6 using Arduino IDE

5. Connect and Power Teensy 3.6 by connecting it through main micro USB to your XAC

6. Turn on your Bluetooth Keyboard or Mice and press Connect/Pair button

7. The led on your keyboard or mice will initially blink and then stay on once it's paird.

8. You will need to pair the mice or keyboard for every usage at the moment. Ultimately, you can skip pairing for every usage by commenting and uncommenting following lines:

		// BluetoothController bluet(myusb, true, "0000");   // Version does pairing to device
		//BluetoothController bluet(myusb);   // version assumes it already was paired
		
# Tested Devices 

 <table style="width:100%">
  <tr>
    <th>Device Name</th>
    <th>Purchase Link</th>
    <th>Type</th>
  </tr>
    <tr>
    <td>Logitech Bluetooth Mouse M557</td>
    <td>https://www.amazon.ca/gp/product/B00JUHDYSO</td>
    <td>BT Mice</td>
  </tr>
  <tr>
    <td>Rii i8+ Mini Bluetooth Keyboard</td>
    <td>https://www.amazon.ca/Rii-Bluetooth-Touchpad＆QWERTY-Smartphones-Raspberry/dp/B00JO80LVW</td>
    <td>BT Keyboard</td>
  </tr>
</table>
