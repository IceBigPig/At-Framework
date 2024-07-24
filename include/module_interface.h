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
 * ģ��ӿ�
 * ���½ӿ�Ϊģ���ṩ�Ĺ���
 */
typedef struct {
    /* ��ʼ���ӿ� */
    int (*init)(void);
    /* ����ʼ�� */
    int (*deinit)(void);
    /* �������� */
    at_status_t (*send_command)(const at_command_t *cmd, char *response, size_t response_size);
    /* ģ�鿪�� */
    at_status_t (*power_on)(char *response, size_t response_size);
    /* ģ��ػ� */
    at_status_t (*power_off)(char *response, size_t response_size);
    /* ���總�ż�� */
    at_status_t (*network_attach_check)(void);
    /* ���總�� */
    at_status_t (*attach_network)(char *response, size_t response_size);
    /* ����ȥ���� */
    at_status_t (*detach_network)(char *response, size_t response_size);
    /* �����׽��� */
    int (*open_socket)(ProtocolType type);
    /* �ر��׽��� */
    at_status_t (*close_socket)(char *response, size_t response_size);
    /* ����TCP������ */
    at_status_t (*connect_tcp_server)(int socket_id,char *ip_addr, int port);
    /* �������ݵ�TCP������ */
    at_status_t (*send_tcp_data)(int socket_id, const char *data, int length);
    /* ��ȡģ���ź�ǿ�� */
    at_status_t (*get_signal_strength)(char *response, size_t response_size);
    /* �¼�����ص� */
    void (*handle_event)(const char *event);
} module_interface_t;

at_status_t module_send_command(const at_command_t *cmd, char *response, size_t response_size);
#endif // MODULE_INTERFACE_H
