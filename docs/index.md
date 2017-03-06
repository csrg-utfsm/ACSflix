# Benchmark for ACSflix commit ce8e9875011e874b995b42ddb5388234eb59855d

This benchmark is based on the [http://zeromq.org/results:10gbe-tests](same test taken by ZMQ), which consisted in:

> sending 1M messages over the network as fast as possible. The test was run for different messages size (1, 2, 4, 8, 16, 32, 64, 128, 256, 512 and 1024 bytes). The whole test was performed 3 times.

With that in mind, we followed ZMQ Instructions on [http://zeromq.org/results:perf-howto](How To Benchmark)

## Latency/Throughput Test

These tests will allow us to define a baseline behaviour

 - Idle systems, with different message sizes, for 1 million roundtrips, from A to B: 

| Message Size (Bytes) | 1 | 2 | 4 | 8 | 16 | 32 | 64 | 128 | 256 | 512 | 1024 | 
|  Latency  (us) | 126.943 | 128.261 | 130.060 | 130.633 | 132.878 |  |  |  |  |  |  |
|  Throughput (msg/s)   |  |  |  |  |  |  |  |  |  |  |  |
|  Throughput (Mbit/s)  |  |  |  |  |  |  |  |  |  |  |  |


## ACSflix

## HW Specifications
Computer A (Zoidberg): Dell Precision WorkStation T3400, 4GiB RAM DDR2 @ 800 MHz, Core 2 Duo E4600 @ 2.4 GHz, NetXtreme BCM5754 Gigabit
Computer B (acscb): HP Compaq 6200, 6GiB RAM DDR3 @ 1067 MHz, Core i5-2400@ 3.10GHz, 82579LM Gigabit Network
Switch: TP Link TL-SG1008 Gigabit

The computer's SO is Centos 7.3, kernel 3.10.0-514.10.2

## Sources and Useful Links
 - [http://zeromq.org/results:10gbe-tests](ZMQ oficial 10Gb Ethernet Tests)
 - [http://nikolaveber.blogspot.cl/2011/04/if-you-are-planning-large-or-not-even.html]
 - [http://zeromq.org/area:results](ZMQ Benchmaks)
