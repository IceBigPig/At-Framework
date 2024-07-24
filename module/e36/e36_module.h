//
// Created by dell on 2024-07-22.
//

#ifndef E36_MODULE_H
#define E36_MODULE_H

#include "module_interface.h"

extern module_interface_t e36_module;

int e36_init(void);
int e36_deinit(void);
at_status_t e36_power_on(char *response, size_t response_size);
at_status_t e36_power_off(char *response, size_t response_size);
at_status_t e36_network_attach_check(void);
at_status_t e36_attach_network(char *response, size_t response_size);
at_status_t e36_detach_network(char *response, size_t response_size);
int e36_open_socket(ProtocolType type);
at_status_t e36_close_socket(char *response, size_t response_size);
at_status_t e36_send_tcp_data(int socket_id, const char *data, int length);
at_status_t e36_get_signal_strength(char *response, size_t response_size);
/* 连接到TCP服务器 */
at_status_t e36_connect_tcp_server(int socket_id,char *ip_addr, int port);
at_status_t e36_send_command(const at_command_t *cmd, char *response, size_t response_size);
void e36_handle_event(const char *event);
int string_to_hex(const char *input, unsigned char *output, size_t output_size);

#endif // E36_MODULE_H
