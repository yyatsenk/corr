# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/29 13:27:42 by yyatsenk          #+#    #+#              #
#    Updated: 2017/11/15 16:20:04 by yyatsenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CFLAGS += -Wall -Werror -Wextra
SRC =	ft_printf.c ft_white_swap_num.c\
		width_num.c precision_num.c\
		flag_width_pres_maintain.c size_change.c\
		ft_modify.c num_maintain.c width_char.c\
		flag_width_pres_maintain_char.c write_wchar.c\
		ft_size_bin.c char_maintain.c\
		error_maintain.c char_maintain_percent.c\
		width_ptr.c precision_ptr.c ptr_maintain.c\
		width_str.c precision_str.c \
		flag_width_pres_maintain_str.c ft_wstrlen.c write_wstr.c\
		width_wstr.c precision_wstr.c flag_width_pres_maintain_wstr.c\
		str_maintain.c way_definder.c format_cat.c libft/ft_atoi.c\
		libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_itoa_base.c\
		libft/ft_itoa_base_l_u.c libft/ft_itoa_base_size.c libft/ft_itoa_base_ssize.c libft/ft_itoa_base_u_l_l.c\
		libft/ft_atoi.c libft/ft_atoi.c libft/ft_atoi.c libft/ft_atoi.c\
		libft/ft_itoa_base_u_short.c libft/ft_itoa_l.c libft/ft_itoa_l_l.c libft/ft_itoa_l_l_u.c\
		libft/ft_itoa_l_u.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_strncmp.c\
		libft/ft_strncpy.c libft/ft_strnew.c libft/ft_white_swap.c libft/ft_white_swap_wstr.c libft/ft_wstrjoin.c\
		libft/ft_wstrncpy.c libft/ft_strcpy.c libft/ft_wcharlen.c

SRC_OBJ = $(subst .c,.o, $(SRC))		

LIBFT = libft/libft.a

all: $(NAME)

%.o: %.c
	@gcc $(CFLAGS) -c $^ -o $@

$(NAME): $(SRC_OBJ)
	@/bin/rm -f $(NAME)
	@ar rcs $(NAME) $(SRC_OBJ)
	@echo "\033[32mBuilt\033[0m"

clean:
	@/bin/rm -f *.o
	@/bin/rm -f libft/*.o
	@/bin/rm -f libft/libft.a
	@echo "\033[32mCleaned\033[0m"

fclean: clean
	@/bin/rm -rf $(NAME)
	@echo "\033[32mRemoved Executable\033[0m"

re: clean all