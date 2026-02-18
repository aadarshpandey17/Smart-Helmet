#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>
#define MQ3pin 0
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
float sensorValue = analogRead(MQ3pin);
SoftwareSerial mySerial(9, 10);
char msg;
char call;
int relay = 8; // Relay
int vs =7; // vibration sensor
int buzz = 6; //Buzzer
int sensorPin = A0; // Analog input pin connected to the sensor
int alcoholValue;
float longitude= 18.8941;
float  latitude =73.1768;
long vibration(){
  long measurement=pulseIn (vs, HIGH,5000);  //wait for the pin to get HIGH and returns measurement
  return measurement;
}



void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  pinMode(relay, OUTPUT);
  pinMode(vs, INPUT); 
  pinMode (buzz, OUTPUT); 
  delay(100);
}

void loop()
{  
  long measurement =vibration();
  alcoholValue = analogRead(sensorPin); // Read analog value from sensor
  
  Serial.println(alcoholValue);
  sensors_event_t event;
  accel.getEvent(&event);
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");
  float speed = sqrt(pow(event.acceleration.x, 2) + pow(event.acceleration.y, 2) + pow(event.acceleration.z, 2));
  Serial.print("Speed: "); Serial.println(speed);
  delay(1000);
  if ( measurement>50)
  {mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918308164701\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Accident Detected");// The SMS text you want to send
  mySerial.print("https://www.google.com/maps/search/?api=1&query=");
  mySerial.print(longitude);
  mySerial.print(",");
  mySerial.print(latitude);
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  }
  if ( alcoholValue> 200)
  {mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918308164701\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Alcohol Detected");// The SMS text you want to send
  mySerial.print("https://www.google.com/maps/search/?api=1&query=");
  mySerial.print(longitude);
  mySerial.print(",");
  mySerial.print(latitude);
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
    }
  if ( speed> 50)
  {mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+918308164701\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("OverSpeed Detected");// The SMS text you want to send
  mySerial.print("https://www.google.com/maps/search/?api=1&query=");
  mySerial.print(longitude);
  mySerial.print(",");
  mySerial.print(latitude);
  delay(100);
  
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
    }
  
}
