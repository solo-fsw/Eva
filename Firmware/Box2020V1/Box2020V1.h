/* IMPORTANT NOTE
  TXLED must be disabled to prevent Interference with PORTD, done with #UNDEF
*/

/* IMPORTANT NOTE
  TXLED must be disabled to prevent Interference with the COL6, todo this change these 5 lines in the Arduino ..\variants\leonardo\pins_arduino.h file
  #define TX_RX_LED_INIT  //DDRD |= (1<<5), DDRB |= (1<<0)
  #define TXLED0    //  PORTD |= (1<<5)
  #define TXLED1    //  PORTD &= ~(1<<5)
  #define RXLED0    //  PORTB |= (1<<0)
  #define RXLED1    //  PORTB &= ~(1<<0)
*/

//20210501	1.0	Initial release
//20220211 	1.1 Changed DumpInfo to output Jsonstring
//20220617  1.2 Changed name Srbox2020 to Eva
//20220728  1.3 Responsebuton where responding slow after opening and closing the com port. This due some leftover Serial.write for debug purpose in debounceRespButtons()

//Hardware macros
#define BUTTON   A0    //PF7    *defines can be found in arduino\hardware\arduino\avr\variants\leonardo\pins_arduino.h* 
#define SDA_PORT PORTC   //C7
#define SDA_PIN 7
#define SCL_PORT PORTC  //C6
#define SCL_PIN 6
#define STATUSLED2 A3  //F4
#define STATUSLED1 A2  //F5

#define I2C_TIMEOUT 100
#define I2C_FASTMODE 1

#define STX 0x02 //start of text
#define ETX 0x03 //end of text
#define PING 81


#include <ButtonDebounce.h>
#include <SoftWire.h>  //Needs to be place below the i2c port defines
#include <avr/io.h>  //required for SoftWire
#include <EEPROM.h>
#include <Keyboard.h>

//Instance
ButtonDebounce button(BUTTON, 10);
SoftWire Wire = SoftWire();

//Globals
byte mode;
byte lastrespbutton =0;
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 1; //was 10 
byte lastFlickerableState = 0;
const String Version = "HW1:SW1.3";
const String Serialno;

//Enums
enum mode {
  ACTIVE,
  PASSIVE
};
