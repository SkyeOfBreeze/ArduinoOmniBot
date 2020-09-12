Work in progress, but movement should work correctly. Does not currently accept commands

Made for Platform.IO, but may work on Arduino IDE with little modifications
3 Omni Wheel Setup,  120 degrees apart. Can be scaled to a different setup as well.
Wheel positions

```

  B   A
   \ /
    |
    C

```
 
Coordinate system (Degrees)

```
      90
      |
180 -- -- 0
      |
     270
```

Wheel Axle Directions (Degrees)

```
A: 30 degrees
B: 150 degrees
C: 270 degrees
```

Forward Direction:
90 degrees OR pi/2 radians
Wheel directions:

```
 
   A
 (+)
   \
   (-)

   B
   (-)
   /
 (+)    
    
   C
(-)-(+)
```

Forms of control (a byte is assumed here to be sent as -100 to 100 unless otherwise specified):

- 1 Joystick. Variable -1 to 1 on X and Y axis. Sent as packet(0x01, X(byte), Y(byte), /r, /n)

- WSAD. Hardcoded -1 to 1 in X and Y axis, with mixing if multiple are pressed (Sent as packet(0x02, char, /r,/n))

- STOP PACKET: packet(0x00, /r, /n)

- RAW: Raw motor control. Value range, -1 to 1, translated from -100 to 100 via packet(0x03, A(byte), B(byte), C(byte), /r, /n)

Servo Pins: 

```
A: D10
B: D11
C: D12
```

NOTE: any speed calculations for wheels are done in radians