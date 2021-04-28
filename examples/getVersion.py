#!/usr/bin/env python

from ledgerblue.comm import getDongle

# Create APDU message.
# CLA 0xE0
# INS 0x06  GET_APP_CONFIGURATION
# P1 0x00   NO USER CONFIRMATION
# P2 0x00   NO CHAIN CODE
apduMessage = "E0060000ff"

print("-= Vision Ledger =-")
print("Request app Version")

dongle = getDongle(True)
result = dongle.exchange(bytearray.fromhex(apduMessage))

print('Version={:d}.{:d}.{:d}'.format(result[1],result[2],result[3]))
