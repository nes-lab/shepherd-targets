# nRF52 UART_benchmark

The firmware puts out `lorem ipsum` test at a specified baudrate.
This can be used to benchmark the shepherd-testbed:

- testing long term stability limits by stress-testing the whole processing and storage pipeline
- decoding uart from GPIO by only recording timestamped io-changes and later comparing the parsed output against the reference input

Compiling can be done via

```Shell
make BAUDRATE=115200
```

The following discrete baudrates can be configured:

- 1200
- 2400
- 4800
- 14400
- 19200
- 28800
- 31250
- 38400
- 56000
- 57600
- 76800
- 115200
- 230400
- 250000
- 460800
- 921600
- 1000000
