import RPi.GPIO as GPIO
import time

#### SETTINGS
FORWARD=37
BACKWARD=40
RIGHT=38
LEFT=40

S1TRIG = 36
S1ECHO = 33
#### /settings



GPIO.setmode(GPIO.BOARD)

# Initialize ultrasonic sensors
GPIO.setup(S1TRIG, GPIO.OUT)
GPIO.output(S1TRIG, 0)
GPIO.setup(S1ECHO, GPIO.IN)


# Initialize car control pins
GPIO.setup(FORWARD, GPIO.OUT)
GPIO.output(FORWARD, 1)

GPIO.setup(BACKWARD, GPIO.OUT)
GPIO.output(BACKWARD, 1)

GPIO.setup(RIGHT, GPIO.OUT)
GPIO.output(RIGHT, 1)

GPIO.setup(LEFT, GPIO.OUT)
GPIO.output(LEFT, 1)


#########

print("Starting...")



def distance(trig, echo):
    GPIO.output(trig, 1)
    time.sleep(0.00001)
    GPIO.output(trig, 0)
    
    while GPIO.input(echo) == 0:
        pass
    
    start = time.time()
    
    while GPIO.input(echo) == 1:
        pass
    
    end      = time.time()
    duration = end-start
    distance = 170*duration

    # minimum wait time allowed is 60ms, so use 100ms to be sure
    time.sleep(0.1)

    return distance
 

try:
    while True:
        distance = distance(S1TRIG, S1ECHO)
        print("distance = "+ str(distance))

except KeyboardInterrupt:
    print 'Interrupted, bai!'


GPIO.cleanup()