//
// Created by dell on 2024-07-22.
//
#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdint.h>
#include <stddef.h>


// 定时器接口
void platform_delay_ms(unsigned int ms);
void platform_uart_init(void);
void platform_uart_deinit(void);
void platform_uart_send(const char *data, unsigned int length);
int platform_uart_receive(char *buffer, unsigned int length);
// 中断接口
void platform_enable_interrupts(void);
void platform_disable_interrupts(void);

#endif // PLATFORM_H
