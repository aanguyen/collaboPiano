#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;
int fsrPin0 = A0;
int fsrPin1 = A1;
int fsrPin2 = A2;
int fsrReading0, fsrReading1, fsrReading2;

void setup() 
{
  Serial.begin(9600);
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}


void loop()
{
  fsrReading0 = analogRead(fsrPin0);
  fsrReading1 = analogRead(fsrPin1);
  fsrReading2 = analogRead(fsrPin2);
  Serial.print("   Pressure 1: ");
  Serial.println(fsrReading1);
  if (fsrReading0 > 250) {
    uint8_t data[] = "880";
    nrf24.send(data, sizeof(data));
    tone(3, 880, 100);
  }
  if (fsrReading1 > 250) {
    uint8_t data1[] = "831";
    nrf24.send(data1, sizeof(data1));
    tone(3, 831, 100);
  }
  if (fsrReading2 > 250) {
    uint8_t data2[] = "441";
    nrf24.send(data2, sizeof(data2));
    tone(3, 441, 100);  
  }
  nrf24.waitPacketSent();
  //Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);  

  if (nrf24.waitAvailableTimeout(10))
  { 
    // Should be a reply message for us now   
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
      int note = atoi(buf);
      tone(3, note, 100);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    //There is no tone on the other piano
  }
}

