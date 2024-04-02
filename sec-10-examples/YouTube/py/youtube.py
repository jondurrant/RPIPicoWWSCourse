import requests
import os

key = os.environ["YOUTUBEAPIKEY"]



url = ('https://youtube.googleapis.com/youtube/v3/channels?part=statistics&id=UCMX47a_aT7tujbsiD5iD70Q&key=%s'%(
    key
    ))

x = requests.get(url)

print(x.text)