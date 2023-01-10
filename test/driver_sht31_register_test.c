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
 * @file      driver_sht31_register_test.c
 * @brief     driver sht31 register test source file
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
 
#include "driver_sht31_register_test.h"
#include <stdlib.h>

static sht31_handle_t gs_handle;        /**< sht31 handle */

/**
 * @brief     register test
 * @param[in] addr_pin is the iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t sht31_register_test(sht31_address_t addr_pin)
{
    uint8_t res;
    uint16_t status;
    sht31_info_t info;
    sht31_address_t address_pin;
    sht31_repeatability_t repeatability;
    
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
    
    /* start register test */
    sht31_interface_debug_print("sht31: start register test.\n");
    
    /* sht31_set_addr_pin/sht31_get_addr_pin test */
    sht31_interface_debug_print("sht31: sht31_set_addr_pin/sht31_get_addr_pin test.\n");
    
    /* set address pin 0 */
    res = sht31_set_addr_pin(&gs_handle, SHT31_ADDRESS_0);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set addr pin failed.\n");
       
        return 1;
    }
    sht31_interface_debug_print("sht31: set address pin 0.\n");
    res = sht31_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: get addr pin failed.\n");
       
        return 1;
    }
    sht31_interface_debug_print("sht31: check addr pin %s.\n", (SHT31_ADDRESS_0==address_pin)?"ok":"error");
    
    /* set address pin 1 */
    res = sht31_set_addr_pin(&gs_handle, SHT31_ADDRESS_1);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set addr pin failed.\n");
       
        return 1;
    }
    sht31_interface_debug_print("sht31: set address pin 1.\n");
    res = sht31_get_addr_pin(&gs_handle, &address_pin);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: get addr pin failed.\n");
       
        return 1;
    }
    sht31_interface_debug_print("sht31: check addr pin %s.\n", (SHT31_ADDRESS_1==address_pin)?"ok":"error");
    
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
    
    /* sht31_set_repeatability/sht31_get_repeatability test */
    sht31_interface_debug_print("sht31: sht31_set_repeatability/sht31_get_repeatability test.\n");
    
    /* set high */
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_HIGH);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    sht31_interface_debug_print("sht31: set repeatability high.\n");
    res = sht31_get_repeatability(&gs_handle, &repeatability);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: get repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    sht31_interface_debug_print("sht31: check repeatability pin %s.\n", (SHT31_REPEATABILITY_HIGH==repeatability)?"ok":"error");
    
    /* set medium */
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_MEDIUM);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    sht31_interface_debug_print("sht31: set repeatability medium.\n");
    res = sht31_get_repeatability(&gs_handle, &repeatability);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: get repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    sht31_interface_debug_print("sht31: check repeatability pin %s.\n", (SHT31_REPEATABILITY_MEDIUM==repeatability)?"ok":"error");
    
    /* set low */
    res = sht31_set_repeatability(&gs_handle, SHT31_REPEATABILITY_LOW);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    sht31_interface_debug_print("sht31: set repeatability low.\n");
    res = sht31_get_repeatability(&gs_handle, &repeatability);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: get repeatability failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    sht31_interface_debug_print("sht31: check repeatability pin %s.\n", (SHT31_REPEATABILITY_LOW==repeatability)?"ok":"error");
    
    /* set art test */
    sht31_interface_debug_print("sht31: set art test.\n");
    res = sht31_set_art(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set art failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    sht31_interface_debug_print("sht31: check art %s.\n", (res==0)?"ok":"error");
    
    /* sht31_set_heater test*/
    sht31_interface_debug_print("sht31: set heater test.\n");
    
    /* enable heater */
    res = sht31_set_heater(&gs_handle, SHT31_BOOL_TRUE);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set heater failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    sht31_interface_debug_print("sht31: enable heater.\n");
    sht31_interface_debug_print("sht31: check heater %s.\n", (res==0)?"ok":"error");
    
    /* disable heater */
    res = sht31_set_heater(&gs_handle, SHT31_BOOL_FALSE);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: set heater failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    sht31_interface_debug_print("sht31: disable heater.\n");
    sht31_interface_debug_print("sht31: check heater %s.\n", (res==0)?"ok":"error");
    
    /* get_status test*/
    sht31_interface_debug_print("sht31: get status test.\n");
    res = sht31_get_status(&gs_handle, (uint16_t *)&status);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: get status failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    sht31_interface_debug_print("sht31: check status 0x%02X.\n", status);
    
    /* clear_status test*/
    sht31_interface_debug_print("sht31: clear status test.\n");
    res = sht31_clear_status(&gs_handle);
    if (res != 0)
    {
        sht31_interface_debug_print("sht31: clear status failed.\n");
        (void)sht31_deinit(&gs_handle);
       
        return 1;
    }
    
    /* wait 10 ms */
    sht31_interface_delay_ms(10);
    sht31_interface_debug_print("sht31: check clear status %s.\n", (res==0)?"ok":"error");
    
    /* finish register test */
    sht31_interface_debug_print("sht31: finish register test.\n");
    (void)sht31_deinit(&gs_handle);
    
    return 0;
}
