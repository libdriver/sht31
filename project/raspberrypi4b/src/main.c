/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      main.c
 * @brief     main source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-03-05
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/05  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_sht31_register_test.h"
#include "driver_sht31_read_test.h"
#include "driver_sht31_basic.h"
#include "driver_sht31_shot.h"
#include <stdlib.h>

/**
 * @brief     sht31 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t sht31(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            sht31_info_t info;
            
            /* print sht31 info */
            sht31_info(&info);
            sht31_interface_debug_print("sht31: chip is %s.\n", info.chip_name);
            sht31_interface_debug_print("sht31: manufacturer is %s.\n", info.manufacturer_name);
            sht31_interface_debug_print("sht31: interface is %s.\n", info.interface);
            sht31_interface_debug_print("sht31: driver version is %d.%d.\n", info.driver_version/1000, (info.driver_version%1000)/100);
            sht31_interface_debug_print("sht31: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            sht31_interface_debug_print("sht31: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            sht31_interface_debug_print("sht31: max current is %0.2fmA.\n", info.max_current_ma);
            sht31_interface_debug_print("sht31: max temperature is %0.1fC.\n", info.temperature_max);
            sht31_interface_debug_print("sht31: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            sht31_interface_debug_print("sht31: SCL connected to GPIO3(BCM).\n");
            sht31_interface_debug_print("sht31: SDA connected to GPIO2(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show sht31 help */
         
            help:
            
            sht31_interface_debug_print("sht31 -i\n\tshow sht31 chip and driver information.\n");
            sht31_interface_debug_print("sht31 -h\n\tshow sht31 help.\n");
            sht31_interface_debug_print("sht31 -p\n\tshow sht31 pin connections of the current board.\n");
            sht31_interface_debug_print("sht31 -t reg -a (0 | 1)\n\trun sht31 register test.\n");
            sht31_interface_debug_print("sht31 -t read <times> -a (0 | 1)\n\trun sht31 read test.times is test times.\n");
            sht31_interface_debug_print("sht31 -c read <times> -a (0 | 1)\n\trun sht31 read function.times is read times.\n");
            sht31_interface_debug_print("sht31 -c shot <times> -a (0 | 1)\n\trun sht31 shot function.times is read times.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* reg test */
            if (strcmp("reg", argv[2]) == 0)
            {
                sht31_address_t addr_pin;
                
                if (strcmp("-a", argv[3]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[4]) == 0)
                {
                    addr_pin = SHT31_ADDRESS_0;
                }
                else if (strcmp("1", argv[4]) == 0)
                {
                    addr_pin = SHT31_ADDRESS_1;
                }
                else
                {
                    sht31_interface_debug_print("sht31 : address is invalid.\n");
                    
                    return 5;
                }
                /* run reg test */
                if (sht31_register_test(addr_pin))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    else if (argc == 6)
    {
        /* run test */
        if (strcmp("-t", argv[1]) == 0)
        {
             /* read test */
            if (strcmp("read", argv[2]) == 0)
            {
                sht31_address_t addr_pin;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr_pin = SHT31_ADDRESS_0;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr_pin = SHT31_ADDRESS_1;
                }
                else
                {
                    sht31_interface_debug_print("sht31 : address is invalid.\n");
                    
                    return 5;
                }
                
                /* run read test */
                if (sht31_read_test(addr_pin, atoi(argv[3])))
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* run function */
        else if (strcmp("-c", argv[1]) == 0)
        {
            /* read function */
            if (strcmp("read", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times;
                volatile uint32_t i;
                volatile float temperature;
                volatile float humidity;
                sht31_address_t addr_pin;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr_pin = SHT31_ADDRESS_0;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr_pin = SHT31_ADDRESS_1;
                }
                else
                {
                    sht31_interface_debug_print("sht31 : address is invalid.\n");
                    
                    return 5;
                }
                res = sht31_basic_init(addr_pin);
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    sht31_interface_delay_ms(1000);
                    res = sht31_basic_read((float *)&temperature, (float *)&humidity);
                    if (res)
                    {
                        sht31_basic_deinit();
                        
                        return 1;
                    }
                    sht31_interface_debug_print("sht31: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature);
                    sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity);
                }
                sht31_basic_deinit();
                
                return 0;
            }
            /* shot function */
            else if (strcmp("shot", argv[2]) == 0)
            {
                volatile uint8_t res;
                volatile uint32_t times;
                volatile uint32_t i;
                volatile float temperature;
                volatile float humidity;
                sht31_address_t addr_pin;
                
                if (strcmp("-a", argv[4]) != 0)
                {
                    return 5;
                }
                if (strcmp("0", argv[5]) == 0)
                {
                    addr_pin = SHT31_ADDRESS_0;
                }
                else if (strcmp("1", argv[5]) == 0)
                {
                    addr_pin = SHT31_ADDRESS_1;
                }
                else
                {
                    sht31_interface_debug_print("sht31 : address is invalid.\n");
                    
                    return 5;
                }
                res = sht31_shot_init(addr_pin);
                if (res)
                {
                    return 1;
                }
                times = atoi(argv[3]);
                for (i=0; i<times; i++)
                {
                    sht31_interface_delay_ms(1000);
                    res = sht31_shot_read((float *)&temperature, (float *)&humidity);
                    if (res)
                    {
                        sht31_shot_deinit();
                        
                        return 1;
                    }
                    sht31_interface_debug_print("sht31: %d/%d.\n", (uint32_t)(i+1), (uint32_t)times);
                    sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature);
                    sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity);
                }
                sht31_shot_deinit();
                
                return 0;
            }
            /* param is invalid */
            else
            {
                return 5;
            }
        }
        /* param is invalid */
        else
        {
            return 5;
        }
    }
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = sht31(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        sht31_interface_debug_print("sht31: run failed.\n");
    }
    else if (res == 5)
    {
        sht31_interface_debug_print("sht31: param is invalid.\n");
    }
    else
    {
        sht31_interface_debug_print("sht31: unknow status code.\n");
    }

    return 0;
}