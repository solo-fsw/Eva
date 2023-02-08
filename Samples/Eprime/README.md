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


## Add package to E-Prime task
Place the package file Eva.pkg3 preferably in the same location as the E-Prime task that uses the package. Add the package to the E-Prime task by going to Edit --> Experiment --> Packages --> Add. If the package is not listed here, go to Tools --> Options --> Packages. Here, the path where E-Prime searches for the package can be added. 

## Send markers
Place this code in the E-prime Userscript
```
Sub SendMarker(c As context , x As Integer)
 Eva_WriteMarker x    
End Sub
```

A marker can be sent by using an inline with the following code: 
```
SendMarker c, <marker value>
```
 
Alternatively, a marker can be associated with the on- and offset of objects in E-Prime. To implement this, use task events as shown below.


![Onsetmarker](https://user-images.githubusercontent.com/98744988/175535976-3020274b-d028-449e-a84f-acc6cafd22dc.gif)

## Use button boxes
When EVA is installed with button boxes, the buttons can be used as keyboard keys 1 - 8.
