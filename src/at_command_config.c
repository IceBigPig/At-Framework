//
// Created by dell on 2024-07-22.
//

#include "at_command_config.h"

/**
 * E36ģ��ATָ������
 * Ŀǰ�Ŀ���в��ܹ�������Ӧָ��Ĳ�����������ʱ������������
 */
const at_command_config_t e36_command_config = {
        .init_cmd = {"AT", "OK"},
        .module_info_cmd = {"AT+CGMR", ""},
        .network_attach_check_cmd = {"AT+CGATT?", "+CGATT: 1"},
        .attach_network_cmd = {"AT+CGATT=1", "+CGATT: 1"},
        .detach_network_cmd = {"AT+CGATT=0", "OK"},
        .get_signal_strength_cmd = {"AT+CSQ", "+CSQ:"},
        .power_on_cmd = {"AT+CFUN=1", "OK"},
        .power_off_cmd = {"AT+CFUN=0", "OK"},
        .open_socket_cmd = {"AT+SOCR=\"STREAM\",6", "OK"}, // �����������TCP��UDP��δ����
        .close_socket_cmd = {"AT+NETCLOSE", "OK"},
        .connect_tcp_server_cmd = {"", "OK\n+SOCO: 1"},     // �����Զ����������ַ����ģ��ĺ�����ʵ��
        .send_tcp_data_cmd = {"AT+SEND=", "SEND OK"},
        .receive_tcp_data_cmd = {"AT+RECEIVE", "+RECEIVE"}
};
