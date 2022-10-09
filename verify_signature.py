import jwt 
token = input("Enter token(JWT): ")
try:
    public_key = open("ec_public.pem", "r").read()
    res = jwt.decode(token, public_key, algorithms=['ES256'])
    print(f"Token is valid {res}")
except jwt.exceptions.InvalidSignatureError:
    print("Token is invalid. [InvalidSignatureError]")

except jwt.exceptions.DecodeError:
    print("Wrong key. [DecodeError]")

except jwt.exceptions.ExpiredSignatureError:
    print("Token is expired. [ExpiredSignatureError]")

except jwt.exceptions.InvalidTokenError:
    print("Token is invalid. [InvalidTokenError]")



