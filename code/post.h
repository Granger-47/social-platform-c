#ifndef POST_H
#define POST_H

#include "comment.h"


typedef struct Post{
    char username[25];
    char caption[256];
    Comment *comments;
    struct Post *next;
} Post;

Post *createPost(char *username, char *caption);
void freeComments(Post *post);

#endif