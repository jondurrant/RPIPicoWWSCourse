import requests
import os

#key = os.environ["FREECURRENCYAPI"]


#url = ('https://api.freecurrencyapi.com/v1/latest?apikey=%s&currencies=GBP%%2CEUR'%(
#    key
#    ))

key = os.environ["EXCHANGERATEKEY"]

url = ('https://v6.exchangerate-api.com/v6/%s/latest/USD'%key)

x = requests.get(url)

print(x.text)