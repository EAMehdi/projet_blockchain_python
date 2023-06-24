import pytest
import crypt_message as crypt

def test_hmac_sha512_valid():
    key = "secret"
    message = "Hello, World!"
    assert crypt.hmac_sha512(key, message) == '851caed63934ad1c9a03aef23ba2b84f224bdff4f5148efc57d95f9ae80ca9db2e98bc4c709a529eb1b7234a1ac2e381d28e0eb1efa090bb19613f5c124b6d5b'

def test_hmac_sha512_empty_key():
    message = "Hello, World!"
    with pytest.raises(ValueError):
        crypt.hmac_sha512('', message)

def test_hmac_sha512_wrong_key_type():
    message = "Hello, World!"
    with pytest.raises(TypeError):
        crypt.hmac_sha512(123, message)

def test_hmac_sha512_wrong_message_type():
    key = "secret"
    with pytest.raises(TypeError):
        crypt.hmac_sha512(key, 123)


