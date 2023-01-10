### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(sht31 REQUIRED)
```


### 3. SHT31

#### 3.1 Command Instruction

1. Show sht31 chip and driver information.

   ```shell
   sht31 (-i | --information)
   ```

2. Show sht31 help.

   ```shell
   sht31 (-h | --help)
   ```

3. Show sht31 pin connections of the current board.

   ```shell
   sht31 (-p | --port)
   ```

4. Run sht31 register test.

   ```shell
   sht31 (-t reg | --test=reg) [--addr=<0 | 1>]
   ```

5. Run sht31 read test, num is test times.

   ```shell
   sht31 (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]
   ```

6. Run sht31 read function, num is read times.

   ```shell
   sht31 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
   ```

7. Run sht31 shot function, num is read times.

   ```shell
   sht31 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
./sht31 -i

sht31: chip is Sensirion SHT31.
sht31: manufacturer is Sensirion.
sht31: interface is IIC.
sht31: driver version is 2.0.
sht31: min supply voltage is 2.4V.
sht31: max supply voltage is 5.5V.
sht31: max current is 1.50mA.
sht31: max temperature is 125.0C.
sht31: min temperature is -40.0C.
```

```shell
./sht31 -p

sht31: SCL connected to GPIO3(BCM).
sht31: SDA connected to GPIO2(BCM).
```

```shell
./sht31 -t reg --addr=0

sht31: chip is Sensirion SHT31.
sht31: manufacturer is Sensirion.
sht31: interface is IIC.
sht31: driver version is 2.0.
sht31: min supply voltage is 2.4V.
sht31: max supply voltage is 5.5V.
sht31: max current is 1.50mA.
sht31: max temperature is 125.0C.
sht31: min temperature is -40.0C.
sht31: start register test.
sht31: sht31_set_addr_pin/sht31_get_addr_pin test.
sht31: set address pin 0.
sht31: check addr pin ok.
sht31: set address pin 1.
sht31: check addr pin ok.
sht31: sht31_set_repeatability/sht31_get_repeatability test.
sht31: set repeatability high.
sht31: check repeatability pin ok.
sht31: set repeatability medium.
sht31: check repeatability pin ok.
sht31: set repeatability low.
sht31: check repeatability pin ok.
sht31: set art test.
sht31: check art ok.
sht31: set heater test.
sht31: enable heater.
sht31: check heater ok.
sht31: disable heater.
sht31: check heater ok.
sht31: get status test.
sht31: check status 0x8070.
sht31: clear status test.
sht31: check clear status ok.
sht31: finish register test.
```

```shell
./sht31 -t read --addr=0 --times=3

