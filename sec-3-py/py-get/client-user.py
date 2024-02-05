#!/usr/bin/env python # 
"""
Test script to execute a HTTP Get of a URL
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

urlValid = ('http://john:hello@%s:%d/user'%(hostname, port))
urlInvalid = ('http://john:bye@%s:%d/user'%(hostname, port))

x = requests.get(urlValid)
t = x.json()
print("JSON %s"%json.dumps(t))

x = requests.get(urlInvalid)
print(x)
