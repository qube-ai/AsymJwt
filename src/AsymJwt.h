#include <Arduino.h>
#include "jwt.h"
#include "crypto/nn.h"

namespace AsymJWT
{
    bool readPrivKey(String path);
    String generateJwt(String payload);
};


