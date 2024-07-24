//
// Created by dell on 2024-07-22.
//
#ifndef MODULE_INTERFACE_H
#define MODULE_INTERFACE_H

#include <stdint.h>
#include "at_command.h"
#include "module_interface.h"
#include "at_command_config.h"
#include <string.h>
#include <stdio.h>

/**
 * 模块接口
 * 以下接口为模块提供的功能
 */
typedef struct {
    /* 初始化接口 */
    int (*init)(void);
    /* 反初始化 */
    int (*deinit)(void);
    /* 发送命令 */
    at_status_t (*send_command)(const at_command_t *cmd, char *response, size_t response_size);
    /* 模块开机 */
    at_status_t (*power_on)(char *response, size_t response_size);
    /* 模块关机 */
    at_status_t (*power_off)(char *response, size_t response_size);
    /* 网络附着检测 */
    at_status_t (*network_attach_check)(void);
    /* 网络附着 */
    at_status_t (*attach_network)(char *response, size_t response_size);
    /* 网络去附着 */
    at_status_t (*detach_network)(char *response, size_t response_size);
    /* 创建套接字 */
    int (*open_socket)(ProtocolType type);
    /* 关闭套接字 */
    at_status_t (*close_socket)(char *response, size_t response_size);
    /* 连接TCP服务器 */
    at_status_t (*connect_tcp_server)(int socket_id,char *ip_addr, int port);
    /* 发送数据到TCP服务器 */
    at_status_t (*send_tcp_data)(int socket_id, const char *data, int length);
    /* 获取模块信号强度 */
    at_status_t (*get_signal_strength)(char *response, size_t response_size);
    /* 事件处理回调 */
    void (*handle_event)(const char *event);
} module_interface_t;

at_status_t module_send_command(const at_command_t *cmd, char *response, size_t response_size);
#endif // MODULE_INTERFACE_H
