# Asym Jwt

Arduino library for creating asymmetrically signed jwt. Supports ES256 only.


- Generate key pair using using `gen_keys.fish`
```bash
fish gen_keys.fish

output: 
Generating P-256 Elliptic Curve key pair
Generating private key
Enter device name:
read> Test-2
read EC key
writing EC key
read EC key
writing EC key
Keys have been created.
```

- For adding private key in esp8266 with `platform.io` . After running the `gen_keys.fish`, there will be a data directory in root. In platform.io select `Build Filesystem Image` and then `Upload Filesystem Image` .

```cpp

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

```
