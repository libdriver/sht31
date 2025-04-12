### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

GPIO Pin: INT GPIO17.

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

6. Run sht31 alert test, ms is the timeout in ms, degree is the degree of limit, percentage is the percentage of limit.

   ```shell
   sht31 (-t alert | --test=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>][--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]
   ```

7. Run sht31 read function, num is read times.

   ```shell
   sht31 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
   ```

8. Run sht31 shot function, num is read times.

   ```shell
   sht31 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]
   ```
9. Run sht31 alert function, ms is the timeout in ms, degree is the degree of limit, percentage is the percentage of limit.

   ```shell
   sht31 (-e alert | --example=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>][--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]
   ```
10. Run sht31 sn function.

   ```shell
   sht31 (-e sn | --example=sn) [--addr=<0 | 1>]
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
sht31: ALERT connected to GPIO17(BCM).
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
sht31: sht31_get_status test.
sht31: check status 0x8070.
sht31: sht31_clear_status test.
sht31: check clear status ok.
sht31: sht31_get_serial_number test.
sht31: serial number is 0x10 0xE2 0x41 0x1F.
sht31: sht31_set_high_alert_limit/sht31_get_high_alert_limit test.
sht31: set is 0xF6F7.
sht31: clear is 0x934B.
sht31: check high alert limit set ok.
sht31: check high alert limit clear ok.
sht31: sht31_set_low_alert_limit/sht31_get_low_alert_limit test.
sht31: set is 0xDADD.
sht31: clear is 0x5609.
sht31: check low alert limit set ok.
sht31: check low alert limit clear ok.
sht31: sht31_alert_limit_convert_to_register test.
sht31: 80.00% 60.00C converted 0xCD33.
sht31: 22.00% -9.00C converted 0x3869.
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
sht31: temperature is 29.13C.
sht31: humidity is 27.53%.
sht31: temperature is 29.65C.
sht31: humidity is 27.32%.
sht31: temperature is 29.79C.
sht31: humidity is 26.81%.
sht31: set rate 1Hz.
sht31: temperature is 29.85C.
sht31: humidity is 26.40%.
sht31: temperature is 29.82C.
sht31: humidity is 26.19%.
sht31: temperature is 30.00C.
sht31: humidity is 26.09%.
sht31: set rate 2Hz.
sht31: temperature is 29.93C.
sht31: humidity is 26.09%.
sht31: temperature is 30.02C.
sht31: humidity is 26.05%.
sht31: temperature is 29.96C.
sht31: humidity is 26.00%.
sht31: set rate 4Hz.
sht31: temperature is 29.90C.
sht31: humidity is 25.89%.
sht31: temperature is 29.93C.
sht31: humidity is 26.05%.
sht31: temperature is 29.99C.
sht31: humidity is 25.94%.
sht31: set rate 10Hz.
sht31: temperature is 29.93C.
sht31: humidity is 25.95%.
sht31: temperature is 30.06C.
sht31: humidity is 25.98%.
sht31: temperature is 29.93C.
sht31: humidity is 25.98%.
sht31: set medium repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 30.02C.
sht31: humidity is 25.99%.
sht31: temperature is 29.96C.
sht31: humidity is 26.00%.
sht31: temperature is 30.03C.
sht31: humidity is 26.26%.
sht31: set rate 1Hz.
sht31: temperature is 30.09C.
sht31: humidity is 26.33%.
sht31: temperature is 30.03C.
sht31: humidity is 26.28%.
sht31: temperature is 30.04C.
sht31: humidity is 26.05%.
sht31: set rate 2Hz.
sht31: temperature is 30.06C.
sht31: humidity is 25.99%.
sht31: temperature is 30.06C.
sht31: humidity is 25.86%.
sht31: temperature is 30.00C.
sht31: humidity is 25.91%.
sht31: set rate 4Hz.
sht31: temperature is 30.09C.
sht31: humidity is 25.95%.
sht31: temperature is 30.07C.
sht31: humidity is 25.89%.
sht31: temperature is 30.09C.
sht31: humidity is 25.90%.
sht31: set rate 10Hz.
sht31: temperature is 30.07C.
sht31: humidity is 25.84%.
sht31: temperature is 30.04C.
sht31: humidity is 25.93%.
sht31: temperature is 30.06C.
sht31: humidity is 25.90%.
sht31: set high repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 30.06C.
sht31: humidity is 25.95%.
sht31: temperature is 30.07C.
sht31: humidity is 25.95%.
sht31: temperature is 30.07C.
sht31: humidity is 25.95%.
sht31: set rate 1Hz.
sht31: temperature is 30.10C.
sht31: humidity is 26.03%.
sht31: temperature is 30.10C.
sht31: humidity is 25.89%.
sht31: temperature is 30.12C.
sht31: humidity is 25.86%.
sht31: set rate 2Hz.
sht31: temperature is 30.13C.
sht31: humidity is 25.89%.
sht31: temperature is 30.12C.
sht31: humidity is 25.85%.
sht31: temperature is 30.13C.
sht31: humidity is 25.80%.
sht31: set rate 4Hz.
sht31: temperature is 30.14C.
sht31: humidity is 25.62%.
sht31: temperature is 30.12C.
sht31: humidity is 25.75%.
sht31: temperature is 30.12C.
sht31: humidity is 25.78%.
sht31: set rate 10Hz.
sht31: temperature is 30.14C.
sht31: humidity is 25.89%.
sht31: temperature is 30.14C.
sht31: humidity is 25.94%.
sht31: temperature is 30.16C.
sht31: humidity is 25.97%.
sht31: single read.
sht31: set low repeatability.
sht31: temperature is 30.17C.
sht31: humidity is 26.02%.
sht31: temperature is 30.17C.
sht31: humidity is 25.88%.
sht31: temperature is 30.10C.
sht31: humidity is 25.95%.
sht31: set medium repeatability.
sht31: temperature is 30.16C.
sht31: humidity is 25.86%.
sht31: temperature is 30.16C.
sht31: humidity is 25.89%.
sht31: temperature is 30.17C.
sht31: humidity is 25.88%.
sht31: set high repeatability.
sht31: temperature is 30.16C.
sht31: humidity is 25.89%.
sht31: temperature is 30.16C.
sht31: humidity is 25.91%.
sht31: temperature is 30.17C.
sht31: humidity is 25.91%.
sht31: disable clock stretching.
sht31: temperature is 30.16C.
sht31: humidity is 25.92%.
sht31: temperature is 30.20C.
sht31: humidity is 25.94%.
sht31: temperature is 30.17C.
sht31: humidity is 25.86%.
sht31: finish read test.
```

