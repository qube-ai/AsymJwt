#include <Arduino.h>

#ifndef AsymJwt_h
#define AsymJwt_h

#include "crypto/make_jwt.h"
#include "crypto/nn.h"
#include "crypto/ecc.h"
#include "crypto/ecdsa.h"
#include "crypto/sha256.h"


namespace AsymJWT
{
    bool readPrivKey(String path);
    String generateJwt(String payload);
};


#endif
