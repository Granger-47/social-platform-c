#include <stdio.h>
#include <stdlib.h>
#include "platform.h"

Platform *platform;

Platform* createPlatform(){
    platform = (Platform *)malloc(sizeof(Platform));
    if (!platform) {
        printf("Memory allocation failed for platform\n");
        exit(1);
    }
    platform->posts = NULL;
    platform->lastViewedPost = NULL;
    return platform;
}

bool addPost(char *username, char *caption){
    Post *newPost = createPost(username,caption);
    if(!newPost){
        printf("Post creation failed \n");
        return false;
    }
    newPost->next = platform->posts; //insert element to beginning of linked list (linked list of posts)
    platform->lastViewedPost = newPost;
    platform->posts = newPost;
    return true;
}

bool deletePost(int n){
    Post* curr = platform->posts;
    if(!curr) return false;
    if(n==1){ 
        platform->posts = platform->posts->next;  //deleting the first post (most recent post)
        freeComments(curr);
        free(curr);
        return true;
    }
    for(int i=1;curr!=NULL && i<n-1; i+=1){
        curr = curr->next; //traverses until curr is n-1th post
    }
    if (!curr || !curr->next) return false; // nth post doesn't exist
    Post *temp = curr->next->next;
    freeComments(curr->next);
    free(curr->next);
    curr->next = temp;
    return true;
}


Post* viewPost(int n){
    Post *temp = platform->posts;
    for(int i=1; temp && i<n; i+=1){
        temp = temp->next;   //traverses to nth post
    }
    if(!temp){
        printf("Post doesn't exist \n");
        return NULL;
    }
    platform->lastViewedPost = temp;
    printf("%s says: %s\n",temp->username, temp->caption);
    return temp;
}


Post* currPost(){
    if(!platform->lastViewedPost){
        if(!platform->posts){
            printf("There are no posts yet. \n");
            return NULL; //if there are no posts
        }
        else{
            platform->lastViewedPost = platform->posts;//if no posts are visited, lastViewedPost is set to recent post
        }
    }
    return platform->lastViewedPost;
}


Post* nextPost(){
    if(!platform->posts){
        printf("There are no posts yet. \n");
        return NULL; //if there are no posts
    }
    if (!platform->lastViewedPost) {
        platform->lastViewedPost = platform->posts; // default to most recent
    }
    if(platform->lastViewedPost->next == NULL) return platform->lastViewedPost; //lastViewedPost is the oldest post

    Post* temp = platform->lastViewedPost->next; //next element in linked list will be the post added right before curr
    printf("%s says: %s\n",temp->username, temp->caption);
    platform->lastViewedPost = temp;
    return temp;
}

Post* previousPost(){
    if(!platform->posts) return NULL;
    if(!platform->lastViewedPost){
        platform->lastViewedPost = platform->posts;
        return platform->lastViewedPost;
    }
    Post* curr = platform->posts;
    Post* prev = NULL;
    while(curr && curr!=platform->lastViewedPost){
        prev = curr;
        curr = curr->next;
    }
    if (!prev) {
        printf("Next post does not exist.\n"); //highly unlikely
        return NULL;
    }
    platform->lastViewedPost = prev;
    printf("%s says: %s\n",prev->username, prev->caption);
    return prev;
}

bool addComment(char *username, char *content){
    if(!platform->lastViewedPost){
        return false;
    }
    Comment *newCmt = createComment(username,content);
    if(platform->lastViewedPost->comments == NULL){
        platform->lastViewedPost->comments = newCmt;
    } else {
        newCmt->next = platform->lastViewedPost->comments;
        platform->lastViewedPost->comments = newCmt;
    }
    return true;
}

bool deleteComment(int n){
    if(!platform->lastViewedPost){
        return false;
    }
    Post *recent = platform->lastViewedPost;
    Comment* curr = recent->comments;
    if(n==1){ 
        recent->comments = recent->comments->next;  //deleting the first comment (most recent comment)
        free(curr);
        return true;
    }
    for(int i=1;curr!=NULL && i<n-1; i+=1){
        curr = curr->next; //traverses until curr is n-1th comment
    }
    if (!curr || !curr->next) return false; // nth comment doesn't exist
    Comment *temp = curr->next->next;
    free(curr->next);
    curr->next = temp;
    return true;
}

Comment* viewComments(){
    if(!platform->lastViewedPost){
        printf("Post not found. \n");
        return NULL;
    }
    Comment* comments = platform->lastViewedPost->comments;
    if(!comments){
        printf("Post has no comments. \n");
        return NULL;
    }
    Comment* reversed = NULL;
    Comment* curr = comments;
    while(curr){
        Comment* newNode = (Comment*)malloc(sizeof(Comment));
        if(!newNode){
            printf("Memory allocation failed\n");
            return NULL;
        }

        int i;
        int maxUsernameLength = sizeof(newNode->username);
        int maxContentLength = sizeof(newNode->content);
        for (i = 0; i < maxUsernameLength - 1 && curr->username[i] != '\0'; i++)
            newNode->username[i] = curr->username[i];
        newNode->username[i] = '\0';

        for (i = 0; i < maxContentLength - 1 && curr->content[i] != '\0'; i++)
            newNode->content[i] = curr->content[i];
        newNode->content[i] = '\0';

        newNode->next = reversed;
        reversed = newNode;

        curr = curr->next;
    }
    return reversed;
}


bool addReplyToComment(int commentIndex, char *username, char *content) {
    if (!platform->lastViewedPost) return false;

    Comment *curr = platform->lastViewedPost->comments;
    for (int i = 1; curr && i < commentIndex; i++)
        curr = curr->next;

    if (!curr) return false;

    return addReply(curr, username, content);
}

bool deleteReplyFromComment(int commentIndex, int replyIndex) {
    if (!platform->lastViewedPost) return false;

    Comment *curr = platform->lastViewedPost->comments;
    for (int i = 1; curr && i < commentIndex; i++)
        curr = curr->next;

    if (!curr) return false;

    return deleteReply(curr, replyIndex);
}

Comment *viewRepliesOfComment(int commentIndex) {
    if (!platform->lastViewedPost) return NULL;

    Comment *curr = platform->lastViewedPost->comments;
    for (int i = 1; curr && i < commentIndex; i++)
        curr = curr->next;

    if (!curr) {
        printf("Comment not found.\n");
        return NULL;
    }

    return viewReplies(curr);
}