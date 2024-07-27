SRCS =  main.c signals/sig_calls.c syntax/syntax.c syntax/syntax_pipe.c syntax/syntax_redirect.c \
		tokens/tokens.c tokens/append.c tokens/expand_cases.c tokens/expand_utils.c tokens/getvalues.c  tokens/tokens_utils.c clean/free_shell.c clean/free_tokens.c clean/free_tree.c \
        tokens/expand.c tokens/join.c parse/parse.c parse/search_functions.c parse/fill_nodes.c parse/define_cmd_args.c parse/print_tree.c execution/run.c builtins/cd.c builtins/echo.c \
        builtins/export.c builtins/pwd.c builtins/unset.c builtins/export_utils.c builtins/exit.c builtins/manipulate_envs.c execution/run_parent.c safety/safe_functions.c \
		heredoc/expand_heredoc.c heredoc/run_heredoc.c execution/redirects.c execution/execution_utils.c execution/run_execve.c shell_struct/init.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS =  -Werror -Wall -Wextra -g

NAME = minishell

PRINTFA = ./includes/ft_printf/libftprintf.a

PRINTFD = ./includes/ft_printf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(PRINTFA)
    
	$(CC) $(OBJS) $(PRINTFA) $(CFLAGS) -lreadline -o $(NAME)

$(PRINTFA): $(PRINTFD)
    
	make -C $(PRINTFD)

clean:
    
	make clean -C $(PRINTFD)
    
	rm -rf $(OBJS)

fclean: clean
    
	make fclean -C $(PRINTFD)
    
	rm -rf $(NAME)

re: fclean all