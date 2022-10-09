
#include <crypto/make_jwt.h>

static const char base64_chars[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789-_";

String base64_encode(const unsigned char *bytes_to_encode, unsigned int in_len)
{
    String ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--)
    {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3)
        {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] =
                ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] =
                ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
            {
                ret += base64_chars[char_array_4[i]];
            }
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
        {
            char_array_3[j] = '\0';
        }

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] =
            ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] =
            ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
        {
            ret += base64_chars[char_array_4[j]];
        }
    }

    return ret;
}

String MakeBase64Signature(NN_DIGIT *signature_r, NN_DIGIT *signature_s)
{
    unsigned char signature[64];
    NN_Encode(signature, (NUMWORDS - 1) * NN_DIGIT_LEN, signature_r,
              (NN_UINT)(NUMWORDS - 1));
    NN_Encode(signature + (NUMWORDS - 1) * NN_DIGIT_LEN,
              (NUMWORDS - 1) * NN_DIGIT_LEN, signature_s,
              (NN_UINT)(NUMWORDS - 1));

    return base64_encode(signature, 64);
}

String CreateJwt(String payload, NN_DIGIT *priv_key)
{
    ecc_init();

    // header: base64_encode("{\"alg\":\"ES256\",\"typ\":\"JWT\"}") + "."
    String header_payload_base64 =
        "eyJhbGciOiJFUzI1NiIsInR5cCI6IkpXVCJ9." + base64_encode((const unsigned char *)payload.c_str(), payload.length());

    Sha256 sha256Instance;
    sha256Instance.update((const unsigned char *)header_payload_base64.c_str(), header_payload_base64.length());
    unsigned char sha256[SHA256_DIGEST_LENGTH];
    sha256Instance.final(sha256);

    // Signing sha with ec key. Bellow is the ec private key.
    point_t pub_key;
    ecc_gen_pub_key(priv_key, &pub_key);

    ecdsa_init(&pub_key);

    NN_DIGIT signature_r[NUMWORDS], signature_s[NUMWORDS];
    ecdsa_sign((uint8_t *)sha256, signature_r, signature_s, priv_key);

    return header_payload_base64 + "." +
           MakeBase64Signature(signature_r, signature_s);
}
