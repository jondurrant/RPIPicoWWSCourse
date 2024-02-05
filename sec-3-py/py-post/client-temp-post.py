import requests
import os
import json
import sys


hostname = "localhost"
port = 5000

if len(sys.argv) > 1:
    hostname = sys.argv[1]

if len(sys.argv) == 3:
    port = int(sys.argv[2])

url = ('http://%s:%d/temp'%(hostname, port))
newHeaders = {'Content-type': 'application/json', 'Accept': 'text/plain'}

data = {'temp': 26.5}

x = requests.post(url, json=data, headers=newHeaders)
if (not x.ok):
    print("HTTP ERROR Code %d"%x.status_code)
else:
    t = x.json()
    if (t['status'] == "OK"):
        print("Submitted OK")
    else:
        print("Error submitting")