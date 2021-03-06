# Benchmark for ACSflix commit ce8e987501

This benchmark is based on the [same test taken by ZMQ](http://zeromq.org/results:10gbe-tests), which consisted in:

> sending 1M messages over the network as fast as possible. The test was run for different messages size ( 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096 and 8192 bytes). The whole test was performed 3 times.

With that in mind, we followed ZMQ Instructions on [How To Benchmark](http://zeromq.org/results:perf-howto)

## Latency/Throughput Test

These tests will allow us to define a baseline behaviour

 - Idle systems, MTU 1500, with different message sizes, for 1 million roundtrips, from A to B: 

| Message Size (Bytes) | 2         | 4         | 8         | 16        | 32        | 64        | 128      | 256      | 512      | 1024    |
|  Latency  (us)       | 128.261   | 130.060   | 131.086   | 130.633   | 132.878   | 136.549   | 138.214  | 139.322  | 142.327  | 156.682 |
|  Throughput (msg/s)  | 5.247.773 | 5.154.931 | 4.935.712 | 4.584.653 | 2.919.801 | 1.497.671 | 748.864  | 365.747  | 186.768  | 94.288  |
|  Throughput (Mbit/s) | 83.964    | 164.958   | 315.886   | 586.836   | 747.469   | 766.808   | 766.837  | 749.050  | 765.002  | 772.407 |

| Message Size (Bytes) | 2048    | 4096    | 8192    |
|  Latency  (us)       | 145.435 | 264.269 | 289.649 |
|  Throughput (msg/s)  | 47.470  | 23.771  | 11.812  |
|  Throughput (Mbit/s) | 777.748 | 778.928 | 774.111 |

## ACSflix

The logic in ACSflix is pretty simple:
 * We use PUSH/PULL sockets to send the data.
 * And a PUB/SUB channel to notify the worker of the End of Transmission.

Each of the Push/Pull pair of sockets is referred as a _Flow_, which can be grouped in a _Stream_.

 - The minimum buffer size is 2 Bytes. 
 - Testings are performed over OSes with firewalls.
 - An equivalent file size has been calculated with: (1 Million messages * X Bytes) / 1024^2
 - In ACSflix, using -b flag, buffer size can be set.
 - Files used are images available at [http://repo.csrg.cl/images]-

 - Raw Spreadsheat with results [here](https://docs.google.com/spreadsheets/d/1Cc6lL09_GAdZqS7Cgd2qobvoYTfTsW_EFV5t3pR1eSc/edit?usp=sharing)

### 1 Flow, 1 Stream

|File Size [MB] - Buffer Size [B]| 1.91 (2) | 3.82 (4) | 7.64 (8) | 15.28 (16) | 30.56 (32) | 61.12 (64) | 122.24 (128) | 244.48 (256) | 488.96 (512) | 977.12 (1024) |
| Message Count | 1003567 | 1186428 | 1066113 | 1055297 | 1055155 | 1012879 | 995589 | 1007966 | | |
|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|  Throughput (msg/s)  | 534282 | 498097 | 526471 | 528386 | 531906 | 482857 | 490666 | 389603 | 
|  Throughput (Mbit/s) | 8.549 | 15.939 | 33.694 | 67.633 | 136.168 | 247.223 | 502.442 | 797.907 |

|File Size (MB)| 1956 (2048) | 3912 (4096) | 7824 (8192) |
| Message Count | | | |
|--------------------------------------------------------|
|  Throughput (msg/s)  |
|  Throughput (Mbit/s) |

### 3 Flows, 1 Stream



### 3 Flows, 3 Streams



## HW Specifications
 * Computer A (Zoidberg): Dell Precision WorkStation T3400, 4GiB RAM DDR2 @ 800 MHz, Core 2 Duo E4600 @ 2.4 GHz, NetXtreme BCM5754 Gigabit

 * Computer B (acscb): HP Compaq 6200, 6GiB RAM DDR3 @ 1067 MHz, Core i5-2400@ 3.10GHz, 82579LM Gigabit Network

 * Switch: TP Link TL-SG1008 Gigabit

The computer's SO is Centos 7.3, kernel 3.10.0-514.10.2

## Sources and Useful Links
 - [ZMQ oficial 10Gb Ethernet Tests](http://zeromq.org/results:10gbe-tests)
 - [http://nikolaveber.blogspot.cl/2011/04/if-you-are-planning-large-or-not-even.html]
 - [ZMQ Benchmaks](http://zeromq.org/area:results)
 - [Pub/sub reports 15 us extra interval and ZMQ_NOBLOCK lows the extra time to just 10 us](http://stackoverflow.com/questions/30660627/zeromq-performance-test-whats-the-accurate-latency)
