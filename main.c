#include <unistd.h>
#include <stdlib.h>
#include "module/e36/e36_module.h"
#include "queue.h"

void processItem(char *item) {
    printf("Processing item: %s\n", item);
    // �������ݵ�TCP������

    // �ȴ���������Ӧ

        // ��Ӧ����
            // 1���źŲ��� -> �洢��Ϣ���ر�����
            // 2������Ͽ� -> ���ԭ�� -> ����������
            // 3���������Ͽ� -> ����������
            // 4����������Ӧ��ʱ -> ����������
            // 5��ģ��δ��Ӧ ->������������
}

int socket_id;

int main() {

    // ָ��ģ��
    module_interface_t *module = &e36_module;
    // TODO ����ģ��
    // ��ʼ��ģ��
    if (module->init()!=0) {
        printf("ģ���ʼ��ʧ��\n");
    }
    char buffer_s[128];
    // ���ģ���Ƿ��������
    if (module->network_attach_check()==AT_SUCCESS) {
        printf("PDP���ųɹ�!\n");
        // �����׽���
        socket_id = e36_open_socket(TCP);
        if (socket_id < 0) {
            printf("�����׽���ʧ��\n");
        }
        // ���ӷ�����
        printf("���ӷ�����...\n");
        if (module->connect_tcp_server(socket_id, "47.104.72.22", 10086) == AT_SUCCESS) {
            printf("���ӷ������ɹ�\n");
        } else {
            printf("���ӷ�����ʧ��\n");
        }
    } else {
        printf("ģ���޷�����\n");
    }

    Queue q;
    initQueue(&q);
    char input[100];

    while (1) {
        printf("Enter data: ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            input[strcspn(input, "\n")] = 0; // ȥ�����з�
            enqueue(&q, input);
        }

        while (!isEmpty(&q)) {
            char *item = dequeue(&q);
            if (item) {
                processItem(item);
                module->send_tcp_data(socket_id, item, strlen(item));
                free(item); // �ͷŷ�����ڴ�
            }
        }
    sleep(1); // ��ʱ1��
    }
    return 0;
}


