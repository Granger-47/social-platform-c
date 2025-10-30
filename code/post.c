#include <stdlib.h>
#include "post.h"

Post* createPost(char *username, char *caption) {
    Post *newPost = (Post *)malloc(sizeof(Post));
    int i;
    int maxUsernameLength = sizeof(newPost->username);
    int maxCaptionLength = sizeof(newPost->caption);

    for(i=0; i<maxUsernameLength-1 && username[i]!='\0'; i+=1){
        newPost->username[i] = username[i];
    }
    newPost->username[maxUsernameLength-1] = '\0'; 
    for (i = 0; i < maxCaptionLength - 1 && caption[i] != '\0'; i++) {
        newPost->caption[i] = caption[i];
    }
    newPost->caption[i] = '\0';
    newPost->comments = NULL;
    newPost->next = NULL;
    return newPost;
}

void freeComments(Post *post){
    if(!post) return;
    if(!post->comments) return;
    while(post->comments){
        Comment* temp = post->comments->next;
        free(post->comments);
        post->comments = temp;
    }
}