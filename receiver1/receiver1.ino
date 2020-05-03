//simple Tx on pin D12
//Written By : Mohannad Rawashdeh
// 3:00pm , 13/6/2013
//http://www.genotronex.com/
//..................................
#include <VirtualWire.h>


unsigned long timeC1,timeC2,timeC3,timeD1,timeD2,timeD3,timeE1,timeE2,timeE3,timeF1,timeF2,timeF3;
int FlagC=0,FlagD=0,FlagE=0,FlagF=0;

void setup()
{
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_setup(4000);  // Bits per sec
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    vw_rx_start();       // Start the receiver PLL running
}
    void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
      if((buf[0]=='A')&&(buf[1]=='1')){  
        if(FlagC==0)
        {
          timeC1 = millis();
          Serial.println(timeC1);
          FlagC=1;
        }
        timeC2 = millis();
        digitalWrite(13, HIGH);
     //  Serial.print("tone C");
      tone(8,523,500);
       timeC3 = timeC2 - timeC1;
      }  
      if((buf[0]=='A')&&(buf[1]=='2')){ 
        digitalWrite(13, HIGH);
       //Serial.print("tone D");
      tone(8,587,500); 
      FlagC=0;
      }
      if((buf[0]=='A')&&(buf[1]=='3')){ 
        digitalWrite(13, HIGH);
    //   Serial.print("tone E");
      tone(8,659,500);
      FlagC=0;
      }
      if((buf[0]=='A')&&(buf[1]=='4')){ 
        digitalWrite(13, HIGH);
      // Serial.print("tone F");
      tone(8,698,500);
      FlagC=0;
      }
      if((buf[0]=='A')&&(buf[1]=='5')){   
        digitalWrite(13, HIGH);
       Serial.println("Record and play Mode");
       
       tone(8,523);
       delay(timeC3);
       tone(8,0,10);
       timeC3=0;
      }
      /*else{
  tone(8,0,200);
  Serial.println("wrong code\n");
    }*/
      }
      else{
  digitalWrite(13, LOW);
    }

}
