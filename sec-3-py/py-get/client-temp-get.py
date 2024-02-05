#!/usr/bin/env python # 
"""
Test script to execute a HTTP Get of a URL
Will send a temperature to the server
Usage: client-temp.py <hostname: optional> <port: optional>
"""

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

data = {'temp': 26.5}

x = requests.get(url, params=data)
if (not x.ok):
    print("HTTP ERROR Code %d"%x.status_code)
else:
    t = x.json()
    if (t['status'] == "OK"):
        print("Submitted OK")
    else:
        print("Error submitting")