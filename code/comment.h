#ifndef COMMENT_H
#define COMMENT_H


#include <stdbool.h>
#include "reply.h"
struct Post; 

typedef struct Comment {
    char username[25];
    char content[256];
    struct Comment *next; 
    struct Comment *replies;   
} Comment;

Comment *createComment(char *username, char *content);

bool addReply(Comment *comment, char *username, char *content);
bool deleteReply(Comment *comment, int n);
Comment *viewReplies(Comment *comment);

#endif
