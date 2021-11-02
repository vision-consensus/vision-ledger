# Test Case

Test cases are based on the following seed:

```
abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon abandon about
```

Select 12 words, enter 11 times `abandon` and one time `about`.

> This is the seed phrase we are going to use everywhere. Obviously don't use it to store your funds (unless testnet).\
> First Private key from this seed is b5a4cea271ff424d7c31dc12a3e43e401df7a40d7412a15750f3f0b6b5449a28 \
> Public key:  04ff21f8e64d3a3c0198edfbb7afdc79be959432e92e2f8a1984bb436a414b8edcec0345aad0c1bf7da04fd036dd7f9f617e30669224283d950fab9dd84831dc83\
>  Address: 41c8599111f29c1e1e061265b4af93ea1f274ad78a\
> Address base 58: TUEZSdKsoDHQMeZwihtdoBiN46zxhGWYdH

# Installing Vision app for Ledger
Testers, jump to: [Load pre-compiled HEX file](#load-pre-compiled-hex-file).

# Clone this repository
```bash
git clone https://github.com/vision-consensus/vision-ledger.git
cd vision-ledger
```


# Compiling from source

## Docker toolchain image
In order to make compiling as eas as possible you can make use of a docker image containing all the necessary compilers and the [nanos-secure-sdk](https://github.com/LedgerHQ/nanos-secure-sdk).

Make sure you have [Docker](https://www.docker.com/community-edition) installed.

### Step 1 - Build the image:
> make sure to select the appropriate $BOLOS_SDK in Dockerfile
```bash
docker build -t ledger-chain:latest .
```
The `.` at the end is **important!**

 
### Step 2 - Use Docker image
```bash
docker run --rm -v "$(pwd)":/vision-ledger -w /vision-ledger ledger-chain make
```

## Using your own toolchain
```bash
make
```


# Load app onto Ledger Nano S

Before attempting to load the hex file, make sure your Ledger Nano S 
is connected and the firware is updated to the [latest version](https://support.ledgerwallet.com/hc/en-us/articles/360002731113-Update-the-firmware).

Enter your PIN and **make sure you're seeing the Dashboard app**.

## Using Docker image
### Step 1 - Install virtualenv
```bash
[sudo] pip install -U setuptools
[sudo] pip install virtualenv
```

### Step 2 - Create new virtualenv
#### linux dependencies for ledgerblue module
> libudev1 libudev-dev libusb-1.0-0-dev

```bash
virtualenv -p python3 ledger
source ledger/bin/activate
pip install ledgerblue
or pip install git+https://github.com/LedgerHQ/blue-loader-python.git 
```

If you run into errors here, make sure you have the required dependencies installed. See [Ledger - Loader Python](https://github.com/LedgerHQ/blue-loader-python).

### Step 3 - Load HEX file
```bash
python -m ledgerblue.loadApp \
--targetId 0x31100003 \
--fileName bin/app.hex \
--icon `docker run --rm -v "$(pwd)":/vision_ledger -w /vision_ledger ledger-chain sh -c 'python $BOLOS_SDK/icon.py icon.gif hexbitmaponly'` \
--curve secp256k1 \
--path "44'/195'" \
--apdu \
--appName "Vision" \
--appVersion `cat ./VERSION` \
--appFlags 0x40 \
--delete \
--dataSize `cat debug/app.map | grep _nvram_data_size | tr -s ' ' | cut -f2 -d' '` \
--tlv 
```

### Step 4 - Leave virtualenv
To get out of your Python virtualenv again after everything is done.
```bash
deactivate
```

## Using your own toolchain

```bash
make load
```

## Load pre-compiled HEX file

Testers should start here.

Write down or remember the version number without the `v`. `v0.0.1` becomes `0.0.1`.

Write down the `dataSize`. You will need these in the step 3.

### Step 1 - Install virtualenv
See step 1 above. 

### Step 2 - Create new virtualenv
See step 2 above. 

### Step 3 - Load HEX file
```bash
python -m ledgerblue.loadApp \
--targetId 0x31100003 \
--fileName NAME_OF_PRECOMPILED_HEX_HERE.hex \
--icon 0100000000ffffff0000000000fc000c0f3814c822103f101120092005400340018001800000000000 \
--curve secp256k1 \
--path "44'/195'" \
--apdu \
--appName "Vision" \
--appVersion "VERSION_NUMBER" \
--appFlags 0x40 \
--delete \
--dataSize DATA_SIZE_OF_PRECOMPILED_HEX \
--tlv 
```
Replace `NAME_OF_PRECOMPILED_HEX_HERE.hex` with the location and name of the pre-compiled HEX file.

Replace `VERSION_NUMBER` with the version number of the pre-compiled HEX file.

Replace `DATA_SIZE_OF_PRECOMPILED_HEX` with the data size of the pre-compiled HEX file.

### Step 4 - Leave virtualenv
See step 4 above.


remark:
p2p: 16666 

fullnode http : 7080
fullnode rpc : 60061

solidity http : 7081
solidity rpc : 60071

pbft http : 7082
pbft rpc : 60081

eventquery rpc : 6666
