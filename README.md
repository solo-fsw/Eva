# Eva
Eva is a replacement of PST's SRBox (Serial Response Box) and the parallel port (LPT). It is used for sending or receiving markers. It also processes button responses, which are interpreted as keyboard buttons 1 - 8.

## Response Buttons
Responses from the response buttons are interpreted as keyboard events.
Button1 corresponds to keyboard 1, Button2 to keyboard 2 etc.
There are only events on button presses, not button releases.
Button markers for Biosemi are D8 for Button1, D9 for Button2 etc.
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
Active data mode is the normal operation mode, that is used most of the time.

***Active data Mode:***
All markers received over the serial usb port will be set on the Biosemi and Biopac connector.
Eva will set the value off the switches S0-S7 on the Biosemi and Biopac connector when pressing the Trigger button.

***Passive data mode:***
This mode can be handy when you still want to use the parallel port as marker source. The parallel port cable need to be connected to the Biopac connector. Received markers will be send to the Biosemi connector and will be shown on led D0-D7. 
Received markers on serial usb port and markers generated with the S0-S7 will be ignored.
Passive mode will be indicated by the passive red led.

## Switch between passive and active data mode
There are 3 possible options to switch between the active and passive data mode.
- Hold down the trigger button during powering up the SrBox2020, the data mode will be toggled and comfirmed by the led Passive.
- Place Eva in command mode and send an S for passive data mode or A for active data mode.
- When the box detects during boot an high level on bit2 (0x04) it will switch to passive data mode. 

Most parallel ports output bit2 high before initializing, if Eva detects this it’s most likely connected to an parallel port and will switch to input to protect itself.  
Passive mode will be indicated by the passive led.

## Data and command mode
Data mode is used for sending markers, all the data that is sent over the serial usb connection will be set on the output connectors Biosemi and Biopac.
To put the Eva in data mode open the comport @ 115200 baud, 8 bits, none parity, 1 stop bit (115200,8,N,1).

For switching to command mode open the comport @ 4800 baud (4800,8,N,1).
The red led Cmd will light up when it is in command mode.
 
## Command mode commands
- V - Gives info about Eva. Response is a Json String: *{"Version":"HW1:SW1.2","Serialno":"S01234","Device":"Eva"}*
- S - Puts Eva in passive data mode. Response: *Passive*
- A - Puts Eva in active data mode
- M - Returns the current state of the data mode. Response: *Active*
- P - Pings Eva to see if it’s alive. Response: *Pong,Eva*

Other commands will be ignored. Response: *Unknown command* 

Commands are case sensitive.

## How to use
- In Python, the [marker_management library](https://github.com/solo-fsw/python-markers) can be used. 
- In OpenSesame, the [markers plugin](https://github.com/solo-fsw/opensesame_plugin_markers/tree/main) can be used. 
- In E-Prime, the [Markers package](https://github.com/solo-fsw/eprime_package_markers) can be used.
- In MATLAB, see the [UsbParMarker documentation](https://github.com/solo-fsw/UsbParMarker/tree/main#matlab).
