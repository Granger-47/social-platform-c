# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Target executable
TARGET = main

# Source files inside the code/ directory
SRCS = code/main.c code/platform.c code/post.c code/comment.c code/reply.c

# Object files (same directory, but with .o extension)
OBJS = $(SRCS:.c=.o)

# Default rule
all: $(TARGET)

# Build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to compile each .c into .o
code/%.o: code/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJS) $(TARGET)

# Run program
run: $(TARGET)
	./$(TARGET)
