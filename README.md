ACSFlix
=======

## Dependencies
- libuuid-devel, uuid. Epel repo is recommended. 
- cmake
- zmq 4.2.0+
- protobuf-compiler
- protobuf-devel

## How to Build
 - Create folder build inside ACSFlix folder and cd into it
 - protoc --cpp_out=. BdBlock.proto inside proto folder
 - run cmake
 - If you're using a self-compiled version of zmq and czmq, CMakeList.txt must be modified.
 
 ## Rebuild due to CZMQ Zero Copy Deprecation
 - https://github.com/zeromq/czmq/commit/de8c1bc4
