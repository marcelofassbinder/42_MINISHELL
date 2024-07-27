
CFILES = ft_printf.c ft_print_format.c ft_putchar.c ft_putstr.c ft_putmem.c ft_putnbr_base.c ft_putnbr_int.c 

OBJS = ${CFILES:.c=.o}

RM = rm -rf

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

LIBFTA = ./libft/libft.a

LIBFTD = ./libft

all: $(NAME)

$(OBJS): $(CFILES)
	$(CC) $(CFLAGS) -c $(CFILES)

$(NAME): $(OBJS) $(LIBFTA) 
	cp $(LIBFTA) $(NAME)
	ar rcs $(NAME) $(OBJS)
	@echo "\r \e[1;93mFT_PRINTF \e[0mfiles compiled successfully"

$(LIBFTA): $(LIBFTD)
	make -C $(LIBFTD) 

clean:
	$(RM) $(OBJS)
	make clean -s -C $(LIBFTD) 

fclean: clean
	$(RM) $(NAME)
	make fclean -s -C $(LIBFTD) 

re: fclean all

.SILENT: