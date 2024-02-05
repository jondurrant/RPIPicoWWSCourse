#!/usr/bin/env python # 
"""
Test script to execute a HTTP Post of a URL
Will authentical using HTTP Basic
Usage: client-user.py <hostname: optional> <port: optional>
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

url = ('http://%s:%d/user'%(hostname, port))

#Create session and provide credentials
session = requests.Session()
session.auth = ("john", "hello")


newHeaders = {'Content-type': 'application/json', 'Accept': 'text/plain'}
data = {}

x = session.post(url, json=data, headers=newHeaders)
if (not x.ok):
    print("HTTP ERROR Code %d"%x.status_code)
else:
    t = x.json()
    if (t['status'] == "OK"):
        print("Submitted OK")
    else:
        print("Error submitting")