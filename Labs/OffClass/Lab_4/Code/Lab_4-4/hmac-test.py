import hashlib
import hmac

def generate_hmac_sha1(key, message):
    return hmac.new(key, message, hashlib.sha1).hexdigest()

def generate_hmac_sha256(key, message):
    return hmac.new(key, message, hashlib.sha256).hexdigest()


def generate_hmac_sha512(key, message):
    return hmac.new(key, message, hashlib.sha512).hexdigest()


key = b'laiquanthien1501'
message = b'xin-chao-the-gioi'

hmac_digest = generate_hmac_sha1(key, message)
print(f'HMAC-SHA1: {hmac_digest}')

hmac_digest = generate_hmac_sha256(key, message)
print(f'HMAC-SHA256: {hmac_digest}')

hmac_digest = generate_hmac_sha512(key, message)
print(f'HMAC-SHA512: {hmac_digest}')
