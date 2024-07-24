//
// Created by dell on 2024-07-22.
//

#include <unistd.h>
#include "module_interface.h"
#include "platform.h"

/**
 * @brief 发送AT命令并等待响应
 */
at_status_t module_send_command(const at_command_t *cmd, char *response, size_t response_size) {
    // 清空响应缓冲区
    memset(response, 0, response_size);
    // 发送AT命令
    platform_uart_send(cmd->command, strlen(cmd->command));
    platform_uart_send("\r\n", 2);
    printf("command:-> %s\n", cmd->command);
    // 等待响应
    unsigned int elapsed_time = 0;
    while (elapsed_time < cmd->timeout_ms) {
        int bytesRead = platform_uart_receive(response, response_size - 1);
        if (bytesRead > 0) {
            printf("response: <- %s\n", response);
            response[bytesRead] = '\0'; // 确保响应以空字符结尾

            if (strstr(response, cmd->response_prefix) != NULL) {
                return AT_SUCCESS;
            } else {
                return AT_INVALID_RESPONSE;
            }
        }
        platform_delay_ms(10);
        elapsed_time += 10;
    }
    sleep(1); // 延时1秒
    return AT_TIMEOUT;
}
