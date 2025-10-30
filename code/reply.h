#ifndef REPLY_H
#define REPLY_H

typedef struct Reply {
    char username[25];
    char content[256];
    struct Reply *next;
} Reply;

Reply *createReply(char *username, char *content);

void freeReplies(Reply *reply);
#endif
