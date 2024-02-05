#!/usr/bin/env python # 
"""
Test script to execute a HTTP Get of a URL
Usage: client-time.py <hostname: optional> <port: optional>
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

url = ('http://%s:%d/time'%(hostname, port))

print("HTTP GET to %s"%url)
x = requests.get(url)
print(type(x))

t = x.json()
print("JSON %s"%json.dumps(t))



print("%d-%d-%d %d:%d:%d"%(t['day'], t['month'], t['year'], t['hour'], t['minute'], t['second']))