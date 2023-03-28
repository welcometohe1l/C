#include "message.h"
#include "macros.h"
#include <string.h>

// Public
Message *create_message(void) {
    char text[MSG_MAX_LEN] = {0};

    fputs("Type your message here: ", stdout);
    
    if (fseek(stdin, 0, SEEK_SET)) {
        error_message("fseek() error");
        return NULL;
    }
    if (fgets(text, MSG_MAX_LEN, stdin) == NULL) {
        error_message("fgets() error");
        return NULL;
    }

    time_t msg_time;
    size_t text_len = strlen(text) + 1;
    size_t msg_size = sizeof(Message) + text_len * sizeof(char);

    if ((msg_time = time(NULL)) == (time_t)(-1)) {
        error_message("create_message() error: time() error");
        return NULL;
    } 

    Message *msg = (Message *)malloc(msg_size);

    if (msg == NULL) {
        error_message("create_message() error: malloc() error");
        return NULL;
    }

    memcpy(msg->text, text, text_len);
    msg->time = msg_time;
    msg->size = msg_size;
    msg->text_len = text_len;

    return msg;
}
