


void i2cinit() {                         //Reading the MCP23008 IO expander
  Wire.begin();                           //creates a Wire object
  Wire.beginTransmission(0x20);           //begins talking to the slave device
  Wire.write(0x00);                      //selects the IODIRA register
  Wire.write(11111111);                  //this sets the pins as inputs
  Wire.endTransmission();               //stops talking to device
}

byte i2cread() {
  Wire.beginTransmission(0x20);          //starts talking to slave device
  Wire.write(0x09);                     //selects the GPIO pins register
  Wire.endTransmission();               //stops talking to device
  Wire.requestFrom(0x20, 1);            // requests one byte of data from MCP
  //byte inputs = Wire.read();          // store the incoming byte into inputs
  return Wire.read();
}


void changemode() {                       //Change the operation mode when the marker button is pressed during boot
  mode = EEPROM.read(1);
  if (digitalRead(BUTTON) == LOW) {
    mode++;
    if (mode > 1) {
      mode = 0;
    }
    EEPROM.write(1, mode);
    setstatusled(mode);
    while (digitalRead(BUTTON) == LOW) {  //wait until button is released
    }
  }
  setmode();
}

void setmode() {
  mode = EEPROM.read(1);
  setstatusled(mode);
  if (mode == ACTIVE) {
    //while (!Serial);             // Leonardo: wait for serial monitor
    DDRD = 0xFF; //PortD all pins output
    PORTD = 0x00;
  }
  else if (mode == PASSIVE) {
    DDRD = 0x00; //PortD all pins input
  }
}

void lptconnected() {
  DDRD = 0x00;                      //PortD all pins input
  if (PIND == 0x04) {              //Bit 2 is high, default value from LPT port, so probarly LPT kabel form pc connected.
    EEPROM.write(1, PASSIVE);       //Set to passive mode
  }
}


void setstatusled(byte mode) {
  switch (mode) {
    case 0:
      digitalWrite(STATUSLED1, LOW);
      digitalWrite(STATUSLED2, LOW);
      break;
    case 1:
      digitalWrite(STATUSLED1, HIGH);
      digitalWrite(STATUSLED2, LOW);
      break;
    case 2:
      digitalWrite(STATUSLED1, LOW);
      digitalWrite(STATUSLED2, HIGH);
      break;
    case 3:
      digitalWrite(STATUSLED1, HIGH);
      digitalWrite(STATUSLED2, HIGH);
      break;
    default:
      break;
  }
}

void handlecommands() {
  switch (Serial.read()) {
    case 'V':
      DumpMyInfo();
      break;
    case 'S':
      Serial.println("Passive");
      EEPROM.write(1, PASSIVE);
      setmode();
      break;
    case 'A':
      Serial.println("Active");
      EEPROM.write(1, ACTIVE);
      setmode();
      break;
    case 'P':
      Serial.println("Pong,Box2020");
      break;

    default:
      Serial.println("Unknown command");
      break;
  }
}

//void DumpMyInfo() {
//  Serial.print("Version:");
//  Serial.print(Version);
//  Serial.print(",");
//  Serial.print("Serialno:");
//  Serial.print(Serialno);
//  Serial.print(",");
//  Serial.println("Device:Srbox2020");
  //Serial.write(ETX);
}

void DumpMyInfo() {
  Serial.print("{Version:\"");
  Serial.print(Version);
  Serial.print("\",");
  Serial.print("Serialno:\"");
  Serial.print(Serialno);
  Serial.print("\",");
  Serial.println("Device:\"Srbox2020\"}");
  //Serial.write(ETX);
}

void writeStringToEEPROM(int addrOffset, const String &strToWrite)
{
  byte len = strToWrite.length();
  EEPROM.write(addrOffset, len);
  for (int i = 0; i < len; i++)
  {
    EEPROM.write(addrOffset + 1 + i, strToWrite[i]);
  }
}

String readStringFromEEPROM(int addrOffset)
{
  int newStrLen = EEPROM.read(addrOffset);
  char data[newStrLen + 1];
  for (int i = 0; i < newStrLen; i++)
  {
    data[i] = EEPROM.read(addrOffset + 1 + i);
  }
  data[newStrLen] = '\0'; // the character may appear in a weird way, you should read: 'only one backslash and 0'
  return String(data);
}

