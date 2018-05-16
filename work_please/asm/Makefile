# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/16 11:06:57 by yyatsenk          #+#    #+#              #
#    Updated: 2018/05/16 11:06:59 by yyatsenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRCS := src/main.c 
SRCS +=	src/all_cat.c 
SRCS +=	src/all_data_maintain.c 
SRCS +=	src/be_valid_dude.c 
SRCS +=	src/byte_operations.c 
SRCS +=	src/check_args.c
SRCS += src/check_comment.c 
SRCS +=	src/check_dir.c 
SRCS +=	src/check_ind.c 
SRCS +=	src/check_line.c 
SRCS +=	src/check_name.c 
SRCS +=	src/check_reg.c
SRCS +=	src/code_analyse.c 
SRCS +=	src/dem_code_one_arg.c 
SRCS +=	src/error_1.c 
SRCS +=	src/error_2.c 
SRCS +=	src/fore_bites_help.c 
SRCS +=	src/free_all_structs.c 
SRCS +=	src/lable_command_maintain.c
SRCS += src/make_file_name_com.c 
SRCS +=	src/put_data_0.c 
SRCS +=	src/set_data.c 
SRCS +=	src/sheluha_1.c 
SRCS +=	src/sheluha.c 

FLAGS = -Wall -Werror -Wextra 

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ../libft re
	@make -C ../ft_printf re
	@gcc -o $(NAME) $(FLAGS) ./src/*.c ../libft/libft.a ../ft_printf/libftprintf.a
	@echo "\033[0;32mAsm done!\033[0m"

clean:
	@make clean -C ../libft
	@make -C ../ft_printf clean
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C ../libft
	@make -C ../ft_printf fclean
	@rm -f $(NAME)

re: fclean all

.phony: all clean fclean re
