#include <unistd.h>
#include <stdlib.h>
#include "module/e36/e36_module.h"
#include "queue.h"

void processItem(char *item) {
    printf("Processing item: %s\n", item);
    // 发送数据到TCP服务器

    // 等待服务器响应

        // 响应错误
            // 1、信号不好 -> 存储信息，关闭网络
            // 2、网络断开 -> 检查原因 -> 重连服务器
            // 3、服务器断开 -> 重连服务器
            // 4、服务器响应超时 -> 重连服务器
            // 5、模块未响应 ->重启重新连接
}

int socket_id;

int main() {

    // 指定模块
    module_interface_t *module = &e36_module;
    // TODO 启动模块
    // 初始化模块
    if (module->init()!=0) {
        printf("模块初始化失败\n");
    }
    char buffer_s[128];
    // 检测模块是否可以上网
    if (module->network_attach_check()==AT_SUCCESS) {
        printf("PDP附着成功!\n");
        // 创建套接字
        socket_id = e36_open_socket(TCP);
        if (socket_id < 0) {
            printf("创建套接字失败\n");
        }
        // 连接服务器
        printf("连接服务器...\n");
        if (module->connect_tcp_server(socket_id, "47.104.72.22", 10086) == AT_SUCCESS) {
            printf("连接服务器成功\n");
        } else {
            printf("连接服务器失败\n");
        }
    } else {
        printf("模块无法上网\n");
    }

    Queue q;
    initQueue(&q);
    char input[100];

    while (1) {
        printf("Enter data: ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // 去掉换行符
            enqueue(&q, input);
        }

        while (!isEmpty(&q)) {
            char *item = dequeue(&q);
            if (item) {
                processItem(item);
                module->send_tcp_data(socket_id, item, strlen(item));
                free(item); // 释放分配的内存
            }
        }
    sleep(1); // 延时1秒
    }
    return 0;
}


