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
 * @file      driver_sht31_read_test.c
 * @brief     driver sht31 read test source file
 * @version   2.0.0
 * @author    Shifeng Li
 * @date      2021-03-05
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/03/05  <td>2.0      <td>Shifeng Li  <td>format the code
 * <tr><td>2020/11/03  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_sht31_read_test.h"

static sht31_handle_t gs_handle;        /**< sht31 handle */

/**
 * @brief     read test
 * @param[in] addr_pin is the iic device address
 * @param[in] times is test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sht31_read_test(sht31_address_t addr_pin, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    sht31_info_t info;
    
    /* link functions */
    DRIVER_SHT31_LINK_INIT(&gs_handle, sht31_handle_t);
    DRIVER_SHT31_LINK_IIC_INIT(&gs_handle, sht31_interface_iic_init);
    DRIVER_SHT31_LINK_IIC_DEINIT(&gs_handle, sht31_interface_iic_deinit);
    DRIVER_SHT31_LINK_IIC_READ_ADDRESS16(&gs_handle, sht31_interface_iic_read_address16);
    DRIVER_SHT31_LINK_IIC_WRITE_ADDRESS16(&gs_handle, sht31_interface_iic_write_address16);
    DRIVER_SHT31_LINK_DELAY_MS(&gs_handle, sht31_interface_delay_ms);
    DRIVER_SHT31_LINK_DEBUG_PRINT(&gs_handle, sht31_interface_debug_print);
    
    /* sht31 info */
    res = sht31_info(&info);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: get info failed.\n");
       
        return 1;
    }
    else
    {
        /* print chip information */
        sht31_interface_debug_print("sht31: chip is %s.\n", info.chip_name);
        sht31_interface_debug_print("sht31: manufacturer is %s.\n", info.manufacturer_name);
        sht31_interface_debug_print("sht31: interface is %s.\n", info.interface);
        sht31_interface_debug_print("sht31: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sht31_interface_debug_print("sht31: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sht31_interface_debug_print("sht31: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sht31_interface_debug_print("sht31: max current is %0.2fmA.\n", info.max_current_ma);
        sht31_interface_debug_print("sht31: max temperature is %0.1fC.\n", info.temperature_max);
        sht31_interface_debug_print("sht31: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
    /* start read test */
    sht31_interface_debug_print("sht31: start read test.\n");
    
    /* set address pin */
    res = sht31_set_addr_pin(&gs_handle, addr_pin);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set addr pin failed.\n");
       
        return 1;
    }
    
    /* sht31 init */
    res = sht31_init(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: init failed.\n");
       
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    
    /* set art */
    res = sht31_set_art(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set art failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    
    /* set default heater */
    res = sht31_set_heater(&gs_handle, SHT31_BOOL_TRUE);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set heater failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    sht31_interface_debug_print("sht31: continuous read.\n");
    
    /* set low repeatability */
    sht31_interface_debug_print("sht31: set low repeatability.\n");
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_LOW);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rate 0.5Hz */
    sht31_interface_debug_print("sht31: set rate 0.5Hz.\n");
    
    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_0P5HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);
    
        /* wait 2500 ms */
        sht31_interface_delay_ms(2500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 1Hz */
    sht31_interface_debug_print("sht31: set rate 1Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_1HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1500 ms */
        sht31_interface_delay_ms(1500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 2Hz */
    sht31_interface_debug_print("sht31: set rate 2Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_2HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht31_interface_delay_ms(1000);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 4Hz */
    sht31_interface_debug_print("sht31: set rate 4Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_4HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht31_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 10Hz */
    sht31_interface_debug_print("sht31: set rate 10Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_10HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht31_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set medium repeatability */
    sht31_interface_debug_print("sht31: set medium repeatability.\n");
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_MEDIUM);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rate 0.5Hz */
    sht31_interface_debug_print("sht31: set rate 0.5Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_0P5HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 2500 ms */
        sht31_interface_delay_ms(2500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 1Hz */
    sht31_interface_debug_print("sht31: set rate 1Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_1HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1500 ms */
        sht31_interface_delay_ms(1500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 2Hz */
    sht31_interface_debug_print("sht31: set rate 2Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_2HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht31_interface_delay_ms(1000);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 4Hz */
    sht31_interface_debug_print("sht31: set rate 4Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_4HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht31_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 10Hz */
    sht31_interface_debug_print("sht31: set rate 10Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_10HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht31_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set high repeatability */
    sht31_interface_debug_print("sht31: set high repeatability.\n");
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_HIGH);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set rate 0.5Hz */
    sht31_interface_debug_print("sht31: set rate 0.5Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_0P5HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 2500 ms */
        sht31_interface_delay_ms(2500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 1Hz */
    sht31_interface_debug_print("sht31: set rate 1Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_1HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1500 ms */
        sht31_interface_delay_ms(1500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 2Hz */
    sht31_interface_debug_print("sht31: set rate 2Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_2HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht31_interface_delay_ms(1000);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 4Hz */
    sht31_interface_debug_print("sht31: set rate 4Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_4HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht31_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* set rate 10Hz */
    sht31_interface_debug_print("sht31: set rate 10Hz.\n");

    /* start continuous read */
    res = sht31_start_continuous_read(&gs_handle, SHT31_RATE_10HZ);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: start continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_continuous_read(&gs_handle, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: continuous read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 500 ms */
        sht31_interface_delay_ms(500);
    }

    /* stop continuous read */
    res = sht31_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: stop continuous failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }

    /* wait 10 ms */
    sht31_interface_delay_ms(10);

    /* link iic read address16 with scl */
    DRIVER_SHT31_LINK_IIC_READ_ADDRESS16(&gs_handle, sht31_interface_iic_scl_read_address16);
    sht31_interface_debug_print("sht31: single read.\n");

    /* set low repeatability */
    sht31_interface_debug_print("sht31: set low repeatability.\n");
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_LOW);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_single_read(&gs_handle, SHT31_BOOL_TRUE, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: single read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht31_interface_delay_ms(1000);
    }

    /* set medium repeatability */
    sht31_interface_debug_print("sht31: set medium repeatability.\n");
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_MEDIUM);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_single_read(&gs_handle, SHT31_BOOL_TRUE, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: single read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht31_interface_delay_ms(1000);
    }

    /* set high repeatability */
    sht31_interface_debug_print("sht31: set high repeatability.\n");
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_HIGH);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
        
        return 1;
    }
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_single_read(&gs_handle, SHT31_BOOL_TRUE, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: single read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht31_interface_delay_ms(1000);
    }

    /* disable clock stretching */
    sht31_interface_debug_print("sht31: disable clock stretching.\n");
    for (i = 0; i < times; i++)
    {
        uint16_t temperature_raw;
        float temperature_s;
        uint16_t humidity_raw;
        float humidity_s;
        
        res = sht31_single_read(&gs_handle, SHT31_BOOL_FALSE, (uint16_t *)&temperature_raw, (float *)&temperature_s, (uint16_t *)&humidity_raw, (float *)&humidity_s);
        if (res != 0)
        {
            sht31_interface_debug_print("sht31: single read failed.\n");
            (void)sht31_deinit(&gs_handle);
            
            return 1;
        }
        sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature_s);
        sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity_s);

        /* wait 1000 ms */
        sht31_interface_delay_ms(1000);
    }

    /* finish read test */
    sht31_interface_debug_print("sht31: finish read test.\n");
    (void)sht31_deinit(&gs_handle);

    return 0;
}
