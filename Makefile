# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnikolov <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 18:02:56 by rmamison          #+#    #+#              #
#    Updated: 2022/09/19 14:04:28 by rmamison         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft

SRC =	main.c \
		builtins/builtin.c \
		builtins/echo.c \
		builtins/cd.c \
		builtins/env.c \
		builtins/exit.c \
		builtins/export.c \
		builtins/unset.c \
		builtins/pwd.c \
		signals/signals.c \
		env/environment.c \
		utils/errors.c \
		utils/utils.c \
		jud/handle_input.c \
		jud/lexical_split.c \
		jud/help_lexical_split.c \
		jud/analyse_lexical.c \
		jud/init_struct_shell.c \
		jud/list_utils.c \
		jud/help_list_utils.c \
		jud/free_utils.c \
		jud/redirection_parse.c \
		jud/treat_quote_dollar.c \
		jud/help_treat_quote_dollar.c \
		jud/parse_clean_quote.c \
		jud/heredoc.c \
		jud/exec.c \
		jud/exec_utils.c \
		jud/init_redirection.c \

SRCS = $(addprefix srcs/, $(SRC))
DIR_S = srcs

INCLUDE = -I includes/ -I libft/ \
		  -I ~/.brew/Cellar/readline/8.1.2/include/readline

READLINE_LIB = -L /Users/$(USER)/.brew/Cellar/readline/8.1.2/lib -lreadline
LIB_LIBFT = libft/libft.a

FLAGS = -Wall -Wextra -Werror #-g3 -o0 -fsanitize=address
CC = gcc

RM = rm -rf

DIR = file_object
OB = $(addprefix $(DIR)/, $(SRCS:%.c=%.o))
CLONE = file_object \
	file_object/srcs \
	file_object/srcs/builtins \
	file_object/srcs/env \
	file_object/srcs/signals \
	file_object/srcs/utils \
	file_object/srcs/jud \

$(DIR)/%.o : %.c
	@mkdir -p $(CLONE)
	@$(CC) $(INCLUDE) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OB)
	@echo "Compiling libft..."
	@make -C $(LIBFT)
	@echo "compilation [libft] is done!"
	@echo "Compiling minishell..."
	@$(CC) $(FLAGS) $(READLINE_LIB) $(OB) -o $@ libft/libft.a
	@echo "Compilation [minishell] is done!"

clean :
	@echo "Remove all file_object..."
	@$(RM) $(DIR)
	@make clean -C $(LIBFT)
	@echo "file_object removed!"

fclean : clean
	@echo "Remove all file_object & file_binary..."
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)
	@echo "object and binary_file removed!"

re : fclean $(NAME)
.PHONY: all clean fclean re
