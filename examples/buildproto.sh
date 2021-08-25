#!/bin/sh
mkdir -p protocol/googleapis/google/api
mkdir -p protocol/vision
mkdir proto

cp -rf ~/vision-core/vprotocol/src/main/protos/*  protocol/vision
#git clone https://github.com/vision-consensus/vision-core.git protocol/vision

#curl https://raw.githubusercontent.com/googleapis/googleapis/master/google/api/annotations.proto > protocol/googleapis/google/api/annotations.proto
#curl https://raw.githubusercontent.com/googleapis/googleapis/master/google/api/http.proto > protocol/googleapis/google/api/http.proto

sudo python3 -m grpc_tools.protoc -I./protocol/vision -I./protocol/googleapis --python_out=./proto ./protocol/vision/api/*.proto ./protocol/vision/core/*.proto ./protocol/googleapis/google/api/*.proto 
sudo python3 -m grpc_tools.protoc -I./protocol/vision -I./protocol/googleapis --python_out=./proto --grpc_python_out=./proto ./protocol/vision/api/*.proto
 