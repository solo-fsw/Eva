void buttonChanged(int state) {   //Trigger Button handeling
  if (mode == ACTIVE) {
    if (state == 0) {              //Button pressed
      PORTD = i2cread();
    }
    else {
      PORTD = 0;
    }
  }
}


void debounceRespButtons() {            //Check if a response button is pressed, if yes then debounce the button(s).
  if (PINB != lastFlickerableState) {
    lastDebounceTime = millis();
    lastFlickerableState = PINB;
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (PINB != lastrespbutton) {
      Serial.write(PINB);
      for (uint8_t i = 0; i < 8; i++) {
        if (bitRead( PINB, i ) == 1) {
          Keyboard.print(char(49 + i));  //"A" +i
        }
      }
      lastrespbutton = PINB;
    }
  }
}

