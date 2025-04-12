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
#include "driver_sht31_alert_test.h"
#include "driver_sht31_basic.h"
#include "driver_sht31_shot.h"
#include "driver_sht31_alert.h"
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "gpio.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */
uint8_t (*g_gpio_irq)(void) = NULL;        /**< gpio irq */

/**
 * @brief exti 0 irq
 * @note  none
 */
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

/**
 * @brief     gpio exti callback
 * @param[in] pin gpio pin
 * @note      none
 */
void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    if (pin == GPIO_PIN_0)
    {
        if (g_gpio_irq != NULL)
        {
            g_gpio_irq();
        }
    }
}

/**
 * @brief     interface receive callback
 * @param[in] type receive type
 * @note      none
 */
static void a_receive_callback(uint16_t type)
{
    switch (type)
    {
        case SHT31_STATUS_ALERT_PENDING_STATUS :
        {
            sht31_interface_debug_print("sht31: irq alert pending status.\n");
            
            break;
        }
        case SHT31_STATUS_HUMIDITY_ALERT :
        {
            sht31_interface_debug_print("sht31: irq humidity alert.\n");
            
            break;
        }
        case SHT31_STATUS_TEMPERATURE_ALERT :
        {
            sht31_interface_debug_print("sht31: irq temperature alert.\n");
            
            break;
        }
    }
}

