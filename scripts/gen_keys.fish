
#!/usr/bin/fish        
        
echo "Generating P-256 Elliptic Curve key pair"

echo "Generating private key"
echo "Enter device name: "
read deviceID
        
set priv_key_filename "ec-private-$deviceID.pem"
set pub_key_filename "ec-public-$deviceID.pem"

openssl ecparam -genkey -name prime256v1 -noout -out $priv_key_filename
openssl ec -in $priv_key_filename -pubout -out $pub_key_filename

mkdir data

openssl ec -outform der -in $priv_key_filename -out private-key.der

mv private-key.der data/

echo "Keys have been created."