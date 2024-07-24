//
// Created by dell on 2024-07-22.
//

#ifndef AT_COMMAND_CONFIG_H
#define AT_COMMAND_CONFIG_H

#include "at_command.h"

/**
 * AT指令配置结构体
 */
typedef struct {
    at_command_t init_cmd;
    at_command_t module_info_cmd;
    at_command_t network_attach_check_cmd;
    at_command_t attach_network_cmd;
    at_command_t detach_network_cmd;
    at_command_t get_signal_strength_cmd;
    at_command_t power_on_cmd;
    at_command_t power_off_cmd;
    at_command_t open_socket_cmd;
    at_command_t close_socket_cmd;
    at_command_t connect_tcp_server_cmd;
    at_command_t send_tcp_data_cmd;
    at_command_t receive_tcp_data_cmd;
    // 添加其他类别的AT指令
} at_command_config_t;

/**
 * 协议类型
 */
typedef enum {
    TCP,
    UDP
} ProtocolType;


extern const at_command_config_t e36_command_config;
extern const at_command_config_t ec800m_command_config;

#endif // AT_COMMAND_CONFIG_H
