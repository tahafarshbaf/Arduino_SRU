# Potentiometer

$$
R = \frac{\rho L}{A}
$$


## Components


## Schematic
![po](Images/pot.jpg)



## Code

```C++
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int Potentiometer = analogRead(A0);
  Potentiometer = map(Potentiometer, 0, 1023, 0, 100);
  Serial.print("Rotation percentage ");
  Serial.println(Potentiometer);
}
```




