
#include <Arduino.h>

#include <stdio.h>

#include "crypto/ecc.h"
#include "crypto/ecdsa.h"
#include "crypto/nn.h"
#include "crypto/sha256.h"

String base64_encode(const unsigned char *bytes_to_encode, unsigned int in_len);

String MakeBase64Signature(NN_DIGIT *signature_r, NN_DIGIT *signature_s);

String CreateJwt(String payload, NN_DIGIT *priv_key);
