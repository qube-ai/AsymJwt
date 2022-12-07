#ifdef ASYMJWT_DEBUG
    #define AsymJwt_Log(...) Serial.print(__VA_ARGS__)
    #define AsymJwt_Logln(...) Serial.println(__VA_ARGS__)
#else
    #define AsymJwt_Log(...) (void)0
    #define AsymJwt_Logln(...) (void)0
#endif

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
