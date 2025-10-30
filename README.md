Social Platform (C Implementation)

A modular C program that simulates a mini social media platform, allowing users to:
Create and delete posts
Add and delete comments
Add and delete replies to comments
Navigate between posts (current, next, previous)
View threaded comments and replies
All operations are accessible through a command-line interface (CLI).

Project Structure
Project Root
├── Makefile             # Build automation script
├── README.md            # Project documentation
└── code/
    ├── main.c           # CLI interface
    ├── platform.c/h     # Core platform logic
    ├── post.c/h         # Post structure & functions
    ├── comment.c/h      # Comment structure & functions
    ├── reply.c/h        # Reply structure & functions


Each .h file declares functions and structs, while corresponding .c files define them.
This modular separation keeps the project clean and maintainable.

Compilation
Option 1: Using Makefile (Recommended)

From the project root directory:

# Clean old builds
mingw32-make clean

# Compile the entire project
mingw32-make

# Run the program
mingw32-make run


Note: On Windows, make is usually called mingw32-make.

Option 2: Manual Compilation (Without Makefile)
gcc code/main.c code/platform.c code/post.c code/comment.c code/reply.c -o main
./main

Program Features
1. Post Management

Add a new post

Delete an existing post by number

View a specific post or navigate between posts

2. Comment System

Add comments to the current post

View or delete comments (nth most recent)

3. Reply System

Add replies to a specific comment

View replies (displayed in reverse order for readability)

Delete a specific reply

4. Navigation

nextPost() — move to an older post

previousPost() — move to a newer post

currPost() — view the currently selected post

Example Interaction
1. Add Post
2. View Post by Number
...
Enter your choice: 1
Enter username: saketh
Enter caption: Hello World!
Post added successfully!

Enter your choice: 7
Enter username: aakash
Enter comment: Nice post!
Comment added successfully!

Enter your choice: 10
Enter comment number to reply to: 1
Enter username: jothi
Enter reply: Thanks Aakash!
Reply added successfully!

Memory Management
Every Post node contains a linked list of Comments.
Each Comment node contains a linked list of Replys.
Functions like freeComments() and freeReplies() ensure no memory leaks occur.

Author
Poluru Saketh Koundinya
Designed as part of a Data Structures and Algorithms coursework project.


Future Improvements
Add persistent storage (save/load posts to a file)
Implement timestamps and post sorting
Improve CLI formatting for readability