#ifndef MESSAGE_H
#define MESSAGE_H

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MSG_MAX_LEN 1000

// Data
typedef struct {
    size_t size;
    time_t time;
    size_t text_len;
    char text[];
} Message;

// Functions

// You have to call free() on message obj
Message *create_message(void); 

#endif // MESSAGE_H
