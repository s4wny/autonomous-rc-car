#define FORWARD 6
#define BACKWARD 7
#define LEFT 8
#define RIGHT 9
#define ON LOW
#define OFF HIGH

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins

  // Activate relay
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  // Turn off all relays
  for(int x = 2; x <= 9; x++) {
    pinMode(x, OUTPUT);
    digitalWrite(x, OFF);
  }
  
  digitalWrite(FORWARD, ON);
  delay(1000);
  digitalWrite(RIGHT, ON);
  delay(1000);
  digitalWrite(RIGHT, OFF);
  delay(1000);
  digitalWrite(LEFT, ON);
  delay(1000);
  digitalWrite(LEFT, OFF);
  delay(500);
  digitalWrite(FORWARD, OFF);
  delay(1000);

  digitalWrite(BACKWARD, ON);
  delay(1000);
  move(LEFT, 500);
  move(RIGHT, 500);
  move(LEFT, 500);
  move(RIGHT, 500);
  digitalWrite(BACKWARD, OFF);
  move(LEFT, 500);
  move(RIGHT, 500);
  
}

// the loop function runs over and over again forever
void loop() {

}

// 30ms seems to be the lowest reliable delay,
// lower than 30 will sometimes work but other times not.
// EDIT: Sometimes 30ms doesn't work either.
void move(int direction, int myDelay) {
  digitalWrite(direction, ON);
  delay(myDelay);
  digitalWrite(direction, OFF);
}

