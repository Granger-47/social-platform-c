#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h"

void printMenu() {
    printf("\n========== SOCIAL PLATFORM ==========\n");
    printf("1. Add Post\n");
    printf("2. View Post by Number\n");
    printf("3. Delete Post\n");
    printf("4. View Current Post\n");
    printf("5. Next Post\n");
    printf("6. Previous Post\n");
    printf("7. Add Comment to Current Post\n");
    printf("8. View Comments of Current Post\n");
    printf("9. Delete Comment\n");
    printf("10. Add Reply to a Comment\n");
    printf("11. View Replies of a Comment\n");
    printf("12. Delete Reply from a Comment\n");
    printf("0. Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}

int main() {
    Platform *p = createPlatform();
    int choice;
    char username[25], caption[256], content[256];
    int postNum, commentNum, replyNum;

    while (1) {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("\nEnter username: ");
                scanf(" %[^\n]", username);
                printf("Enter caption: ");
                scanf(" %[^\n]", caption);
                if (addPost(username, caption))
                    printf("Post added successfully!\n");
                else
                    printf("Failed to add post.\n");
                break;

            case 2:
                printf("\nEnter post number to view: ");
                scanf("%d", &postNum);
                viewPost(postNum);
                break;

            case 3:
                printf("\nEnter post number to delete: ");
                scanf("%d", &postNum);
                if (deletePost(postNum))
                    printf("Post deleted successfully!\n");
                else
                    printf("Post not found.\n");
                break;

            case 4:
                printf("\n--- Current Post ---\n");
                if (currPost())
                    printf("%s says: %s\n", platform->lastViewedPost->username,
                           platform->lastViewedPost->caption);
                break;

            case 5:
                printf("\n--- Next Post ---\n");
                nextPost();
                break;

            case 6:
                printf("\n--- Previous Post ---\n");
                previousPost();
                break;

            case 7:
                printf("\nEnter username: ");
                scanf(" %[^\n]", username);
                printf("Enter comment: ");
                scanf(" %[^\n]", content);
                if (addComment(username, content))
                    printf("Comment added successfully!\n");
                else
                    printf("Failed to add comment.\n");
                break;

            case 8: {
                printf("\n--- Viewing Comments ---\n");
                Comment *comments = viewComments();
                if (comments) {
                    int i = 1;
                    for (Comment *temp = comments; temp; temp = temp->next, i++)
                        printf("%d. %s: %s\n", i, temp->username, temp->content);

                    // free the reversed temporary list
                    Comment *c = comments;
                    while (c) {
                        Comment *next = c->next;
                        free(c);
                        c = next;
                    }
                }
                break;
            }

            case 9:
                printf("\nEnter comment number to delete: ");
                scanf("%d", &commentNum);
                if (deleteComment(commentNum))
                    printf("Comment deleted successfully!\n");
                else
                    printf("Comment not found.\n");
                break;

            case 10:
                printf("\nEnter comment number to reply to: ");
                scanf("%d", &commentNum);
                printf("Enter username: ");
                scanf(" %[^\n]", username);
                printf("Enter reply: ");
                scanf(" %[^\n]", content);
                if (addReplyToComment(commentNum, username, content))
                    printf("Reply added successfully!\n");
                else
                    printf("Failed to add reply.\n");
                break;

            case 11: {
                printf("\nEnter comment number to view replies: ");
                scanf("%d", &commentNum);
                Comment *replies = viewRepliesOfComment(commentNum);
                if (replies) {
                    int i = 1;
                    for (Comment *r = replies; r; r = r->next, i++)
                        printf("↳ %d. %s: %s\n", i, r->username, r->content);

                    // free reversed list
                    Comment *c = replies;
                    while (c) {
                        Comment *next = c->next;
                        free(c);
                        c = next;
                    }
                }
                break;
            }

            case 12:
                printf("\nEnter comment number: ");
                scanf("%d", &commentNum);
                printf("Enter reply number to delete: ");
                scanf("%d", &replyNum);
                if (deleteReplyFromComment(commentNum, replyNum))
                    printf("Reply deleted successfully!\n");
                else
                    printf("Reply not found.\n");
                break;

            case 0:
                printf("\nExiting program. Goodbye!\n");

                // Free all posts + comments
                while (p->posts) {
                    Post *tempPost = p->posts->next;
                    freeComments(p->posts);
                    free(p->posts);
                    p->posts = tempPost;
                }
                free(p);
                return 0;

            default:
                printf("Invalid choice. Please select again.\n");
        }
    }
}