sht31: chip is Sensirion SHT31.
sht31: manufacturer is Sensirion.
sht31: interface is IIC.
sht31: driver version is 2.0.
sht31: min supply voltage is 2.4V.
sht31: max supply voltage is 5.5V.
sht31: max current is 1.50mA.
sht31: max temperature is 125.0C.
sht31: min temperature is -40.0C.
sht31: start read test.
sht31: continuous read.
sht31: set low repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 31.60C.
sht31: humidity is 30.18%.
sht31: temperature is 32.31C.
sht31: humidity is 29.20%.
sht31: temperature is 32.37C.
sht31: humidity is 28.53%.
sht31: set rate 1Hz.
sht31: temperature is 32.54C.
sht31: humidity is 26.51%.
sht31: temperature is 32.57C.
sht31: humidity is 26.18%.
sht31: temperature is 32.54C.
sht31: humidity is 25.47%.
sht31: set rate 2Hz.
sht31: temperature is 32.61C.
sht31: humidity is 25.23%.
sht31: temperature is 32.61C.
sht31: humidity is 25.02%.
sht31: temperature is 32.62C.
sht31: humidity is 24.92%.
sht31: set rate 4Hz.
sht31: temperature is 32.65C.
sht31: humidity is 24.83%.
sht31: temperature is 32.62C.
sht31: humidity is 24.89%.
sht31: temperature is 32.69C.
sht31: humidity is 24.88%.
sht31: set rate 10Hz.
sht31: temperature is 32.62C.
sht31: humidity is 24.78%.
sht31: temperature is 32.62C.
sht31: humidity is 24.78%.
sht31: temperature is 32.61C.
sht31: humidity is 24.86%.
sht31: set medium repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 32.61C.
sht31: humidity is 24.89%.
sht31: temperature is 32.68C.
sht31: humidity is 25.60%.
sht31: temperature is 32.54C.
sht31: humidity is 25.15%.
sht31: set rate 1Hz.
sht31: temperature is 32.59C.
sht31: humidity is 24.83%.
sht31: temperature is 32.59C.
sht31: humidity is 24.66%.
sht31: temperature is 32.58C.
sht31: humidity is 24.54%.
sht31: set rate 2Hz.
sht31: temperature is 32.62C.
sht31: humidity is 24.56%.
sht31: temperature is 32.55C.
sht31: humidity is 24.45%.
sht31: temperature is 32.57C.
sht31: humidity is 24.44%.
sht31: set rate 4Hz.
sht31: temperature is 32.52C.
sht31: humidity is 24.43%.
sht31: temperature is 32.55C.
sht31: humidity is 24.44%.
sht31: temperature is 32.59C.
sht31: humidity is 24.48%.
sht31: set rate 10Hz.
sht31: temperature is 32.58C.
sht31: humidity is 24.45%.
sht31: temperature is 32.57C.
sht31: humidity is 24.48%.
sht31: temperature is 32.58C.
sht31: humidity is 24.48%.
sht31: set high repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 32.57C.
sht31: humidity is 24.50%.
sht31: temperature is 32.57C.
sht31: humidity is 24.45%.
sht31: temperature is 32.57C.
sht31: humidity is 24.41%.
sht31: set rate 1Hz.
sht31: temperature is 32.57C.
sht31: humidity is 24.88%.
sht31: temperature is 32.52C.
sht31: humidity is 25.02%.
sht31: temperature is 32.52C.
sht31: humidity is 24.99%.
sht31: set rate 2Hz.
sht31: temperature is 32.52C.
sht31: humidity is 24.78%.
sht31: temperature is 32.50C.
sht31: humidity is 24.72%.
sht31: temperature is 32.48C.
sht31: humidity is 24.56%.
sht31: set rate 4Hz.
sht31: temperature is 32.41C.
sht31: humidity is 24.56%.
sht31: temperature is 32.48C.
sht31: humidity is 24.56%.
sht31: temperature is 32.48C.
sht31: humidity is 24.49%.
sht31: set rate 10Hz.
sht31: temperature is 32.57C.
sht31: humidity is 24.57%.
sht31: temperature is 32.51C.
sht31: humidity is 24.54%.
sht31: temperature is 32.50C.
sht31: humidity is 24.51%.
sht31: single read.
sht31: set low repeatability.
sht31: temperature is 32.55C.
sht31: humidity is 24.49%.
sht31: temperature is 32.52C.
sht31: humidity is 24.48%.
sht31: temperature is 32.61C.
sht31: humidity is 24.62%.
sht31: set medium repeatability.
sht31: temperature is 32.54C.
sht31: humidity is 24.44%.
sht31: temperature is 32.57C.
sht31: humidity is 24.46%.
sht31: temperature is 32.54C.
sht31: humidity is 24.48%.
sht31: set high repeatability.
sht31: temperature is 32.52C.
sht31: humidity is 24.42%.
sht31: temperature is 32.55C.
sht31: humidity is 24.48%.
sht31: temperature is 32.57C.
sht31: humidity is 24.48%.
sht31: disable clock stretching.
sht31: temperature is 32.55C.
sht31: humidity is 24.38%.
sht31: temperature is 32.54C.
sht31: humidity is 24.40%.
sht31: temperature is 32.52C.
sht31: humidity is 24.40%.
sht31: finish read test.
```

```shell
./sht31 -e read --addr=0 --times=3

sht31: 1/3.
sht31: temperature is 33.37C.
sht31: humidity is 32.80%.
sht31: 2/3.
sht31: temperature is 33.37C.
sht31: humidity is 31.57%.
sht31: 3/3.
sht31: temperature is 33.42C.
sht31: humidity is 30.17%.
```

```shell
./sht31 -e shot --addr=0 --times=3

sht31: 1/3.
sht31: temperature is 33.37C.
sht31: humidity is 28.25%.
sht31: 2/3.
sht31: temperature is 33.35C.
sht31: humidity is 28.31%.
sht31: 3/3.
sht31: temperature is 33.34C.
sht31: humidity is 27.97%.
```

```shell
./sht31 -h

Usage:
  sht31 (-i | --information)
  sht31 (-h | --help)
  sht31 (-p | --port)
  sht31 (-t reg | --test=reg) [--addr=<0 | 1>]
  sht31 (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]
  sht31 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
  sht31 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]

Options:
      --addr=<0 | 1>    Set the addr pin.([default: 0])
  -e <read | shot>, --example=<read | shot>
                        Run the driver example.
  -h, --help            Show the help.
  -i, --information     Show the chip information.
  -p, --port            Display the pin connections of the current board.
  -t <reg | read>, --test=<reg | read>
                        Run the driver test.
      --times=<num>     Set the running times.([default: 3])
```

