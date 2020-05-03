int a,b,c,d;
void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
Serial.begin(9600);
}

void loop() {
 // Serial.begin(9600);
  // put your main code here, to run repeatedly:
  a=digitalRead(A0);
  b=digitalRead(A1);
  c=digitalRead(A2);
  d=digitalRead(A3);
digitalWrite(13,1);
Serial.println(a);
if(a==0)
{
tone(8,523);
}

else
{
  tone(8,-1);
  /////(10);
}

tone(8,523,300);
delay(500);
tone(8,523,300);
delay(500);
tone(8,587,500);
delay(500);
tone(8,523,300);
delay(500);
tone(8,698,300);
delay(500);
tone(8,659,300);
delay(500);

digitalWrite(13,0);
//tone(8,1000,1000);
Serial.println("LED OFF\n");
delay(500);
}
