SRCS = main.c

OBJS = $(SRCS:.c=.o) 

CC = cc

CFLAGS =  -Wall -Werror -Wextra

NAME = minishell

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -lreadline -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
	