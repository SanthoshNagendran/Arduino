#include <Wire.h>

#define accel_module (0x53)
byte values[6];
char output[512];

const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance,Set_Value = 1;


void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Wire.begin();
Serial.begin(9600); // Starts the serial communication
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(0);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
}

void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
Set_Value = duration*0.034/2;

while(1)
{
  int xyzregister = 0x32;
  int x,y,z;
  int Diff;

  Wire.beginTransmission(accel_module);
  Wire.write(xyzregister);
  Wire.endTransmission();

  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module,6);

  int i =0;
  while(Wire.available()){
    values[i] = Wire.read();
    i++;
  }

  Wire.endTransmission();

  x = (((int)values[1]) << 8) | values[0];
  y = (((int)values[3]) << 8) | values[2];
  z = (((int)values[5]) << 8) | values[4];

  sprintf(output, "%d %d %d",x,y,z);
  Serial.print(output);
  Serial.print("\n");
  Serial.print(x);
  Serial.write(10);
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
Serial.println("x is ");
Serial.println(Set_Value);
if(Set_Value==0)
{
  Serial.print("bye bye set value is 0");
}
else
{
  Diff = Set_Value - distance;
  if(Diff>=0)
{
  if(Diff<=5)
  {
    if(x>150)
    {
      Serial.print("tone F");
      tone(8,698,500);
    }
  }
}
else if(Diff>=6)
{
  if(Diff<=10)
  {
    if(x>150)
    {
      Serial.print("tone E");
      tone(8,659,500);
    }
  }
}
else if(Diff>=11)
{
  if(Diff<=15)
  {
    if(x>150)
    {
      Serial.print("tone D");
      tone(8,587,500);
    }
  }
}
else if(Diff>=16)
{
  if(x>150)
  {
    Serial.print("tone C");
    tone(8,523,500);
  }
}
else if(Diff>=-5)
{
  if(Diff<0)
  {
    if(x>150)
    {
      Serial.print("tone G");
      tone(8,783,500);
    }
  }
}
else if(Diff>=-10)
{
  if(Diff<-5)
  {
    if(x>150)
    {
      Serial.print("tone A");
      tone(8,880,500);
    }
  }
}
else if(Diff<-10)
{
  if(x>150)
  {
    Serial.print("tone B");
    tone(8,987,500);
  }
}
else
  {
  tone(8,0,200);
  }
}


delay(100);
}

}
