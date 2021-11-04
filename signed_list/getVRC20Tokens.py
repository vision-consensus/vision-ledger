from urllib.request import Request, urlopen
import json
from visionpy import Vision
from binascii import unhexlify
import codecs
import time
import fileinput
import base58

def address_hex(address):
    return base58.b58decode_check(address).hex().upper()

def conv(string):
    ret = "0x"+string[0:2]
    for i in range(1,21):
        ret += ",0x"+string[i*2:(i+1)*2]
    return ret


def urlopen_with_retry(toread, start):
     for i in range(5):
        try:
            time.sleep(0.3) 
            url = "https://vpioneer.infragrid.v.network/api/tokens/overview?limit={}&start={}&order=desc&filter=vrc20&sort=marketcap&order_current=descend".format(toread, start)
            req = Request(url, headers={'User-Agent': 'Mozilla/5.0'})
            return urlopen(req).read()
        except Exception as e:
            print(e)
            continue

ItemsFields = 'tokens'
toread = 20
start = 0
f= open("signedList_VRC20.txt","w+")
full_node = 'https://vpioneer.infragrid.v.network'
solidity_node = 'https://vpioneer.infragrid.v.network'
event_server = 'https://vpioneer.infragrid.v.network'

vision = Vision(network='vpioneer')
totalToken = 0
while (toread>0):
    url = urlopen_with_retry(toread,start)
    data = json.loads(url.decode())
    print(data)
    for T in data[ItemsFields]:
        address = address_hex(T['contractAddress'])
        print(address)
        f.write('{}{}{}{}, \"${} \", {}{},'.format("{","{",conv(address),"}",T['name'],T['decimal'],"}" ))
        f.write('\n')
    
    totalToken += len(data[ItemsFields])
    if len(data[ItemsFields])<toread:
        toread = 0
    start = start + toread

f.write('\n')
f.write('''''')
f.write('\n')
f.close()

totalToken += 7
print("Total Tokens: ",totalToken)
# TODO: update .c .h files



