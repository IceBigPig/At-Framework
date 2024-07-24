//
// Created by dell on 2024-07-22.
//

#include <stdlib.h>
#include <ctype.h>
#include "module_interface.h"
#include "at_command_config.h"
#include "e36_module.h"
#include "platform.h"


static const at_command_config_t *e36_config = &e36_command_config;

// 定义e36模块接口
module_interface_t e36_module = {
        .init = e36_init,
        .deinit = e36_deinit,
        .send_command = e36_send_command,
        .power_on = e36_power_on,
        .power_off = e36_power_off,
        .network_attach_check = e36_network_attach_check,
        .attach_network = e36_attach_network,
        .detach_network = e36_detach_network,
        .open_socket = e36_open_socket,
        .close_socket = e36_close_socket,
        .connect_tcp_server = e36_connect_tcp_server,
        .send_tcp_data = e36_send_tcp_data,
        .get_signal_strength = e36_get_signal_strength,
        .handle_event = e36_handle_event
};

int e36_init(void) {
    platform_uart_init();
    // 使用配置中的初始化命令
    at_command_t at_cmd = {
            .command = e36_config->init_cmd.command,
            .response_prefix = e36_config->init_cmd.response_prefix,
            .timeout_ms = 1000
    };

    char response[64];
    return (module_send_command(&at_cmd, response, sizeof(response)) == AT_SUCCESS) ? 0 : -1;
}

int e36_deinit(void) {
    platform_uart_deinit();
    return 0;
}

at_status_t e36_send_command(const at_command_t *cmd, char *response, size_t response_size) {
    return module_send_command(cmd, response, response_size); // 使用通用命令发送函数
}

// 定义具体的命令函数
at_status_t e36_power_on(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = e36_config->power_on_cmd.command,
            .response_prefix = e36_config->power_on_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return e36_send_command(&at_cmd, response, response_size);
}

at_status_t e36_power_off(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = e36_config->power_off_cmd.command,
            .response_prefix = e36_config->power_off_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return e36_send_command(&at_cmd, response, response_size);
}

at_status_t e36_network_attach_check(void) {
    char response[64];
    at_command_t at_cmd = {
            .command = e36_config->network_attach_check_cmd.command,
            .response_prefix = e36_config->network_attach_check_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return module_send_command(&at_cmd, response, sizeof(response));
}

at_status_t e36_attach_network(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = e36_config->attach_network_cmd.command,
            .response_prefix = e36_config->attach_network_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return e36_send_command(&at_cmd, response, response_size);
}

at_status_t e36_detach_network(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = e36_config->detach_network_cmd.command,
            .response_prefix = e36_config->detach_network_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return e36_send_command(&at_cmd, response, response_size);
}

/**
 * 创建套接字
 * @param type 套接字类型 UDP/TCP
 * @return 套接字ID
 */
int e36_open_socket(ProtocolType type) {
    char response[64];
    char *endptr;
    int value;
    at_command_t at_cmd = {
            .command = e36_config->open_socket_cmd.command,
            .response_prefix = e36_config->open_socket_cmd.response_prefix,
            .timeout_ms = 1000
    };
    // TODO 处理响应代码
    if (e36_send_command(&at_cmd, response, sizeof(response))!=AT_SUCCESS) {
        // TODO 对应的错误处理
        return -1;
    }
    char *ok_ptr = strstr(response, "\nOK");
    if (ok_ptr != NULL) {
        // 在找到 "OK" 之前的部分
        *ok_ptr = '\0';
        // 搜索所创建的套接字ID并返回
        value = strtol(response, &endptr, 10);
        // 检查是否有转换错误
        if (*endptr == '\0' && response != endptr) {
            return value;
        } else {
            printf("Conversion error occurred\n");
            return -1;
        }
    }
    return -1;
}

at_status_t e36_close_socket(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = e36_config->close_socket_cmd.command,
            .response_prefix = e36_config->close_socket_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return e36_send_command(&at_cmd, response, response_size);
}

/**
 * 连接TCP服务器
 * @param socket_id 套接字ID
 * @param ip_addr 服务器IP地址
 * @param port 服务器端口
 * @return 连接状态
 */
at_status_t e36_connect_tcp_server(int socket_id,char *ip_addr, int port) {
    char connect_cmd[64];
    char response[64];
    snprintf(connect_cmd, sizeof(connect_cmd), "AT+SOCO=%d,\"%s\",%d", socket_id, ip_addr, port);
    at_command_t at_cmd = {
            .command = connect_cmd, // 自定义拼凑
            .response_prefix = e36_config->open_socket_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return e36_send_command(&at_cmd, response, sizeof(response));
}

/**
 * 发送数据到TCP服务器
 * @param socket_id 套接字ID
 * @param data 数据内容
 * @param length 数据长度
 * @return 响应状态
 */
at_status_t e36_send_tcp_data(int socket_id, const char *data, int length) {
    char response[64];
    char send_cmd[64];
    unsigned char data_hex[128];
    int result = string_to_hex(data, data_hex, length);
    snprintf(send_cmd, sizeof(send_cmd), "AT+SOSD=%d,%d,\"%s\"", socket_id, result, data_hex);
    at_command_t at_cmd = {
            .command = send_cmd,
            .response_prefix = e36_config->send_tcp_data_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return e36_send_command(&at_cmd, response, sizeof(response));
}

at_status_t e36_get_signal_strength(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = e36_config->get_signal_strength_cmd.command,
            .response_prefix = e36_config->get_signal_strength_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return e36_send_command(&at_cmd, response, response_size);
}

void e36_handle_event(const char *event) {
    printf("需要处理的事件：%s\n", event);
    // 处理事件
}

int hex_char_to_int(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else {
        return -1;
    }
}

int string_to_hex(const char *input, unsigned char *output, size_t output_size) {
    size_t input_length = strlen(input);
    if (input_length % 2 != 0 || output_size < input_length / 2) {
        return -1; // 输入长度必须是偶数，并且输出缓冲区足够大
    }

    for (size_t i = 0; i < input_length; i += 2) {
        int high = hex_char_to_int(input[i]);
        int low = hex_char_to_int(input[i + 1]);

        if (high == -1 || low == -1) {
            return -1; // 非法十六进制字符
        }

        output[i / 2] = (high << 4) | low;
    }

    return input_length / 2; // 返回输出字节数
}
