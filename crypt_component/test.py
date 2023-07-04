import pytest
import crypt_message as crypt

def test_hmac_sha512_valid():
    key = "0x7f86a9f4865b4c9d7f86a9f4865b4c9d7f86a9f4865b4c9d7f86a9f4865b4c9d"
    message = "Hello, World!"
    assert crypt.hmac_sha512(key, message) == '51d746531a26bd58baf64c02e73df5bb4586aca6d61a73f26008319ee33c42b9e7c8b000494fc2c33b101a60623710db11f11ef35976b064f3b00ce39ff0c1fc'

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


