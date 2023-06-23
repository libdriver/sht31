### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

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
sht31 -i

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
sht31 -p

sht31: SCL connected to GPIOB PIN8.
sht31: SDA connected to GPIOB PIN9.
```

```shell
sht31 -t reg --addr=0

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
sht31 -t read --addr=0 --times=3

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
sht31: temperature is 29.69C.
sht31: humidity is 27.99%.
sht31: temperature is 30.44C.
sht31: humidity is 27.79%.
sht31: temperature is 30.64C.
sht31: humidity is 27.56%.
sht31: set rate 1Hz.
sht31: temperature is 30.59C.
sht31: humidity is 27.36%.
sht31: temperature is 30.57C.
sht31: humidity is 27.24%.
sht31: temperature is 30.69C.
sht31: humidity is 27.53%.
sht31: set rate 2Hz.
sht31: temperature is 30.65C.
sht31: humidity is 28.44%.
sht31: temperature is 30.72C.
sht31: humidity is 28.26%.
sht31: temperature is 30.72C.
sht31: humidity is 28.02%.
sht31: set rate 4Hz.
sht31: temperature is 30.74C.
sht31: humidity is 27.77%.
sht31: temperature is 30.64C.
sht31: humidity is 27.69%.
sht31: temperature is 30.72C.
sht31: humidity is 27.49%.
sht31: set rate 10Hz.
sht31: temperature is 30.71C.
sht31: humidity is 27.55%.
sht31: temperature is 30.72C.
sht31: humidity is 27.48%.
sht31: temperature is 30.69C.
sht31: humidity is 27.37%.
sht31: set medium repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 30.74C.
sht31: humidity is 27.43%.
sht31: temperature is 30.81C.
sht31: humidity is 27.47%.
sht31: temperature is 30.75C.
sht31: humidity is 27.49%.
sht31: set rate 1Hz.
sht31: temperature is 30.78C.
sht31: humidity is 27.50%.
sht31: temperature is 30.75C.
sht31: humidity is 27.39%.
sht31: temperature is 30.78C.
sht31: humidity is 27.30%.
sht31: set rate 2Hz.
sht31: temperature is 30.83C.
sht31: humidity is 27.38%.
sht31: temperature is 30.76C.
sht31: humidity is 27.42%.
sht31: temperature is 30.79C.
sht31: humidity is 27.42%.
sht31: set rate 4Hz.
sht31: temperature is 30.79C.
sht31: humidity is 27.51%.
sht31: temperature is 30.81C.
sht31: humidity is 27.60%.
sht31: temperature is 30.81C.
sht31: humidity is 27.72%.
sht31: set rate 10Hz.
sht31: temperature is 30.82C.
sht31: humidity is 27.90%.
sht31: temperature is 30.79C.
sht31: humidity is 27.96%.
sht31: temperature is 30.79C.
sht31: humidity is 28.09%.
sht31: set high repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 30.85C.
sht31: humidity is 28.11%.
sht31: temperature is 30.82C.
sht31: humidity is 28.29%.
sht31: temperature is 30.82C.
sht31: humidity is 28.21%.
sht31: set rate 1Hz.
sht31: temperature is 30.89C.
sht31: humidity is 28.05%.
sht31: temperature is 30.83C.
sht31: humidity is 27.86%.
sht31: temperature is 30.86C.
sht31: humidity is 27.68%.
sht31: set rate 2Hz.
sht31: temperature is 30.83C.
sht31: humidity is 27.57%.
sht31: temperature is 30.83C.
sht31: humidity is 27.54%.
sht31: temperature is 30.85C.
sht31: humidity is 27.47%.
sht31: set rate 4Hz.
sht31: temperature is 30.83C.
sht31: humidity is 27.45%.
sht31: temperature is 30.86C.
sht31: humidity is 27.34%.
sht31: temperature is 30.87C.
sht31: humidity is 27.32%.
sht31: set rate 10Hz.
sht31: temperature is 30.81C.
sht31: humidity is 27.18%.
sht31: temperature is 30.85C.
sht31: humidity is 27.40%.
sht31: temperature is 30.86C.
sht31: humidity is 27.44%.
sht31: single read.
sht31: set low repeatability.
sht31: temperature is 30.87C.
sht31: humidity is 27.56%.
sht31: temperature is 30.81C.
sht31: humidity is 27.72%.
sht31: temperature is 30.83C.
sht31: humidity is 27.57%.
sht31: set medium repeatability.
sht31: temperature is 30.90C.
sht31: humidity is 27.65%.
sht31: temperature is 30.82C.
sht31: humidity is 27.59%.
sht31: temperature is 30.87C.
sht31: humidity is 27.68%.
sht31: set high repeatability.
sht31: temperature is 30.85C.
sht31: humidity is 27.63%.
sht31: temperature is 30.86C.
sht31: humidity is 27.65%.
sht31: temperature is 30.85C.
sht31: humidity is 27.56%.
sht31: disable clock stretching.
sht31: temperature is 30.85C.
sht31: humidity is 27.59%.
sht31: temperature is 30.86C.
sht31: humidity is 27.81%.
sht31: temperature is 30.86C.
sht31: humidity is 28.47%.
sht31: finish read test.
```

```shell
sht31 -e read --addr=0 --times=3

sht31: 1/3.
sht31: temperature is 31.00C.
sht31: humidity is 27.47%.
sht31: 2/3.
sht31: temperature is 31.03C.
sht31: humidity is 27.68%.
sht31: 3/3.
sht31: temperature is 31.02C.
sht31: humidity is 27.66%.
```

```shell
sht31 -e shot --addr=0 --times=3

sht31: 1/3.
sht31: temperature is 30.89C.
sht31: humidity is 27.58%.
sht31: 2/3.
sht31: temperature is 30.90C.
sht31: humidity is 27.48%.
sht31: 3/3.
sht31: temperature is 30.92C.
sht31: humidity is 27.44%.
```

```shell
sht31 -h

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

