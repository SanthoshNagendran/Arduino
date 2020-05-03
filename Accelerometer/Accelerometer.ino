#include <Wire.h>
#include <VirtualWire.h>

char *controller;


#define accel_module (0x53)
byte values[6];
char output[512];
int a;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);

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
  pinMode(13,OUTPUT);
  pinMode(A0,INPUT);
vw_set_ptt_inverted(true); //
vw_set_tx_pin(12);
vw_setup(4000);// speed of data transfer Kbps
}

void loop() {
  // put your main code here, to run repeatedly:
  int xyzregister = 0x32;
  int x,y,z;

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
  
  a=digitalRead(A0);
  
if(y>200)
{
  if(x>120)
  {
    Serial.print("tone C");
    controller="A1"  ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
  tone(8,523,500);  
  }
  
}
else if(y>100)
{
  if(y<200)
  {
   if(x>150)
  {
    Serial.print("tone D");
    controller="A2"  ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
    tone(8,587,500);
  } 
  }
  
}
else if(y>0)
{
  if(y<100)
  {
    if(x>150)
    {
      Serial.print("tone E");
      controller="A3"  ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
      tone(8,659,500);
    }
  }
}
else if(y<0)
{
  if(x>150)
  {
    Serial.print("tone F");
    controller="A4"  ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
    tone(8,698,500);
  }
}
if(a==0)
{
  Serial.print("Sitch Pressed");
    controller="A5"  ;
vw_send((uint8_t *)controller, strlen(controller));
vw_wait_tx(); // Wait until the whole message is gone
a=1;
}
else
{
tone(8,0,200);
  
}
  delay(100);

}
