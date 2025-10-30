#ifndef PLATFORM_H
#define PLATFORM_H

#include "post.h"
#include <stdbool.h>
#include "comment.h"

typedef struct Platform {
    Post *posts;
    Post *lastViewedPost;
} Platform;

Platform* createPlatform();
bool addPost(char *username, char *caption);
bool deletePost(int n);
Post* viewPost(int n);
Post* currPost();
Post* nextPost();
Post* previousPost();

bool addComment(char *username, char *content);
bool deleteComment(int n);
Comment* viewComments();

extern Platform *platform;

bool addReplyToComment(int commentIndex, char *username, char *content);
bool deleteReplyFromComment(int commentIndex, int replyIndex);
Comment *viewRepliesOfComment(int commentIndex);

#endif