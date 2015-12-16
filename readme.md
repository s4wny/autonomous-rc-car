# Autonomous RC car


## Stack

- Arduino UNO Rev 3
- [Relay for arduino](http://www.lctech-inc.com/Hardware/Detail.aspx?id=a6d5bfce-60df-4726-bf86-a86a04e907ad) by [lctech-inc.com](http://www.lctech-inc.com/Hardware/Detail.aspx?id=a6d5bfce-60df-4726-bf86-a86a04e907ad) ""
- HC-SR04 sensors
- A LEGO Dirt Crusher 8369


## Relay from lctech-inc "RE-2578ay"

It is hard to figure out how to use the RE-2578ay relay/circuit but when you do know it is really easy. 

You need to connect the COM pin to a digitalPin on your arduino, and set the pin to HIGH.

For example:

```
#define COM 10

void setup() {
  pinMode(COM, OUTPUT);
  digitalWrite(COM, HIGH);
}
```

Where the rest of the pins should go is easier to figure out:

IN1-IN8 should go to digitalPins. COM should also go to a digital pin (as I said above). GND goes to a ground pin on the arduino, which one doesn't matter. VCC goes to the 5V pin.