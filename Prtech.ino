// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  11  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     12  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing hahahasonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo leftW;
Servo rightW;
Servo attach;
const int buttonPin = 4;
const int reedPin = 13;
int buttonState = 0;
int magnetState = 0;
int magnetCounter = 0;
int runCount = 0;

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  leftW.attach(10);
  leftW.write(90);
  rightW.attach(9);
  rightW.write(90);
  attach.write(10);
  attach.write(90);

  pinMode(buttonPin, INPUT);
  pinMode(reedPin, INPUT);
}

void stop() {
  leftW.write(90);
  rightW.write(90);
}

void forward() {
  leftW.write(15);
  rightW.write(130);
}

void backup() {
  rightW.write(20);
  leftW.write(130);
}

void run() {
   delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int hahahauS = hahahasonar.ping(); // Send ping, get ping time in microseconds (hahahauS).
  //Serial.print("Ping: ");
  int distance = hahahauS/US_ROUNDTRIP_CM;
  Serial.print(distance); // Convert ping time to distance in cm and print result (0 = outside set distance range)
 // Serial.println("cm");
  if (distance > 5) {
    forward();
   
  } else {
     stop();
    delay(1000);
    backup();
    delay(1000);
  }
}

void loop() {
  buttonState = digitalRead(buttonPin);
  magnetState = digitalRead(reedPin);
  if (buttonState == HIGH) {
    if (runCount == 0) {
      forward();
      delay(4500);
      stop();
    }
      if (magnetState == HIGH) {
     run();
     if (magnetCounter == 0) {
       stop();
         attach.write(130);
         delay(500);
         attach.write(90);
         magnetCounter = 1;
     }
   } else {
     run();
     magnetCounter = 0;
   }
    run();
    Serial.println("High");
    runCount++;
  } else {
    stop();
     Serial.println("Low");
     runCount = 0;
  }

}

  // if (magnetState == HIGH) {
    // run();
     //if (magnetCounter == 0) {
       //stop();
         //attach.write(130);
         //delay(500);
         //attach.write(90);
         //magnetCounter = 1;
     //}
   //} else {
     //run();
     //magnetCounter = 0;
   //}