//
// Created by icebi on 2024/7/24.
//

#ifndef ATCOMMANDFRAMEWORK_STRING_UTILS_H
#define ATCOMMANDFRAMEWORK_STRING_UTILS_H

#include <stddef.h>

int string_to_hex(const char *input, unsigned char *output, size_t output_size);
int hex_char_to_int(char c);



#endif //ATCOMMANDFRAMEWORK_STRING_UTILS_H
