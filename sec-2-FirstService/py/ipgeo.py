import requests
import os

key = os.environ["IPGEOLOCATION"]

url = ('https://api.ipgeolocation.io/ipgeo?apiKey=%s'%key)

x = requests.get(url)

print(x.text)
