
#include <SPI.h>
#include <RH_NRF24.h>

RH_NRF24 nrf24;

int fsrPin1 = A0;
int fsrReading1;

int fsrPin2 = A1;
int fsrReading2;

void setup() 
{
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
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
  if (nrf24.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (nrf24.recv(buf, &len))
    {
      int note = atoi(buf);
      tone(3, note, 100);
    }
    else
    {
      Serial.println("recv failed");
    }

  }
  fsrReading1 = analogRead(fsrPin1);
  fsrReading2 = analogRead(fsrPin2);

  if(fsrReading1 > 250){
      tone(3, 1109, 100);
      uint8_t data[] = "1109";
      nrf24.send(data, sizeof(data));
      nrf24.waitPacketSent();
  }
  else if(fsrReading2 > 250){
    tone(3, 988, 100);
    uint8_t data[] = "988";
    nrf24.send(data, sizeof(data));
    nrf24.waitPacketSent();
  }
}

