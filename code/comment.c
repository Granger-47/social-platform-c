#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "comment.h"

Comment *createComment(char *username, char *content) {
    Comment *newComment = malloc(sizeof(Comment));
    if (!newComment) return NULL;

    int i;
    for (i = 0; i < 24 && username[i] != '\0'; i++)
        newComment->username[i] = username[i];
    newComment->username[i] = '\0';

    for (i = 0; i < 255 && content[i] != '\0'; i++)
        newComment->content[i] = content[i];
    newComment->content[i] = '\0';

    newComment->next = NULL;
    newComment->replies = NULL;
    return newComment;
}

bool addReply(Comment *comment, char *username, char *content) {
    if (!comment) return false;
    Comment *newReply = createComment(username, content);
    if (!newReply) return false;

    newReply->next = comment->replies;
    comment->replies = newReply;
    return true;
}

bool deleteReply(Comment *comment, int n) {
    if (!comment || !comment->replies) return false;

    Comment *curr = comment->replies;
    if (n == 1) {
        comment->replies = curr->next;
        free(curr);
        return true;
    }

    for (int i = 1; curr && i < n - 1; i++)
        curr = curr->next;

    if (!curr || !curr->next) return false;

    Comment *temp = curr->next;
    curr->next = temp->next;
    free(temp);
    return true;
}

Comment *viewReplies(Comment *comment) {
    if (!comment || !comment->replies) {
        printf("No replies.\n");
        return NULL;
    }

    Comment *reversed = NULL;
    Comment *curr = comment->replies;
    while (curr) {
        Comment *newNode = createComment(curr->username, curr->content);
        newNode->next = reversed;
        reversed = newNode;
        curr = curr->next;
    }
    return reversed;
}
