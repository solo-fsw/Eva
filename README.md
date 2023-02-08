# Eva

## Response Buttons
The responses from the response buttons will be a keyboard event.
For Button1 1, for button 2 2 etc.
There are only events on button press, not for button release.
Markers for Biosemi will be D8 for button1 , D9 for button 2 etc.
| Button | Keyboard event	| Biosemi marker |
| ------------- | ------------- | ------------- | 
| 1 |	1	| D8 |
| 2	| 2	| D9 |
| 3	| 3	| D10 |
| 4	| 4	| D11 |
| 5	| 5	| D12 |
| 6	| 6	| D13 |
| 7	| 7	| D14 |
| 8	| 8	| D15 |

## Passive/Active data mode
Eva can operate in passive or active data mode.
The main difference is that in active data mode the Biopac connector is **output** for markers. In passive data mode the Biopac connector is **input**.
Active data mode is the normal operation mode, most of the time used.

***Active data Mode:***
All markers received over the serial usb port will be set on the Biosemi and Biopac connector.
Eva will set the value off the switches S0-S7 on the Biosemi and Biopac connector when pressing the Trigger button.

***Passive data mode:***
This mode can be handy when you still want to use the parallel port as marker source. The parallel port cable need to be connected to the Biopac connector. Received markers will be send to the Biosemi connector and will be shown on led D0-D7. 
Received markers on serial usb port and markers generated with the S0-S7 will be ignored.
Passive mode will be indicated by the passive led.

## Switch between passive and active data mode
There are 3 possible options to switch between the active and passive data mode.
- Hold down the trigger button during powering up the SrBox2020, the data mode will be toggled and comfirmed by the led Passive.
- Place Eva in command mode and send an S for passive data mode or A for active data mode.
- When the box detects during boot an high level on bit2 (0x04) it will switch to passive data mode. 

Most parallel port will output bit2 high before initializing, if the SrBox202 will detect this it’s most likely connected to an parallel port and will switch to input to protect itself.  
Passive mode will be indicated by the passive led.

## Data and command mode
Eva works normally in data mode, all the data send over the serial usb connection will be set on the output connectors Biosemi and Biopac.

To put the Eva in data mode open the comport 115200 baud, 8 bits, none parity, 1 stop bit (115200,8,N,1).


For switching to command mode open the comport @ 4800 baud (4800,8,N,1).
The red led Cmd will light up when it is in command mode.
 
## Command mode commands
- V - Version will give info about Eva. Response Json String: *{"Version":"HW1:SW1.2","Serialno":"S01234","Device":"Eva"}*
- S – Will put the SrBox2020 in passive data mode. Response: *Passive*
- A – Will put the SRBox2020 in active data mode
- M - Will return the current state of the data mode. Response: *Active*
- P – Ping the SrBox2020 to see if it’s alive. Response: *Pong,Eva*


Other commands will be ignored. Response : Unknown command 

Commands are case sensitive.
