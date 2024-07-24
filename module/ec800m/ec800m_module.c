//
// Created by dell on 2024-07-22.
//

#include <stdlib.h>
#include "module_interface.h"
#include "at_command_config.h"
#include "ec800m_module.h"
#include "platform.h"


static const at_command_config_t *ec800m_config = &ec800m_command_config;

// ����ec800mģ��ӿ�
module_interface_t ec800m_module = {
        .init = ec800m_init,
        .deinit = ec800m_deinit,
        .send_command = ec800m_send_command,
        .power_on = ec800m_power_on,
        .power_off = ec800m_power_off,
        .network_attach_check = ec800m_network_attach_check,
        .attach_network = ec800m_attach_network,
        .detach_network = ec800m_detach_network,
        .open_socket = ec800m_open_socket,
        .close_socket = ec800m_close_socket,
        .connect_tcp_server = ec800m_connect_tcp_server,
        .send_tcp_data = ec800m_send_tcp_data,
        .get_signal_strength = ec800m_get_signal_strength,
        .handle_event = ec800m_handle_event
};

int ec800m_init(void) {
    platform_uart_init();
    // ʹ�������еĳ�ʼ������
    at_command_t at_cmd = {
            .command = ec800m_config->init_cmd.command,
            .response_prefix = ec800m_config->init_cmd.response_prefix,
            .timeout_ms = 1000
    };

    char response[64];
    return (module_send_command(&at_cmd, response, sizeof(response)) == AT_SUCCESS) ? 0 : -1;
}

int ec800m_deinit(void) {
    platform_uart_deinit();
    return 0;
}

at_status_t ec800m_send_command(const at_command_t *cmd, char *response, size_t response_size) {
    return module_send_command(cmd, response, response_size); // ʹ��ͨ������ͺ���
}

// �������������
at_status_t ec800m_power_on(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = ec800m_config->power_on_cmd.command,
            .response_prefix = ec800m_config->power_on_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return ec800m_send_command(&at_cmd, response, response_size);
}

at_status_t ec800m_power_off(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = ec800m_config->power_off_cmd.command,
            .response_prefix = ec800m_config->power_off_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return ec800m_send_command(&at_cmd, response, response_size);
}

at_status_t ec800m_network_attach_check(void) {
    char response[64];
    at_command_t at_cmd = {
            .command = ec800m_config->network_attach_check_cmd.command,
            .response_prefix = ec800m_config->network_attach_check_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return module_send_command(&at_cmd, response, sizeof(response));
}

at_status_t ec800m_attach_network(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = ec800m_config->attach_network_cmd.command,
            .response_prefix = ec800m_config->attach_network_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return ec800m_send_command(&at_cmd, response, response_size);
}

at_status_t ec800m_detach_network(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = ec800m_config->detach_network_cmd.command,
            .response_prefix = ec800m_config->detach_network_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return ec800m_send_command(&at_cmd, response, response_size);
}

/**
 * �����׽���
 * @param type �׽������� UDP/TCP
 * @return �׽���ID
 */
int ec800m_open_socket(ProtocolType type) {
    char response[64];
    char *endptr;
    int value;
    at_command_t at_cmd = {
            .command = ec800m_config->open_socket_cmd.command,
            .response_prefix = ec800m_config->open_socket_cmd.response_prefix,
            .timeout_ms = 1000
    };
    // TODO ������Ӧ����
    if (ec800m_send_command(&at_cmd, response, sizeof(response))!=AT_SUCCESS) {
        // TODO ��Ӧ�Ĵ�����
        return -1;
    }
    char *ok_ptr = strstr(response, "\nOK");
    if (ok_ptr != NULL) {
        // ���ҵ� "OK" ֮ǰ�Ĳ���
        *ok_ptr = '\0';
        // �������������׽���ID������
        value = strtol(response, &endptr, 10);
        // ����Ƿ���ת������
        if (*endptr == '\0' && response != endptr) {
            return value;
        } else {
            printf("Conversion error occurred\n");
            return -1;
        }
    }
    return -1;
}

at_status_t ec800m_close_socket(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = ec800m_config->close_socket_cmd.command,
            .response_prefix = ec800m_config->close_socket_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return ec800m_send_command(&at_cmd, response, response_size);
}

/**
 * ����TCP������
 * @param socket_id �׽���ID
 * @param ip_addr ������IP��ַ
 * @param port �������˿�
 * @return ����״̬
 */
at_status_t ec800m_connect_tcp_server(int socket_id,char *ip_addr, int port) {
    char connect_cmd[64];
    char response[64];
    snprintf(connect_cmd, sizeof(connect_cmd), "AT+SOCO=%d,\"%s\",%d", socket_id, ip_addr, port);
    at_command_t at_cmd = {
            .command = connect_cmd, // �Զ���ƴ��
            .response_prefix = ec800m_config->open_socket_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return ec800m_send_command(&at_cmd, response, sizeof(response));
}

/**
 * �������ݵ�TCP������
 * @param socket_id �׽���ID
 * @param data ��������
 * @param length ���ݳ���
 * @return ��Ӧ״̬
 */
at_status_t ec800m_send_tcp_data(int socket_id, const char *data, int length) {
    char response[64];
    char send_cmd[64];
    unsigned char data_hex[128];
    int result = string_to_hex(data, data_hex, length);
    snprintf(send_cmd, sizeof(send_cmd), "AT+SOSD=%d,%d,\"%s\"", socket_id, result, data_hex);
    at_command_t at_cmd = {
            .command = send_cmd,
            .response_prefix = ec800m_config->send_tcp_data_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return ec800m_send_command(&at_cmd, response, sizeof(response));
}

at_status_t ec800m_get_signal_strength(char *response, size_t response_size) {
    at_command_t at_cmd = {
            .command = ec800m_config->get_signal_strength_cmd.command,
            .response_prefix = ec800m_config->get_signal_strength_cmd.response_prefix,
            .timeout_ms = 1000
    };
    return ec800m_send_command(&at_cmd, response, response_size);
}

void ec800m_handle_event(const char *event) {
    printf("��Ҫ������¼���%s\n", event);
    // �����¼�
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
        return -1; // ���볤�ȱ�����ż������������������㹻��
    }

    for (size_t i = 0; i < input_length; i += 2) {
        int high = hex_char_to_int(input[i]);
        int low = hex_char_to_int(input[i + 1]);

        if (high == -1 || low == -1) {
            return -1; // �Ƿ�ʮ�������ַ�
        }

        output[i / 2] = (high << 4) | low;
    }

    return input_length / 2; // ��������ֽ���
}
