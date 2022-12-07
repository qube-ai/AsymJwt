#include "AsymJwt.h"


NN_DIGIT priv_key[9];

void storePrivateKey(const unsigned char *private_key)
{
  priv_key[8] = 0;
  for (int i = 7; i >= 0; i--)
  {
    for (int byte_num = 0; byte_num < 4; byte_num++)
    {
      priv_key[i] = (priv_key[i] << 8) + *private_key;
      ++private_key;
    }
  }
}

bool AsymJWT::readPrivKey(String path)
{
    if (!LittleFS.begin())
    {
        AsymJwt_Logln("[AsymJwt.readPrivKey] Failed to mount file system");
        return false;
    }
    File f = LittleFS.open(path, "r");
    if (f)
    {
        size_t size = f.size();
        uint8_t data[size];
        f.read(data, size);
        f.close();

        BearSSL::PrivateKey pk(data, size);
        storePrivateKey(pk.getEC()->x);

        // Private key setup complete
        AsymJwt_Logln("[AsymJwt.readPrivKey] Private key setup complete");
        return true;
    }
    else
    {
        AsymJwt_Logln("[AsymJwt.readPrivKey] No private key found on device!");
        return false;
    }
}

String AsymJWT::generateJwt(String payload){
  // Disable software watchdog as these operations can take a while.
  ESP.wdtDisable();
  String jwt = CreateJwt(payload, priv_key);
  ESP.wdtEnable(0);
  return jwt;
}
