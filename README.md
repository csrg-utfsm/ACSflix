# ACSFlix

## Dependencies

- libuuid-devel, uuid. Epel repo is recommended.
- cmake
- zmq 3.2+
- zmq-devel
- protobuf-compiler
- protobuf-devel

## How to run test
Compile
```
mkdir -p build
cd build
cmake ..
make
```
You may need to set `LD_LIBRARY_PATH` for the binaries to work if you use a custom installation of zmq (not necessary nor recommended)
```
export LD_LIBRARY_PATH=/usr/local/lib
```
Run sender with input file:
```
./sender tcp://*:9991 file
```
Run worker with output file name:
```
./worker tcp://localhost:9991 file
```

## Worker results
Using `zmq_send` with 73M video with `chunk_size = 512kB`
```
real	0m0.690s
user	0m0.050s
sys	0m0.080s
```
Using `zmq_send` with 3.5G video with `chunk_size = 512kB`
```
real	0m49.443s
user	0m1.280s
sys	0m6.660s
```
