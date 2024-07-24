//
// Created by dell on 2024-07-22.
//

#include "platform.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h> // for usleep
#include <windows.h>

/*******************************************
 *
 * ʹ��ʱ��Ҫ����Щ�����ڶ�Ӧ��ƽ̨��ʵ�֣������Ե��Զ�ģ��
 *
 *******************************************/

// UART ��ʼ������غ���
int uart_init(const char *portName, int baudRate);
void uart_deinit(void);
int uart_send(const char *data, unsigned int length);
int uart_receive(char *buffer, unsigned int length);

/**
 * @brief       ��ʼ��UART
 */
void platform_uart_init(void) {
    // ��ʼ��UART�������Ͽ���Ϊ��
    printf("UART initialized...\n");
    if (uart_init("COM9", CBR_9600) == -1) {
        printf("Error in opening serial port\n");
        return;
    }
    printf("UART initialization successful!\n");
}

/**
 * @brief       ����ʼ��UART
 */
void platform_uart_deinit(void) {
    // ����ʼ��UART�������Ͽ���Ϊ��
    printf("UART deinitialized\n");
    uart_deinit();
}

void platform_uart_send(const char *data, unsigned int length) {
    // �������ݣ�������ģ�����
    uart_send(data, strlen(data));
    // ģ�ⷢ�����ݣ�ͨ����ӡ���������̨
}

int platform_uart_receive(char *buffer, unsigned int length) {
    // �Ӵ��ڽ�������
    int bytesRead = uart_receive(buffer, length);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';  // �����ַ���
    } else {
        printf("Failed to receive data.\n");
    }
    return bytesRead;
}

void platform_delay_ms(unsigned int ms) {
    // ������ʹ��usleepʵ����ʱ
    usleep(ms * 1000);
}

void platform_enable_interrupts(void) {
    // ������ģ��
    printf("Interrupts enabled\n");
}

void platform_disable_interrupts(void) {
    // ������ģ��
    printf("Interrupts disabled\n");
}


// ʾ�� UART ʵ��
static HANDLE hSerial;
static DCB dcbSerialParams = { 0 };
static COMMTIMEOUTS timeouts = { 0 };

int uart_init(const char *portName, int baudRate) {
    hSerial = CreateFile(
            portName,
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error in opening serial port\n");
        return -1;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error getting state\n");
        return -1;
    }

    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error setting state\n");
        return -1;
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error setting timeouts\n");
        return -1;
    }

    return 0;
}

void uart_deinit() {
    CloseHandle(hSerial);
}

int uart_send(const char *data, unsigned int length) {
    DWORD bytesWritten;
    if (!WriteFile(hSerial, data, length, &bytesWritten, NULL)) {
        printf("Error writing to serial port\n");
        return -1;
    }
    return bytesWritten;
}

int uart_receive(char *buffer, unsigned int length) {
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, length, &bytesRead, NULL)) {
        printf("Error reading from serial port\n");
        return -1;
    }
    return bytesRead;
}
