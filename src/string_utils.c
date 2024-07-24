//
// Created by icebi on 2024/7/24.
//
#include "string_utils.h"
#include "string.h"
#include <ctype.h>

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
