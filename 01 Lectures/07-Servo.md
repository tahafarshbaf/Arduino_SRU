# Servo
*Servo* motors are a special type of motor that don’t spin around in a circle, but 
move to a specific position and stay there until you tell them to move again. 
Servos usually only rotate 180 degrees (one half of a circle). 

Similar to the way you used pulses to PWM an LED in the Color Mixing Lamp Project, 
servo motors expect a number of pulses that tell them what angle to move to. The 
pulses always come at the same time intervals, but the width varies between 1000 
and 2000 microseconds. While it’s possible to write code to generate these pulses, 
the Arduino software comes with a library that allows you to easily control the motor


## Schematics
![servo](Images/servo.jpg)


> [!IMPORTANT]
> When a servo motor starts to move, it draws more current than 
if it were already in motion. This will cause a dip in the voltage 
on your board. By placing a 100uf capacitor across power and 
ground right next to the male headers  you can 
smooth out any voltage changes that may occur. You can also 
place a capacitor across the power and ground going into your 
potentiometer. These are called `decoupling capacitors` because 
they reduce, or decouple, changes caused by the components 
from the rest of the circuit. Be very careful to make sure you are 
connecting the cathode to ground (that’s the side with a black 
stripe down the side) and the anode to power. If you put the 
capacitors in backwards, they can explode.

## Code
```C++
#include <Servo.h>

Servo myServo;

int const potPin = A0; 
int potVal; 
int angle;

void setup() {
    myServo.attach(9);
    Serial.begin(9600);
    }
void loop() {
    potVal = analogRead(potPin); 
    Serial.print(“potVal: “); 
    Serial.print(potVal);
    angle = map(potVal, 0, 1023, 0, 179);
    Serial.print(“, angle: “); 
    Serial.println(angle); 
    myServo.write(angle);
    delay(15);
}
```