LIBFT	= ../
NAME	= libft_printf.a
SRCS	= ft_printf.c	\
						ft_printchar.c	ft_printstr.c	ft_printptr.c	\
						ft_print_d.c	ft_print_u.c	ft_print_xX.c	\

DIR_S	= srcs
DIR_O	= temp
SR		= $(addprefix $(DIR_S)/,$(SRCS))
OB		= $(addprefix $(DIR_O)/,$(SRCS:.c=.o))

CC		= clang
RM		= rm -f
CFLAGS	= -g -Wall -Wextra -Werror -I
INCLUDE	= ./include

all		= $(NAME)

$(NAME) : $(OB)
					make -C $(LIBFT)
					cp ../libft.a $(NAME)
					ar -rcs $(NAME) $(OB)

$(DIR_O)/%.o: $(DIR_S)/%.c
							mkdir -p temp
							$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean	:
			$(RM) $(OB)
			$(RM) -rf $(DIR_O)
			make clean -C $(LIBFT)

fclean	: clean
				$(RM) $(NAME)
				$(RM) ../libft.a

re		: fclean $(NAME)

.PHONY: all clean fclean re
