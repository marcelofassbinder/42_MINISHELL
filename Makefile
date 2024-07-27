SRCS =  main.c signals/sig_calls.c syntax/syntax.c syntax/syntax_pipe.c syntax/syntax_redirect.c tokens/tokens.c tokens/append.c tokens/expand_cases.c\
		tokens/expand_utils.c tokens/get_values.c  tokens/tokens_utils.c clean/free_shell.c clean/free_tokens.c clean/free_tree.c tokens/expand.c \
		tokens/join.c parse/parse.c parse/search_functions.c parse/fill_nodes.c parse/define_cmd_args.c execution/run.c builtins/cd.c builtins/echo.c\
		builtins/export.c builtins/pwd.c builtins/unset.c builtins/export_utils.c builtins/exit.c builtins/manipulate_envs.c execution/run_parent.c shell_struct/init.c\
		safety/safe_functions.c heredoc/expand_heredoc.c heredoc/run_heredoc.c execution/redirects.c execution/execution_utils.c execution/run_execve.c

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
	@printf "\r \e[1;32mMINISHELL\e[0m compiled successfully\n "
	@printf "\n\e[1;97;3m Welcome to \e[1;3;32mGAU\e[1;3;31mSHE\e[1;3;93mLL!! \n\e[0m"
	@printf "\n\e[97;3m A project developed by the 42 Porto Students:\n \e[1mMarcelo Fassbinder (mfassbin)\e[0m\n \e[1;3mVinicius Vaccari (vivaccar)\n\e[0m"
	@printf "\n Run \001\e[1;97m\002./minishell\001\e[0m\002 to start the program.\n\n"

$(PRINTFA): $(PRINTFD)
    
	make -s -C $(PRINTFD)

clean:
    
	make clean -s -C $(PRINTFD)
	rm -rf $(OBJS)
	@printf " \e[1;31mObjects removed\n\e[0m"

fclean: clean
    
	make fclean -s -C $(PRINTFD)
	rm -rf $(NAME)
	@printf "\n \e[1;31mExecutable removed\n\e[0m"

re: fclean all

.SILENT: