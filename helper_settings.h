#pragma once

#define DATA_FILE_PATH ":/json/file.json"

#define GROUPS_NUMBER 7
#define USERS_PER_GROUP 13

#define STARTING_GROUP_COUNTER 1
#define STARTING_USER_COUNTER 1

#define CONSOLE_PRINT_CHAR_DELAY 7

enum ConsoleTextType {
    ERROR = 'e',
    WARNING = 'w',
    ACTION = 'a',
    DEFAULT = 'd',
    BLUETOOTH = 'b'
};
