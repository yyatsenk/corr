/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:37:28 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/05/08 18:37:29 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COR_H
# define COR_H

# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "op.h"

int g_num_str;
int g_arg_num;

typedef struct s_all_data
{
    char *str;
	struct s_all_data *next;
}           t_all_data;

typedef enum e_arg
{
    dulya,
    t_reg,
    t_dir,
    t_ind,
	t_dir_or_ind,
	t_reg_or_ind,
	t_reg_or_dir,
	all_poss
}           t_arg;

typedef struct 	s_un_label
{
	char *name;
	int pos_x;
	int pos_y;
	struct s_un_label *next;
}				t_un_label;

typedef struct 	s_command_code
{
	char		*one;
	char		*two;
	char		*three;
	int			result;
}				t_command_code;

typedef struct 	s_bytes
{
	char *l_name;
	long long int num_to_code;
	int num_of_bytes;
	int pos_x;
	int pos_y;
}				t_bytes;

typedef struct 	s_args_code
{
	t_bytes one;
	t_bytes two;
	t_bytes three;
}				t_args_code;


typedef struct 	s_i_j
{
	int name_is_set;
	int comm_is_set;
	char *name;
	char *comment;
}				t_i_j;


typedef struct  s_op
{
    char *name;
	int arg_num;
    t_arg one;
    t_arg two;
    t_arg three;
    int opcode;
    int cycles;
    char *desc;
    int cod_octal;
    int size;
}               t_op;

t_op    op_tab[17];

typedef struct 	s_comm
{
	char *name;
	int size;
	int position;
	int is_label;
	int	index;
	int code_param;
	long long num;
	char *str_orig;
	char *str;
	t_op command_op;
	t_command_code c_code;
	t_args_code a_code;
	struct s_comm *next;
	struct s_comm *prev;
	t_un_label *down_un;
}				t_command;


void make_binary(char **str_binary, long long num, int num_bytes);
long long make_decimal(char *octet, int octet_size);
long long make_positive(long long num, int bytes);
t_un_label *init_u_label(char *name, int pos_y, int pos_x);
t_un_label *add_new_u_l(t_un_label *new, t_un_label *begin);
t_command *add_c(t_command *new, t_command *begin);
t_command *init_c(char **name, int position, int size, int is_label);
char *label_cat(char *str, int *end);
char *comm_cat(char *str, int i);
char *arg_cat(char *str, int *i);
void check_maybe_arg(char *str, char *my_str, int i, char *command);
t_op check_command(char *command, char *str);
void set_data(t_command *c_copy, char **label_name, int bytes);
void set_dir(t_command *comm, char **label_name);
int check_reg(char *str, int *size, t_command *command);
int check_lable_name(char *str);
int check_duplicates(t_un_label *down, char *name);
int comma_find(char *str, int *i, t_op command, int read);
int check_end_line(char *str, char *str_orig);
char *join_cooler(t_command_code *code);
void put_commads(int fd,t_command *command);
void make_evil_warrior(t_command *command, char *arg, char *name, char *comment);
int lable_is_there(t_command *command);
int check_line(int fd, char *str, t_command *command, t_i_j n_c_set);
int check_dir(int *size, t_command *comm);
int check_ind(char **str, int *size, t_command *command, char **str_orig);
int ft_decimal_code(t_command_code code);
int one_arg(int arg_code, int *size, t_command **comm);
int check_args(t_op command, char *str, t_command **comm, char *str_orig);
int code_analyse(int fd, char *str, t_command **comm, t_i_j n_c_set);
int check_name(char *str, char **name, int fd);
int check_comment(char *str, char **comment, int fd);
int be_valid_dude(int fd, t_command **command, t_i_j *n_c_set);
int check_com_or_name(char *str, t_i_j *n_c_set, int fd);
t_all_data *add_all_data(t_all_data *new, t_all_data *begin);
t_all_data *init_all_data(char *str);
void free_all_data(t_all_data *begin);
void print_all_data_free(t_all_data *begin);
void free_all_structs(t_command *command);
int my_pow(int num, int s);
void fore_bites_help(int *argument, int begin, int end, char *str_binary);
#endif
