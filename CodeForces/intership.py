import time
import hmac
import hashlib
import struct
import base64
import requests

email = "kushagrapandey.make@gmail.com"
secret = email + "HENNGECHALLENGE004"

def generate_totp():
    counter = int(time.time() // 30)
    msg = struct.pack(">Q", counter)
    h = hmac.new(secret.encode(), msg, hashlib.sha512).digest()
    o = h[-1] & 0x0F
    code = (struct.unpack(">I", h[o:o+4])[0] & 0x7fffffff) % (10**10)
    return str(code).zfill(10)

totp = generate_totp()

auth = base64.b64encode(f"{email}:{totp}".encode()).decode()

headers = {
    "Authorization": f"Basic {auth}",
    "Content-Type": "application/json"
}

data = {
    "github_url": "https://gist.github.com/kushagra0333/f604101f24f5b736f87aa78061fc6b9e",
    "contact_email": email,
    "solution_language": "python"
}

response = requests.post(
    "https://api.challenge.hennge.com/challenges/backend-recursion/004",
    json=data,
    headers=headers
)

print(response.status_code)
print(response.text)