import crypt_message as crypt

key = "secret"
message = "Hello World!"
message_alt = "Hello World!"
result = crypt.hmac_sha512(key, message)

print(f'Le message original est : {message}')
print(f'La clé est : {key}')
print(f'Message chiffré : {result}')

