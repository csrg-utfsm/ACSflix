# How to run test
Compile
```
make clean
make
```
You may need to set `LD_LIBRARY_PATH` for the binaries to work
```
export LD_LIBRARY_PATH=/usr/local/lib
```
Run sender with input file name or `debug` option
```
./sender tcp://*:9991 file|debug
```
Run worker with output file name or `stdout` option
```
./worker tcp://localhost:9991 test.out|stdout
```

# Worker results
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