//
// Created by dell on 2024-07-22.
//

#ifndef ec800m_MODULE_H
#define ec800m_MODULE_H

#include "module_interface.h"

extern module_interface_t ec800m_module;

int ec800m_init(void);
int ec800m_deinit(void);
at_status_t ec800m_power_on(char *response, size_t response_size);
at_status_t ec800m_power_off(char *response, size_t response_size);
at_status_t ec800m_network_attach_check(void);
at_status_t ec800m_attach_network(char *response, size_t response_size);
at_status_t ec800m_detach_network(char *response, size_t response_size);
int ec800m_open_socket(ProtocolType type);
at_status_t ec800m_close_socket(char *response, size_t response_size);
at_status_t ec800m_send_tcp_data(int socket_id, const char *data, int length);
at_status_t ec800m_get_signal_strength(char *response, size_t response_size);
/* 连接到TCP服务器 */
at_status_t ec800m_connect_tcp_server(int socket_id,char *ip_addr, int port);
at_status_t ec800m_send_command(const at_command_t *cmd, char *response, size_t response_size);
void ec800m_handle_event(const char *event);
int string_to_hex(const char *input, unsigned char *output, size_t output_size);

#endif // ec800m_MODULE_H
