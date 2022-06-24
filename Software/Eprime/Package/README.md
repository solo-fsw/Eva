<!-- About -->
## About Eva.epk3 package
The eva.epk3 package is developed for using the Eva response box with E-prime 3.<br>
With this package the intergration of an Eva box in your E-prime script is very simple.



<!-- Package calls -->
## Package Calls

| Function | Parameter(s) | Returns | Type
| ------------- | ------------- | ------------- | ------------- |
| Eva_Writemarker  | Marker value |   |int or byte| 
| Eva_SetActiveMode  |    | Status | string |
| Eva_SetPassiveMode  |    | Status | string |
| Eva_Ping  |    | Pong | string|
| Eva_MyInfo  |    | Device info | json string|
| Eva_GetVersion  |    | Version |string|
| Eva_GetSerial  |    | Serial no |String|
| Eva_GetDevice  |    | Device Type |string ("Eva")|
| Eva_GetMode  |    | Current Data mode |string|

<!-- Global variables -->
## Global Variables

| Variable | Type | description|
| ------------- | ------------- | ------------- | 
| SerialEva  | byte |   Com port used by Eva|  


## Use markers with Stimulus.Onsettime
Place this code in the E-prime Userscript
```
Sub SendMarker(c As context , x As Integer)
 Eva_WriteMarker x    
End Sub
```
Add the code and marker value to the required task event.

![Onsetmarker](https://user-images.githubusercontent.com/98744988/175535976-3020274b-d028-449e-a84f-acc6cafd22dc.gif)
