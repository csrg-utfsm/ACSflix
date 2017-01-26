# Worker results
Using `Zero-Copy` with 73M video with `chunk_size = 512kB`
```
real	0m18.942s
user	0m2.640s
sys	0m1.340s
```
Using `Zero-Copy` with 3.5G video with `chunk_size = 512kB`
```
real	16m26.590s
user	2m19.450s
sys	1m13.200s
```
Using `Zero-Copy` with 73M video with `chunk_size = 512kB` and concurrent stack to minimize malloc calls
```
real	0m11.575s
user	0m2.850s
sys	0m1.590s
```