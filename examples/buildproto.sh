#!/bin/sh
mkdir -p protocol/google/api
mkdir proto
git clone https://github.com/vision-consensus/vision-protocol.git protocol/

curl https://raw.githubusercontent.com/googleapis/googleapis/master/google/api/annotations.proto > protocol/google/api/annotations.proto
curl https://raw.githubusercontent.com/googleapis/googleapis/master/google/api/http.proto > protocol/google/api/http.proto

python3 -m grpc_tools.protoc -I./protocol/ --python_out=./proto ./protocol/api/*.proto ./protocol/core/*.proto ./protocol/google/api/*.proto 
python3 -m grpc_tools.protoc -I./protocol/ --python_out=./proto --grpc_python_out=./proto ./protocol/api/*.proto
 