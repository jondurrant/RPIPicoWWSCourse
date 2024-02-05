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

url = ('http://%s:%d/json'%(hostname, port))
newHeaders = {'Content-type': 'application/json', 'Accept': 'text/plain'}


j = {
        'temp': 28.0,
        'date': '2023:09:14',
        'time': '08:00:00'
    }


x = requests.post(url, json=j, headers=newHeaders)
if (not x.ok):
    print("HTTP ERROR Code %d"%x.status_code)
else:
    t = x.json()
    if (t['status'] == "OK"):
        print("Submitted OK")
    else:
        print("Error submitting")