#include <stdlib.h>
#include <stdio.h>
#include "reply.h"

Reply *createReply(char *username, char *content) {
    Reply *newReply = (Reply *)malloc(sizeof(Reply));
    if (!newReply) {
        printf("Memory allocation failed for reply\n");
        return NULL;
    }

    int i;
    int maxUser = sizeof(newReply->username);
    int maxCont = sizeof(newReply->content);

    for (i = 0; i < maxUser - 1 && username[i] != '\0'; i++)
        newReply->username[i] = username[i];
    newReply->username[i] = '\0';

    for (i = 0; i < maxCont - 1 && content[i] != '\0'; i++)
        newReply->content[i] = content[i];
    newReply->content[i] = '\0';

    newReply->next = NULL;
    return newReply;
}

void freeReplies(Reply *reply) {
    while (reply) {
        Reply *temp = reply->next;
        free(reply);
        reply = temp;
    }
}
