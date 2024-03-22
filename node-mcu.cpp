#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//static const int RXPin = 4, TXPin = 5;   // GPIO 4=D1(conneect Tx of GPS) and GPIO 5=D2(Connect Rx of GPS)
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800

TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget

SoftwareSerial ss(4, 5);  // The serial connection to the GPS device

BlynkTimer timer;

float spd;       //Variable  to store the speed
float sats;      //Variable to store no. of satellites response
String bearing;  //Variable to store orientation or direction of GPS

char auth[] = "gBFSTU5dbhuuefZpRsIdX80WZNRDpeh1";              // Project authentication key
char ssid[] = "moto";                                       // Name of network (HotSpot or Router name)
char pass[] = "hellomoto";                                      // Corresponding Password

//unsigned int move_index;         // moving index, to be used later
unsigned int move_index = 1;       // fixed location for now
  void setup()
{
  Serial.begin(115200);
  Serial.println();
  ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once
}
void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
      Blynk.virtualWrite(V4, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected
  }
}
void loop()
{
 
    if (ss.available() > 0) 
    
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))
        displayInfo();
  
  Blynk.run();
  timer.run();
}
void displayInfo()
{ 
if (gps.location.isValid() ) 
  {
     float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng());
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V1, String(latitude, 6));   
    Blynk.virtualWrite(V2, String(longitude, 6));  
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    spd = gps.speed.kmph();               //get speed
       Blynk.virtualWrite(V3, spd);
       sats = gps.satellites.value();    //get number of satellites
       Blynk.virtualWrite(V4, sats);
       bearing = TinyGPSPlus::cardinal(gps.course.value()); // get the direction
       Blynk.virtualWrite(V5, bearing);                 
  }
  else
//void disp()
{
    Blynk.virtualWrite(V1, "----");   
    Blynk.virtualWrite(V2, "----");
    Blynk.virtualWrite(V3, "----");   
    Blynk.virtualWrite(V4, "No Satellite(s) in Range");
    Blynk.virtualWrite(V5, "----"); 
}
Serial.println();    }
Source code of ultrasonic sensor:
#include <LiquidCrystal.h>
#define trigPin 8
#define echoPin 9
#define buzrPin 13

long duration, distance;

void check_distance()
  {  
    delay(5);                       
    digitalWrite(trigPin, LOW);  
    delayMicroseconds(2); 
  
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
  
    digitalWrite(trigPin, LOW);
  
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2) / 29.1;
    
    if(distance<50)
      {
            digitalWrite(buzrPin,HIGH);
            digitalWrite(vibrPin,HIGH);
            delay(50); 
            
            digitalWrite(buzrPin,LOW);
            digitalWrite(vibrPin,LOW);
            delay(50);        
      }

    else
      {
            digitalWrite(buzrPin,LOW);
            digitalWrite(vibrPin,LOW);
      }
  }
