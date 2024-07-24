//
// Created by dell on 2024-07-22.
//

#include "../include/at_command.h"
#include <stdio.h>

void at_handle_error(at_status_t status) {
    switch (status) {
        case AT_SUCCESS:
            break;
        case AT_TIMEOUT:
            printf("AT command timeout\n");
            break;
        case AT_ERROR:
            printf("AT command error\n");
            break;
        case AT_INVALID_RESPONSE:
            printf("Invalid AT command response\n");
            break;
    }
}
