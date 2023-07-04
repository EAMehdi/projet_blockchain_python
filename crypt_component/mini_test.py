import crypt_message as crypt

key="0x7f86a9f4865b4c9d7f86a9f4865b4c9d7f86a9f4865b4c9d7f86a9f4865b4c9d"
message="Hello, World!"
print("Le message original est ",message)
print("La clé est : ", key)
result=crypt.hmac_sha512(key, message)
print("Le message chiffré est :\n", result)

