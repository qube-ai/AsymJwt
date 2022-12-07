#include <Arduino.h>
#include <AsymJwt.h>


void setup()
{
  Serial.begin(9600);
  Serial.println("Reading private ket....");
  while (!AsymJWT::readPrivKey("/private-key.der"))
  {
    Serial.println("Failed to read private key. Retrying in 2 seconds");
    delay(2000);
  }
}


void loop()
{
  time_t iat = time(nullptr);
  String payload = "{\"iat\":" + String(iat) + ",\"exp\":" + String(iat + 300) + ",\"thing_id\":\"" + "THING_ID" + "\"}";
  Serial.println(AsymJWT::generateJwt(payload));
  delay(200000);
  Serial.println("Refreshing JWT.");
}