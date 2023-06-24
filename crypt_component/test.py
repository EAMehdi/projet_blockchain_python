import crypt_message as crypt

key = "secret"
message = "Hello, World!"
message_alt = "Hello World!"
result = crypt.hmac_sha512(key, message)
r2msg= crypt.hmac_sha512(key,message_alt)

print(f'Le message est : {message}')
print(f'Le cryptage est : {result}')
print(f'Le message original est : {r2msg}')

