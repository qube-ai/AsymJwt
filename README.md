# Asym Jwt

Library for encoding with asymmetrically signed JSON web tokens for the Arduino and ESP8266 platforms. Only supports P-256 Elliptic Curve keys.


## Installation

### Arduino IDE

1. Download the latest release from the [releases page](https://github.com/qube-ai/AsymJwt/releases).
2. Unzip the downloaded file.
3. Rename the folder to `AsymJwt`.
4. Move the folder to your Arduino libraries folder.

### PlatformIO

1. Add the library to your `platformio.ini` file:

```ini
lib_deps =
    qube-ai/AsymJwt
```

## Usage

### Generating keys

2. Install [openssl](https://www.openssl.org/)
1. Install [fish shell](https://fishshell.com/) (optional)
3. Run `gen_keys.fish` or `gen_keys.sh` script in the `scripts` folder.
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

### Uploading keys to the device

1. Upload the private key to the device in DER format.
2. Keep the public key in a safe place.

#### Arduino IDE

1. Open the Arduino IDE.
2. Open the `Tools` menu.
3. Select `ESP8266 Sketch Data Upload`.
4. Select the private key file.
5. Click `Upload`.

#### PlatformIO

1. Create a `data` folder in the root of your project. 
2. Copy the private key file into the `data` folder. (The above script will create a `private-key.der` file inside `data/`.)
3. Add the following to your `platformio.ini` file (Optional): 

```ini
[env:your_env]
build_flags = -D PIO_FRAMEWORK_ARDUINO_LWIP2_HIGHER_BANDWIDTH
upload_flags = --upload-port $UPLOAD_PORT --upload-file data/private-key.der
```
or 

4. Go to PlatformIO Home > your_env > Platform > Build Filesystem Image > Upload Filesystem Image


### Using the library

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


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Configuration

- Enable debug mode by defining `ASYMJWT_DEBUG` before including the library.
  
  ```cpp
  #define ASYMJWT_DEBUG 1

  #include <AsymJwt.h>
  ```


## TODO

- [ ] Add support for decoding JWTs (currently only encoding is supported)
- [ ] Add support for other key types
- [ ] Add support for other hashing algorithms