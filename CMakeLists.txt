cmake_minimum_required(VERSION 3.10)
project(ATCommandFramework C)

set(CMAKE_C_STANDARD 99)

include_directories(include)
include_directories(modules/e36)

add_executable(main main.c src/at_command.c src/module_interface.c
        module/e36/e36_module.c
        src/at_command_config.c
        src/platform.c
        src/example.c
        src/queue.c
        module/ec800m/ec800m_module.c
        src/string_utils.c
)
