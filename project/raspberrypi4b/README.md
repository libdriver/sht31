### 1. Chip

#### 1.1 Chip Info

chip name : Raspberry Pi 4B.

iic pin: SCL/SDA GPIO3/GPIO2.

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

​          sht31 is a basic command which can test all sht31 driver function:

​           -i        show sht31 chip and driver information.

​           -h       show sht31 help.

​           -p       show sht31 pin connections of the current board.

​           -t (reg -a (0 | 1)| read <times> -a (0 | 1))

​           -t reg -a (0 | 1)        run sht31 register test.

​           -t read <times> -a (0 | 1)        run sht31 read test. times is test times.

​           -c (read <times> -a (0 | 1) | shot <times> -a (0 | 1))

​           -c read <times> -a (0 | 1)      run sht31 read function. times is read times.

​           -c shot <times> -a (0 | 1)       run sht31 shot function. times is read times.

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
./sht31 -t reg -a 0

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
sht31: check status 0x8860.
sht31: clear status test.
sht31: check clear status ok.
sht31: finish register test.
```

```shell
./sht31 -t read 3 -a 0

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
sht31: temperature is 25.05C.
sht31: humidity is 20.98%.
sht31: temperature is 25.88C.
sht31: humidity is 20.93%.
sht31: temperature is 25.87C.
sht31: humidity is 20.74%.
sht31: set rate 1Hz.
sht31: temperature is 26.08C.
sht31: humidity is 20.39%.
sht31: temperature is 26.13C.
sht31: humidity is 20.44%.
sht31: temperature is 26.22C.
sht31: humidity is 20.12%.
sht31: set rate 2Hz.
sht31: temperature is 26.18C.
sht31: humidity is 20.27%.
sht31: temperature is 26.25C.
sht31: humidity is 20.17%.
sht31: temperature is 26.18C.
sht31: humidity is 20.27%.
sht31: set rate 4Hz.
sht31: temperature is 26.25C.
sht31: humidity is 20.13%.
sht31: temperature is 26.33C.
sht31: humidity is 20.24%.
sht31: temperature is 26.36C.
sht31: humidity is 20.21%.
sht31: set rate 10Hz.
sht31: temperature is 26.25C.
sht31: humidity is 20.16%.
sht31: temperature is 26.26C.
sht31: humidity is 20.19%.
sht31: temperature is 26.29C.
sht31: humidity is 20.18%.
sht31: set medium repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 26.36C.
sht31: humidity is 20.12%.
sht31: temperature is 26.33C.
sht31: humidity is 20.07%.
sht31: temperature is 26.39C.
sht31: humidity is 19.95%.
sht31: set rate 1Hz.
sht31: temperature is 26.43C.
sht31: humidity is 20.10%.
sht31: temperature is 26.43C.
sht31: humidity is 19.91%.
sht31: temperature is 26.46C.
sht31: humidity is 20.14%.
sht31: set rate 2Hz.
sht31: temperature is 26.52C.
sht31: humidity is 20.03%.
sht31: temperature is 26.53C.
sht31: humidity is 19.93%.
sht31: temperature is 26.50C.
sht31: humidity is 19.99%.
sht31: set rate 4Hz.
sht31: temperature is 26.53C.
sht31: humidity is 20.00%.
sht31: temperature is 26.52C.
sht31: humidity is 19.93%.
sht31: temperature is 26.56C.
sht31: humidity is 19.85%.
sht31: set rate 10Hz.
sht31: temperature is 26.57C.
sht31: humidity is 19.87%.
sht31: temperature is 26.56C.
sht31: humidity is 19.92%.
sht31: temperature is 26.50C.
sht31: humidity is 19.86%.
sht31: set high repeatability.
sht31: set rate 0.5Hz.
sht31: temperature is 26.68C.
sht31: humidity is 19.84%.
sht31: temperature is 26.60C.
sht31: humidity is 19.86%.
sht31: temperature is 26.61C.
sht31: humidity is 19.86%.
sht31: set rate 1Hz.
sht31: temperature is 26.64C.
sht31: humidity is 19.71%.
sht31: temperature is 26.67C.
sht31: humidity is 19.78%.
sht31: temperature is 26.66C.
sht31: humidity is 19.78%.
sht31: set rate 2Hz.
sht31: temperature is 26.71C.
sht31: humidity is 19.83%.
sht31: temperature is 26.67C.
sht31: humidity is 19.73%.
sht31: temperature is 26.68C.
sht31: humidity is 19.78%.
sht31: set rate 4Hz.
sht31: temperature is 26.68C.
sht31: humidity is 19.83%.
sht31: temperature is 26.68C.
sht31: humidity is 19.76%.
sht31: temperature is 26.71C.
sht31: humidity is 19.78%.
sht31: set rate 10Hz.
sht31: temperature is 26.71C.
sht31: humidity is 19.96%.
sht31: temperature is 26.74C.
sht31: humidity is 19.93%.
sht31: temperature is 26.71C.
sht31: humidity is 19.97%.
sht31: single read.
sht31: set low repeatability.
sht31: temperature is 26.68C.
sht31: humidity is 20.02%.
sht31: temperature is 26.64C.
sht31: humidity is 19.94%.
sht31: temperature is 26.73C.
sht31: humidity is 19.96%.
sht31: set medium repeatability.
sht31: temperature is 26.74C.
sht31: humidity is 19.96%.
sht31: temperature is 26.73C.
sht31: humidity is 20.02%.
sht31: temperature is 26.76C.
sht31: humidity is 20.07%.
sht31: set high repeatability.
sht31: temperature is 26.76C.
sht31: humidity is 20.18%.
sht31: temperature is 26.73C.
sht31: humidity is 20.14%.
sht31: temperature is 26.76C.
sht31: humidity is 20.22%.
sht31: disable clock stretching.
sht31: temperature is 26.77C.
sht31: humidity is 20.09%.
sht31: temperature is 26.76C.
sht31: humidity is 20.04%.
sht31: temperature is 26.78C.
sht31: humidity is 20.06%.
sht31: finish read test.
```

```shell
./sht31 -c read 3 -a 0

sht31: 1/3.
sht31: temperature is 28.44C.
sht31: humidity is 19.86%.
sht31: 2/3.
sht31: temperature is 28.46C.
sht31: humidity is 19.86%.
sht31: 3/3.
sht31: temperature is 28.47C.
sht31: humidity is 19.79%.
```

```shell
./sht31 -c shot 3 -a 0

sht31: 1/3.
sht31: temperature is 28.66C.
sht31: humidity is 19.57%.
sht31: 2/3.
sht31: temperature is 28.60C.
sht31: humidity is 19.59%.
sht31: 3/3.
sht31: temperature is 28.63C.
sht31: humidity is 19.56%.
```

```shell
./sht31 -h

sht31 -i
	show sht31 chip and driver information.
sht31 -h
	show sht31 help.
sht31 -p
	show sht31 pin connections of the current board.
sht31 -t reg -a (0 | 1)
	run sht31 register test.
sht31 -t read <times> -a (0 | 1)
	run sht31 read test.times is test times.
sht31 -c read <times> -a (0 | 1)
	run sht31 read function.times is read times.
sht31 -c shot <times> -a (0 | 1)
	run sht31 shot function.times is read times.
```

