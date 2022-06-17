
#include "Box2020V1.h"



#undef TX_RX_LED_INIT  //DDRD |= (1<<5), DDRB |= (1<<0)
#undef TXLED0    //  PORTD |= (1<<5)
#undef TXLED1    //  PORTD &= ~(1<<5)
#undef RXLED0    //  PORTB |= (1<<0)
#undef RXLED1    //  PORTB &= ~(1<<0)

void setup() {
  lptconnected();           //Check if lpt cable from pc is connected to the Biopac (or Biosemi) connector
  //writeStringToEEPROM(10,"S00794");
  Serialno= readStringFromEEPROM(10);
  
  pinMode(STATUSLED1, OUTPUT);
  pinMode(STATUSLED2, OUTPUT);
  Serial.begin(115200);     // opens serial port, sets data rate to 115200 bps
  changemode();  //check if button is pressed during boot to change mode
  button.setCallback(buttonChanged);  //callback switch for marker sending
  DDRB = 0x00;           //PortB all pins input, Buttons
  i2cinit();
  Keyboard.begin();
}

void loop() {
  button.update();                  //scan Trigger button
  if (Serial.baud() == 115200) {    //data mode
    if (Serial.available() > 0) {
      PORTD = Serial.read();       //send marker to output port
    }
    digitalWrite(STATUSLED2, LOW);
  }
  else if (Serial.baud() == 4800) { //command mode
    digitalWrite(STATUSLED2, HIGH);
    if (Serial.available() > 0) {
      handlecommands();
    }
  }
  debounceRespButtons();
}

