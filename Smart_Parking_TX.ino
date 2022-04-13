#include <LoRa.h>
#define SS D8
#define RST D0
#define DIO1 D2
//String data = distanceCm;
const int trigPin = 5;
const int echoPin = 0;
const int trigPin1 = 2;//tx
const int echoPin1 = 10;//rx
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

long duration1;
float distanceCm1;
float distanceInch1;

String data = "0";
String data1 = "0";

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Sender Host");
  LoRa.setPins(SS, RST, DIO1);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa Error");
    delay(100);
    while (1);
  }
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
}
void loop()
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY/2;
  distanceInch = distanceCm * CM_TO_INCH;
//  Serial.print("Distance (cm): ");
 // Serial.println(distanceCm);
  delay(500);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distanceCm1 = duration1 * SOUND_VELOCITY/2;
  distanceInch1 = distanceCm1 * CM_TO_INCH;
if (distanceCm > 20)
{
  data = "0";
  }
else
  {
  data = "1";
  }

if (distanceCm1 > 20)
{
  data1 = "0";
  }
else
  {
  data1 = "1";
  }
  String alldata = String(data) + String(data1);  
  Serial.print("Sending Data: ");
  Serial.println(alldata);
  LoRa.beginPacket();
  LoRa.print(alldata);
  LoRa.endPacket();
}
