//
// Created by dell on 2024-07-22.
//

#ifndef AT_COMMAND_H
#define AT_COMMAND_H

typedef enum {
    AT_SUCCESS,
    AT_TIMEOUT,
    AT_ERROR,
    AT_INVALID_RESPONSE
} at_status_t;

typedef struct {
    const char *command;
    const char *response_prefix;
    unsigned int timeout_ms;
} at_command_t;

void at_handle_error(at_status_t status);

#endif // AT_COMMAND_H
