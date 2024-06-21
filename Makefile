SRCS = main.c signals.c syntax.c tokens.c append.c utils.c expand.c

OBJS = $(SRCS:.c=.o) 

CC = cc

CFLAGS =  -Wall -Werror -Wextra -g

NAME = minishell

PRINTFA = ./includes/ft_printf/libftprintf.a

PRINTFD = ./includes/ft_printf

all: $(NAME) 
$(NAME): $(OBJS) $(PRINTFA)
	$(CC) $(OBJS) $(PRINTFA) $(CFLAGS) -lreadline -o $(NAME)

$(PRINTFA): $(PRINTFD)
	make -C	$(PRINTFD)

clean:
	make clean -C $(PRINTFD)
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(PRINTFD)
	rm -rf $(NAME)

re: fclean all

