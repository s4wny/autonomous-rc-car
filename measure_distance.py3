import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BOARD)

TRIG = 40
ECHO = 38

GPIO.setup(TRIG, GPIO.OUT)
GPIO.output(TRIG, 0);

GPIO.setup(ECHO, GPIO.IN)

print("Starting...")


try:
    while True:
        GPIO.output(TRIG, 1)
        time.sleep(0.00001)
        GPIO.output(TRIG, 0)
        
        while GPIO.input(ECHO) == 0:
            pass
        
        start = time.time()
        
        while GPIO.input(ECHO) == 1:
            pass
        
        end      = time.time()
        duration = end-start
        distance = 170*duration

        print("distance = "+ str(distance))
        time.sleep(0.1); # minimum wait time allowed is 60ms, so use 100ms to be sure

except KeyboardInterrupt:
    print 'Interrupted, bai!'


GPIO.cleanup()