```shell
./sht31 -t alert --addr=0 --timeout=10000 --high-limit-temp=30.0 --high-limit-humi=50.0 --low-limit-temp=25.0 --low-limit-humi=30.0

sht31: chip is Sensirion SHT31.
sht31: manufacturer is Sensirion.
sht31: interface is IIC.
sht31: driver version is 2.0.
sht31: min supply voltage is 2.4V.
sht31: max supply voltage is 5.5V.
sht31: max current is 1.50mA.
sht31: max temperature is 125.0C.
sht31: min temperature is -40.0C.
sht31: start alert test.
sht31: high limit temperature is 30.00C.
sht31: high limit humidity is 50.00%.
sht31: low limit temperature is 25.00C.
sht31: low limit humidity is 30.00%.
sht31: irq alert pending status.
sht31: irq humidity alert.
sht31: irq temperature alert.
sht31: finish alert test.
```

```shell
./sht31 -e read --addr=0 --times=3

sht31: 1/3.
sht31: temperature is 29.59C.
sht31: humidity is 25.88%.
sht31: 2/3.
sht31: temperature is 29.44C.
sht31: humidity is 26.00%.
sht31: 3/3.
sht31: temperature is 29.35C.
sht31: humidity is 26.11%.
```

```shell
./sht31 -e shot --addr=0 --times=3

sht31: 1/3.
sht31: temperature is 29.14C.
sht31: humidity is 26.40%.
sht31: 2/3.
sht31: temperature is 29.13C.
sht31: humidity is 26.43%.
sht31: 3/3.
sht31: temperature is 29.13C.
sht31: humidity is 26.47%.
```

```shell
./sht31 -e alert --addr=0 --timeout=10000 --high-limit-temp=30.0 --high-limit-humi=50.0 --low-limit-temp=25.0 --low-limit-humi=30.0

sht31: high limit temperature is 30.00C.
sht31: high limit humidity is 50.00%.
sht31: low limit temperature is 25.00C.
sht31: low limit humidity is 30.00%.
sht31: irq alert pending status.
sht31: irq humidity alert.
sht31: irq temperature alert.
sht31: finish.
```

```shell
./sht31 -e sn --addr=0

sht31: serial number is 0x10 0xE2 0x41 0x1F.
```

```shell
./sht31 -h

Usage:
  sht31 (-i | --information)
  sht31 (-h | --help)
  sht31 (-p | --port)
  sht31 (-t reg | --test=reg) [--addr=<0 | 1>]
  sht31 (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]
  sht31 (-t alert | --test=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>]
        [--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]
  sht31 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]
  sht31 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]
  sht31 (-e alert | --example=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>]
        [--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]

Options:
      --addr=<0 | 1>    Set the addr pin.([default: 0])
  -e <read | shot | alert | sn>, --example=<read | shot | alert | sn>
                        Run the driver example.
      --low-limit-temp  Low limit temperature in degress.([default: 25.0])
      --low-limit-humi  Low limit humidity in percentage.([default: 30.0])
  -h, --help            Show the help.
      --high-limit-temp High limit temperature in degress.([default: 30.0])
      --high-limit-humi High limit humidity in percentage.([default: 50.0])
  -i, --information     Show the chip information.
  -p, --port            Display the pin connections of the current board.
  -t <reg | read | alert>, --test=<reg | read | alert>
                        Run the driver test.
      --times=<num>     Set the running times.([default: 3])
      --timeout=<ms>    Set timeout in ms.([default: 10000])
```

