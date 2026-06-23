CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
DEBUGFLAGS	:= -g -O0

SRCS		:= main.c
OBJS		:= $(SRCS:.c=.o)

NAME		:= swapper

all: $(NAME)
	./$(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(wildcard *.o)

fclean: 
	rm -f $(NAME)

re: fclean all

debug:
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -o $(NAME)
	$(MAKE) all