/**
 * @brief     sht31 full function
 * @param[in] argc arg numbers
 * @param[in] **argv arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t sht31(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"times", required_argument, NULL, 2},
        {"timeout", required_argument, NULL, 3},
        {"high-limit-temp", required_argument, NULL, 4},
        {"high-limit-humi", required_argument, NULL, 5},
        {"low-limit-temp", required_argument, NULL, 6},
        {"low-limit-humi", required_argument, NULL, 7},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    uint32_t timeout = 10000;
    float high_limit_temperature = 30.0f;
    float high_limit_humidity = 50.0f;
    float low_limit_temperature = 25.0f;
    float low_limit_humidity = 30.0f;
    sht31_address_t addr = SHT31_ADDRESS_0;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = SHT31_ADDRESS_0;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = SHT31_ADDRESS_1;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* running times */
            case 2 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* timeout */
            case 3 :
            {
                /* set the timeout */
                timeout = atol(optarg);
                
                break;
            } 
            
            /* high_limit_temperature */
            case 4 :
            {
                /* set the high limit temperature */
                high_limit_temperature = (float)atof(optarg);
                
                break;
            } 
            
            /* high_limit_humidity */
            case 5 :
            {
                /* set the high limit humidity */
                high_limit_humidity = (float)atof(optarg);
                
                break;
            } 
            
            /* low_limit_temperature */
            case 6 :
            {
                /* set the low limit temperature */
                low_limit_temperature = (float)atof(optarg);
                
                break;
            } 
            
            /* low_limit_humidity */
            case 7 :
            {
                /* set the low limit humidity */
                low_limit_humidity = (float)atof(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        /* run reg test */
        if (sht31_register_test(addr) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_read", type) == 0)
    {
        /* run read test */
        if (sht31_read_test(addr, times) != 0)
        {
            return 1;
        }
        
        return 0;
    }
    else if (strcmp("t_alert", type) == 0)
    {
        uint8_t res;
        
        /* gpio init */
        g_gpio_irq = sht31_alert_test_irq_handler;
        res = gpio_interrupt_init();
        if (res != 0)
        {
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* run alert test */
        if (sht31_alert_test(addr, high_limit_temperature, high_limit_humidity,
                             low_limit_temperature, low_limit_humidity, timeout) != 0)
        {
            gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        return 0;
    }
    else if (strcmp("e_sn", type) == 0)
    {
        uint8_t res;
        uint8_t sn[4];
        
        /* basic init */
        res = sht31_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* get serial number */
        res = sht31_basic_get_serial_number(sn);
        if (res != 0)
        {
            sht31_basic_deinit();
            
            return 1;
        }
        sht31_interface_debug_print("sht31: serial number is 0x%02X 0x%02X 0x%02X 0x%02X.\n", sn[0], sn[1], sn[2], sn[3]);
        
        /* basic deinit */
        (void)sht31_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature;
        float humidity;
        
        /* basic init */
        res = sht31_basic_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            sht31_interface_delay_ms(1000);
            
            /* read data */
            res = sht31_basic_read((float *)&temperature, (float *)&humidity);
            if (res != 0)
            {
                (void)sht31_basic_deinit();
                
                return 1;
            }
            
            /* output */
            sht31_interface_debug_print("sht31: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature);
            sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity);
        }
        
        /* basic deinit */
        (void)sht31_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        float temperature;
        float humidity;
        
        /* shot init */
        res = sht31_shot_init(addr);
        if (res != 0)
        {
            return 1;
        }
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            /* delay 1000ms */
            sht31_interface_delay_ms(1000);
            
            /* read data */
            res = sht31_shot_read((float *)&temperature, (float *)&humidity);
            if (res != 0)
            {
                (void)sht31_shot_deinit();
                
                return 1;
            }
            
            /* output */
            sht31_interface_debug_print("sht31: %d/%d.\n", (uint32_t)(i + 1), (uint32_t)times);
            sht31_interface_debug_print("sht31: temperature is %0.2fC.\n", temperature);
            sht31_interface_debug_print("sht31: humidity is %0.2f%%.\n", humidity);
        }
        
        /* shot deinit */
        (void)sht31_shot_deinit();
        
        return 0;
    }
    else if (strcmp("e_alert", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* gpio init */
        g_gpio_irq = sht31_alert_irq_handler;
        res = gpio_interrupt_init();
        if (res != 0)
        {
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* output */
        sht31_interface_debug_print("sht31: high limit temperature is %.02fC.\n", high_limit_temperature);
        sht31_interface_debug_print("sht31: high limit humidity is %.02f%%.\n", high_limit_humidity);
        sht31_interface_debug_print("sht31: low limit temperature is %.02fC.\n", low_limit_temperature);
        sht31_interface_debug_print("sht31: low limit humidity is %.02f%%.\n", low_limit_humidity);
        
        /* alert init */
        res = sht31_alert_init(addr, a_receive_callback,
                               high_limit_temperature, high_limit_humidity,
                               high_limit_temperature - 1.0f, high_limit_humidity + 1.0f,
                               low_limit_temperature, low_limit_humidity,
                               low_limit_temperature - 1.0f, low_limit_humidity + 1.0f);
        if (res != 0)
        {
            gpio_interrupt_deinit();
            g_gpio_irq = NULL;
            
            return 1;
        }
        
        /* loop */
        for (i = 0; i < timeout; i++)
        {
            /* delay 1ms */
            sht31_interface_delay_ms(1);
        }
        
        gpio_interrupt_deinit();
        g_gpio_irq = NULL;
        
        /* finish */
        sht31_interface_debug_print("sht31: finish.\n");
        
        /* alert deinit */
        (void)sht31_alert_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        sht31_interface_debug_print("Usage:\n");
        sht31_interface_debug_print("  sht31 (-i | --information)\n");
        sht31_interface_debug_print("  sht31 (-h | --help)\n");
        sht31_interface_debug_print("  sht31 (-p | --port)\n");
        sht31_interface_debug_print("  sht31 (-t reg | --test=reg) [--addr=<0 | 1>]\n");
        sht31_interface_debug_print("  sht31 (-t read | --test=read) [--addr=<0 | 1>] [--times=<num>]\n");
        sht31_interface_debug_print("  sht31 (-t alert | --test=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>]\n");
        sht31_interface_debug_print("        [--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]\n");
        sht31_interface_debug_print("  sht31 (-e read | --example=read) [--addr=<0 | 1>] [--times=<num>]\n");
        sht31_interface_debug_print("  sht31 (-e shot | --example=shot) [--addr=<0 | 1>] [--times=<num>]\n");
        sht31_interface_debug_print("  sht31 (-e alert | --example=alert) [--addr=<0 | 1>] [--timeout=<ms>] [--high-limit-temp=<degree>] [--high-limit-humi=<percentage>]\n");
        sht31_interface_debug_print("        [--low-limit-temp=<degree>] [--low-limit-humi=<percentage>]\n");
        sht31_interface_debug_print("\n");
        sht31_interface_debug_print("Options:\n");
        sht31_interface_debug_print("      --addr=<0 | 1>    Set the addr pin.([default: 0])\n");
        sht31_interface_debug_print("  -e <read | shot | alert | sn>, --example=<read | shot | alert | sn>\n");
        sht31_interface_debug_print("                        Run the driver example.\n");
        sht31_interface_debug_print("      --low-limit-temp  Low limit temperature in degress.([default: 25.0])\n");
        sht31_interface_debug_print("      --low-limit-humi  Low limit humidity in percentage.([default: 30.0])\n");
        sht31_interface_debug_print("  -h, --help            Show the help.\n");
        sht31_interface_debug_print("      --high-limit-temp High limit temperature in degress.([default: 30.0])\n");
        sht31_interface_debug_print("      --high-limit-humi High limit humidity in percentage.([default: 50.0])\n");
        sht31_interface_debug_print("  -i, --information     Show the chip information.\n");
        sht31_interface_debug_print("  -p, --port            Display the pin connections of the current board.\n");
        sht31_interface_debug_print("  -t <reg | read | alert>, --test=<reg | read | alert>\n");
        sht31_interface_debug_print("                        Run the driver test.\n");
        sht31_interface_debug_print("      --times=<num>     Set the running times.([default: 3])\n");
        sht31_interface_debug_print("      --timeout=<ms>    Set timeout in ms.([default: 10000])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
    {
        sht31_info_t info;
        
        /* print sht31 info */
        sht31_info(&info);
        sht31_interface_debug_print("sht31: chip is %s.\n", info.chip_name);
        sht31_interface_debug_print("sht31: manufacturer is %s.\n", info.manufacturer_name);
        sht31_interface_debug_print("sht31: interface is %s.\n", info.interface);
        sht31_interface_debug_print("sht31: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        sht31_interface_debug_print("sht31: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        sht31_interface_debug_print("sht31: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        sht31_interface_debug_print("sht31: max current is %0.2fmA.\n", info.max_current_ma);
        sht31_interface_debug_print("sht31: max temperature is %0.1fC.\n", info.temperature_max);
        sht31_interface_debug_print("sht31: min temperature is %0.1fC.\n", info.temperature_min);
        
        return 0;
    }
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        sht31_interface_debug_print("sht31: SCL connected to GPIOB PIN8.\n");
        sht31_interface_debug_print("sht31: SDA connected to GPIOB PIN9.\n");
        sht31_interface_debug_print("sht31: ALERT connected to GPIOB PIN0.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register sht31 function */
    shell_init();
    shell_register("sht31", sht31);
    uart_print("sht31: welcome to libdriver sht31.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("sht31: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("sht31: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("sht31: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("sht31: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("sht31: param is invalid.\n");
            }
            else
            {
                uart_print("sht31: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
