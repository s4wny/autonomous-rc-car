/*
 * Car movement
 */
#define FORWARD 6
#define BACKWARD 7
#define LEFT 8
#define RIGHT 9

/*
 * Relay on and off
 */
#define ON LOW
#define OFF HIGH

/*
 * Sensors
 *
 * If you add a sensor you also need
 * to initialize it in `initializeSensors()`
 */
#define FRONT_SENSOR_ECHO 4
#define FRONT_SENSOR_TRIG 5

#define LEFT_SENSOR_ECHO 11
#define LEFT_SENSOR_TRIG 12

#define RIGHT_SENSOR_ECHO 3
#define RIGHT_SENSOR_TRIG 2


/**
 * Time between each new movement of the car (in milli seconds)
 * Gives a human time to catch the car / prevent it from crashing / diving down into an abyss
 * or something dangerous.
 *
 * Also important to create a delay to ensure that the ultrasonic sensors
 * do not send out a new sonic wave before the previous one has returned/vanished 
 * Should probably be atleast 100 ms
 */
#define DELAY_BETWEEN_EACH_STEP 1000


/**
 * Movement time in milliseconds, a higher number equals faster movement but also
 * makes it more likely that the car crash into something.
 * 
 * The minimum movementTime is around 30ms. Under that it is likely that the signal
 * is to short for the car to notice/the RC control to send out any signal.
 *
 * 100 ms is a pretty high value and will result in a realy fast car.
 */
#define CAR_SPEED 40


/**
 * The setup function runs once when you press reset or power the board
 */
void setup() {
  initializeSerial();
  initializeRelayCircuit();
  initializeSensors();

  Serial.println("Swag!");
}


/**
 * The Loop
 */
void loop() {
  delay(DELAY_BETWEEN_EACH_STEP);
   
  long dist_front = getDistance(FRONT_SENSOR_TRIG, FRONT_SENSOR_ECHO);  
  long dist_left  = getDistance(LEFT_SENSOR_TRIG, LEFT_SENSOR_ECHO);  
  long dist_right = getDistance(RIGHT_SENSOR_TRIG, RIGHT_SENSOR_ECHO);  

  Serial.println(String(dist_right) +", "+ String(dist_front) +", "+ String(dist_left));

  theAlgorithm(dist_front, dist_left, dist_right);
}


/**
 * The Algorithm that drives the car.
 * 
 * Current algorithm in use:
 *   [1]: Drive if nothing is in front of the car.
 *     [1.1]: If something is near the left side while driving forward, turn right
 *            until something isn't near the left side
 *     [1.2]: If something is near the right side while driving forward, turn left
 *            until something isn't near the right side
 *   [2]: If something is in front of the car, reverse and turn to the direction
 *        which has most space.
 *
 * TODO:
 *   1. If the distance to the right/left is >100 turn into that direction.
 *   2. 
 * 
 * Ideas:
 *   1. Call this function recursively and try to guess the new values of dist_*
 *   2. Keep a log of all dist_* and somehow try to calculate/create a 2D map of
 *      where the car has been, and maybe where the car is located currently.
 */
void theAlgorithm(long dist_front, long dist_left, long dist_right) {
  bool wheelTurned = false;
  
  // [1]
  if(dist_front > 40) {
    // [1.1]
    if(dist_left < 20) {
      turnWheel(RIGHT);
      wheelTurned = true;
    }

    // [1.2]
    if(dist_right < 20) {
      turnWheel(LEFT);
      wheelTurned = true;
    }
  
    digitalWrite(FORWARD, ON);

    // Need extra time if wheels are turned, else it wont move forward at all
    if(wheelTurned) {
      delay(70);
    }
  }
  // [2]
  else {
    if(dist_left > dist_right) {
      turnWheel(RIGHT);
    }
    else {
      turnWheel(LEFT);
    }

    digitalWrite(BACKWARD, ON);
    delay(70); //extra time
  }

  delay(CAR_SPEED);
  stopCar();
}


/**
 * 
 */
void turnWheel(int direction) {
  digitalWrite(direction, ON);

  // Turn the wheels fully before starting to move the car
  delay(300);
}


/**
 * Stop the car (turn of the engine and reset the servo to 0 deg)
 */
void stopCar() {
  digitalWrite(BACKWARD, OFF);
  digitalWrite(FORWARD, OFF);
  digitalWrite(RIGHT, OFF);
  digitalWrite(LEFT, OFF);
}


/**
 * Initializes the relay circuit
 */
void initializeRelayCircuit() {
  // Activate relay
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  // Turn off all relays
  for(int x = 6; x <= 9; x++) {
    pinMode(x, OUTPUT);
    digitalWrite(x, OFF);
  }
}


/**
 * Initilaze the ultrasonic sensors
 */
void initializeSensors() {
  pinMode(FRONT_SENSOR_TRIG, OUTPUT);
  pinMode(FRONT_SENSOR_ECHO, INPUT);
  digitalWrite(FRONT_SENSOR_TRIG, LOW);

  pinMode(RIGHT_SENSOR_TRIG, OUTPUT);
  pinMode(RIGHT_SENSOR_ECHO, INPUT);
  digitalWrite(RIGHT_SENSOR_TRIG, LOW);

  pinMode(LEFT_SENSOR_TRIG, OUTPUT);
  pinMode(LEFT_SENSOR_ECHO, INPUT);
  digitalWrite(LEFT_SENSOR_TRIG, LOW);
}


/**
 * Initialize serial port,
 * required for Serial.println()
 */
void initializeSerial() {
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
}


/**
 * Get the distance to the nearest object in front
 * of the sensor.
 *
 * @return distance in cm
 */
long getDistance(int trig, int echo) {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH); // todo implement max range
  long distance = duration/58.2;

  return distance;
}


/**
 * Move the car
 * 
 * 30ms seems to be the lowest reliable delay,
 * lower than 30 will sometimes work but other times not.
 * EDIT: Sometimes 30ms doesn't work either.
 */
void move(int direction, int myDelay) {
  digitalWrite(direction, ON);
  delay(myDelay);
  digitalWrite(direction, OFF);
}
