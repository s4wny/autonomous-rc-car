# Autonomous RC car


## Stack

- Arduino UNO Rev 3
- [Relay ("RE-2578ay") for arduino](http://www.kjell.com/se/sortiment/el/elektronik/arduino/moduler/relamodul-for-arduino-4x2-p87913) by [lctech-inc.com](http://www.lctech-inc.com/Hardware/Detail.aspx?id=a6d5bfce-60df-4726-bf86-a86a04e907ad) 
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


### Full example

Connect the RE-2578ay to your arduino, 5V to 5V, GND to GND. IN1-IN8 to digitalPin 2-9. COM to digitalPin 10.

![re-2578ay-setup-with-arudino](re-2578ay-setup-with-arudino.jpg?raw=true)
([Image source](http://www.kjell.com/se/fraga-kjell/teman/kom-igang-med-arduino))

Then you can use this code to test that the relay work:
```
// the setup function runs once when you press reset or power the board
void setup() {
  // "activate" relay board
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  
  // Turn off all relays
  for(int x = 2; x <= 9; x++) {
    pinMode(x, OUTPUT);
    digitalWrite(x, HIGH);
  }

  // Turn on every relay, one by one with 1 seconds dealy between wach
  for(int x = 2; x <= 9; x++) {
    delay(1000);
    digitalWrite(x, LOW);
  }
}
```