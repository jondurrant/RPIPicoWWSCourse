#!/usr/bin/env python # 
"""
Test WebServices HTTP Server
Usage: full-server
"""

from flask import request
from flask import Flask
from flask_httpauth import HTTPBasicAuth
from werkzeug.security import generate_password_hash, check_password_hash
from datetime import datetime
import json
import socket


app = Flask(__name__, static_url_path='/static')

@app.route('/', methods=['GET', 'POST'])
def root():
    return "<HTML><BODY><H1>Flask Test Page</H1></BODY?</HTML>"


@app.route('/time', methods=['GET', 'POST'])
def time():
    a = datetime.now()
    t = {
        'year': a.year,
        'month': a.month,
        'day': a.day,
        'hour': a.hour,
        'minute': a.minute,
        'second': a.second
        }

    return json.dumps(t)


@app.route('/temp', methods=['GET', 'POST'])
def temp():
    #print(request.headers)
    #print(request.data)
    s = request.args.get('temp')
    t = 0.0
    
    if request.is_json:
        s = request.get_json()["temp"]
  

    try:
        t = float(s)
    except ValueError:
        print("Data is not float")
        res = {'status': "ERROR"}
        return json.dumps(res)
        
    if request.method == 'POST':
        print("Temp Submitted by POST %f"% t)
    else:
        print("Temp Submitted by GET %f"% t)
    
    res = {'status': "OK"}
    return json.dumps(res)


@app.route('/json', methods=['GET', 'POST'])
def jsonws():
    
    if request.is_json:
        print("Valid JSON: %s"% json.dumps(request.get_json()))
    else:
        print("Invalid JSON");
    
    res = {'status': "OK"}
    return json.dumps(res)

auth = HTTPBasicAuth()

users = {
    "john": generate_password_hash("hello"),
    "susan": generate_password_hash("bye")
}

@auth.verify_password
def verify_password(username, password):
    print("Verifying %s %s"%(username, password))
    if username in users and check_password_hash(users.get(username), password):
        print("User valid")
        return username
    else:
        print("Unknown user")
        return False

@app.route('/user', methods=['GET', 'POST'])
@auth.login_required
def user():
    r = {
        "user": auth.current_user(),
        "status": "OK"
        }
    return json.dumps(r)


@app.route('/args', methods=['GET'])
def args():
    print("/Args: ")
    for key in request.args:
        print(" %s=%s"%(key, request.args[key]))
    
    return json.dumps(request.args)



if __name__ == "__main__":
    app.secret_key = 'DRJONEA'
    app.config['SESSION_TYPE'] = 'filesystem'
    
    hostname = socket.gethostname()
    ip_address = socket.gethostbyname(hostname)
    print(f"Hostname: {hostname}")
    print(f"IP Address: {ip_address}")
    
    app.run(host="0.0.0.0")