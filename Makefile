SRCS = main.c signals/signals.c syntax/syntax.c syntax/syntax_utils.c tokens/tokens.c tokens/append.c free.c tokens/expand.c tokens/join.c \
		parse/parse.c parse/search_functions.c parse/fill_nodes.c

OBJS = $(SRCS:.c=.o) 

CC = cc

CFLAGS =  -Werror -Wall -Wextra -g

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

