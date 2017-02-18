#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;
int fsrPin0 = A0;
int fsrPin1 = A1;
int fsrReading0, fsrReading2;

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
  if (fsrReading0 > 250) {
    Serial.println("Sending to nrf24_server");
    uint8_t data []= "1046";
    nrf24.send(data, sizeof(data));
    tone(3, 1046, 100);
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
    Serial.println("No tone on other piano");
  }
}

