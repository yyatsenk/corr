/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:10:54 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/04/26 13:10:58 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
#include "op.h"

int g_num_str = 0;
int g_arg_num = 0;

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

typedef struct 	s_comm
{
	char *name;
	int size;
	int position;
	int is_label;
	int	index;
	int code_param;
	t_command_code c_code;
	t_args_code a_code;
	struct s_comm *next;
	struct s_comm *prev;
	t_un_label *down_un;
}				t_command;

typedef struct 	s_i_j
{
	int name_is_set;
	int comm_is_set;
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

t_op    op_tab[17] =
{
	{"live", 1, (2), (0), (0), 1, 10, "alive", 1, 4},
	{"ld", 2, (4), (1), (0), 2, 5, "load", 2, 4},
	{"st", 2, (1), (5), (0), 3, 5, "store", 2, 4},
	{"add", 3, (1), (1), (1), 4, 10, "addition", 2, 4},
	{"sub", 3, (1), (1), (1), 5, 10, "soustraction", 2, 4},
	{"and", 3, (7), (7), (1), 6, 6,"et (and  r1, r2, r3   r1&r2 -> r3", 2, 4},
	{"or", 3, (7), (7), (1), 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 2, 4},
	{"xor", 3, (7), (7), (1), 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 2, 4},
	{"zjmp", 1, (2), (0), (0), 9, 20, "jump if zero", 1, 2},
	{"ldi", 3, (7), (6), (1), 10, 25,	"load index", 2, 2},
	{"sti", 3, (1), (7), (6), 11, 25,	"store index", 2, 2},
	{"fork", 1, (2), (0), (0), 12, 800, "fork", 1, 2},
	{"lld", 2, (4), (1), (0), 13, 10, "long load", 2, 4},
	{"lldi", 3, (7), (6), (1), 14, 50,"long load index", 2, 2},
	{"lfork", 1, (2), (0), (0), 15, 1000, "long fork", 1, 2},
	{"aff", 1, (1), (0), (0), 16, 2, "aff", 2, 4},                     
	{0, 0, (0), (0), (0), 0, 0, 0, 0}
};

void make_binary(char **str_binary, long long num, int num_bytes)
{
	int i;

	(*str_binary) = (char*)malloc(sizeof(char) * (num_bytes * 8) + 1);
	i = (num_bytes * 8) - 1;
	(*str_binary)[(num_bytes * 8)] = '\0';
	while (i >= 0)
	{
		if ((num / 2) == 0)
		{
			if (num == 1)
			{
				(*str_binary)[i] = '1';
				num--;
			}
			else
				(*str_binary)[i] = '0';
		}
		else
		{
			(*str_binary)[i] = num % 2 + '0';
			num = num / 2;
		}
		i--;
	}
}

long long make_decimal(char *octet, int octet_size)
{
	int i;
	long long res;

	res = 0;
	i = 0;
	while (octet[i])
	{
		if (octet[i] == '1')
			res += pow(2, ((i - octet_size) * (-1)));
		i++;
	}
	return (res);
}

long long make_positive(long long num, int bytes)
{
	char *str_binary;
	int i;
	int last_index;
	
	i = 0;
	num = -num;
	make_binary(&str_binary, num, bytes);
	while (str_binary[i])
	{
		if (str_binary[i] == '0')
			str_binary[i] = '1';
		else if (str_binary[i] == '1')
			str_binary[i] = '0';
		i++;
	}
	last_index = (bytes * 7 + bytes / 2);
	if (bytes == 4)
		last_index = 31;
	num = make_decimal(str_binary, last_index);
	num++;
	free(str_binary);
	return (num);
}


int check_name(char *str, char **name, int fd)
{
	int	i;
	int j;
	int kavi;

	kavi = 0;
	if (ft_strncmp(str, ".name", 5))
		return (0);
	i = 5;
	while (str[i] && str[i] != '\"')
	{
		if (str[i]>= 'A' && str[i] <= 'Z')
		{
			printf("Lexical error at [%i:%i]\n", g_num_str, i + 1);
			exit(1);
		}
		i++;
	}
	if (!str[i])
	{
		i = 5;
		while (str[i])
		{
			j = i;
			while ((str[j] >= 'a' && str[j] <= 'z')|| (str[j] >= '0' && str[j] <= '9'))
			{
				j++;
				if (!ft_isalpha(str[j]) && !ft_isdigit(str[j]))
				{
					printf("Syntax error at token [TOKEN][%03i:%03i] INSTRUCTION \"%s\"\n", g_num_str, i + 1, ft_strsub(str, i, j -i));
					exit(1);
				}
			}
			i++;
		}
	}
	if (!str[i])
		printf ("Syntax error at token [TOKEN][%03i:%03i] ENDLINE\n", g_num_str, i + 1);
	kavi++;
	i++;
	j = i;
	while (str[i] && str[i] != '\"')
	{
		//if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
		//	return (0);
		i++;
	}
	if (!str[i])
	{
		while (kavi != 2 && get_next_line(fd, &str)!= 0)
		{
			g_num_str++;
			i = -1;
			while (str[++i])
				if (str[i]== '\"')
				{	
					kavi++;
					break;
				}
		}
		if (kavi == 2)
			printf ("Lexical error at [%i:%i]\n", g_num_str, i + 2);
		else
			printf ("Syntax error at token [TOKEN][%03i:%03i] END \"(null)\"\n",g_num_str, 1);
		exit(1);
	}
	if (str[i] && str[i + 1])
		return (0);
	*name = ft_strsub(str, j, i - j);
	return (1);
}

int check_comment(char *str, char **comment, int fd)
{
	int	i;
	int j;
	int kavi;

	kavi = 0;
	if (ft_strncmp(str, ".comment", 8))
		return (0);
	i = 8;
	while (str[i] && str[i] != '\"')
	{
		if (str[i]>= 'A' && str[i] <= 'Z')
		{
			printf("Lexical error at [%i:%i]\n", g_num_str, i + 1);
			exit(1);
		}
		i++;
	}
	if (!str[i])
	{
		i = 8;
		while (str[i])
		{
			j = i;
			while ((str[j] >= 'a' && str[j] <= 'z')|| (str[j] >= '0' && str[j] <= '9'))
			{
				j++;
				if (!ft_isalpha(str[j]) && !ft_isdigit(str[j]))
				{
					printf("Syntax error at token [TOKEN][%03i:%03i] INSTRUCTION \"%s\"\n", g_num_str, i + 1, ft_strsub(str, i, j -i));
					exit(1);
				}
			}
			i++;
		}
	}
	if (!str[i])
	{
			printf ("Syntax error at token [TOKEN][%03i:%03i] ENDLINE\n", g_num_str, i + 1);
			exit (1);
	}
	kavi++;
	i++;
	j = i;
	while (str[i] && str[i] != '\"')
		i++;
	if (!str[i])
	{
		while (kavi != 2 && get_next_line(fd, &str)!= 0)
		{
			g_num_str++;
			i = -1;
			while (str[++i])
				if (str[i]== '\"')
				{	
					kavi++;
					break;
				}
		}
		if (kavi == 2)
			printf ("Lexical error at [%i:%i]\n", g_num_str, i + 2);
		else
			printf ("Syntax error at token [TOKEN][%03i:%03i] END \"(null)\"\n",g_num_str, 1);
		exit(1);
	}
	if (str[i] && str[i + 1])
		return (0);
	*comment = ft_strsub(str, j, i - j);
	return (1);
}

t_un_label *init_u_label(char *name, int pos_y, int pos_x)
{
	t_un_label *u_label;

	u_label = (t_un_label*)malloc(sizeof(t_un_label)); 
	u_label->name = name;
	u_label->pos_y = pos_y;
	u_label->pos_x = pos_x;
	u_label->next = NULL;
	return (u_label);
}

t_un_label *add_new_u_l(t_un_label *new, t_un_label *begin)
{
	t_un_label	*copy;

	copy = begin;
	if (!begin)
		return (new);
	while (begin->next)
		begin = begin->next;
	begin->next = new;
	return (copy);
}


t_command *add_c(t_command *new, t_command *begin)
{
	t_command	*copy;

	copy = begin;
	if (!begin)
		return (new);
	while (begin->next)
		begin = begin->next;
	begin->next = new;
	new->prev = begin;
	return (copy);
}

t_command *init_c(char *name, int position, int size, int is_label)
{
	t_command *com;

	com = (t_command*)malloc(sizeof(t_command));	
	com->name = name;
	com->size = size;
	com->is_label = is_label;
	com->position = position;
	com->a_code.one.l_name = NULL;
	com->a_code.two.l_name = NULL;
	com->a_code.three.l_name = NULL;
	com->a_code.one.num_of_bytes = 0;
	com->a_code.two.num_of_bytes = 0;
	com->a_code.three.num_of_bytes = 0;
	com->c_code.one = NULL;
	com->c_code.two = NULL;
	com->c_code.three = NULL;
	com->next = NULL;
	com->prev = NULL;
	com->down_un = NULL;
	return (com);
}

char *label_cat(char *str, int *end)
{
	int i;
	int begin;
	char *res;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (!str[i])
		return (NULL);
	begin = i;
	while (str[i] && str[i] != ':')
		i++;
	if (!str[i])
		return (NULL);
	*end = i;
	res = ft_strsub(str, begin, *end - begin);
	return (res);

}

char *comm_cat(char *str, int i)
{
	char *res;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	res = ft_strsub(str, 0, i);
	return (res);
}

char *arg_cat(char *str, int *i)
{
	char *res;
	int begin;

	while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
		(*i)++;
	begin = *i;
	if (!str[*i])
		return (NULL);
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t'\
		&& str[*i] != ',' && str[*i] != '\n')
		(*i)++;
	res = ft_strsub(str, begin, *i - begin);
	return (res);
}

void reg_er(char *arg, char *str, char *command)
{
	int i;
	long long reg;
	
	i = 1;
	if (!arg)
		return;
	if (arg && arg[0] != 'r')
		return;
	reg = ft_atoi(&arg[1]);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return;
		i++;
	}
	printf("Invalid instruction at token [TOKEN][%03i:%03i] INSTRUCTION \"%s\"\n", g_num_str, (int)(ft_strstr(str,command) - str) + 1, command);
	exit(1);
}

void dir_er(char *arg, char *str, char *command)
{
	int i;
	char *value;

	i = -1;
	if (!arg)
		return;
	if (arg && arg[0] != '%')
		return ;
	value = ft_strsub(arg, 1, ft_strlen(arg) - 1);
	while (value[++i])
			if (!ft_isdigit(value[i]) && value[i] != '-' && !ft_isalpha(value[i]) && value[i] != ':')
			{
				printf("Lexical error at [%03i:%03i]\n", g_num_str, (int)(ft_strstr(str,arg) - str) + 1);
				exit(1);
			}
			else if (value[i] == '-' && i != 0)
				return ;
	if (i == 0 || (arg[i - 1] == ':' || arg[i - 1] == '%'))
	{
		printf("Lexical error at [%03i:%03i]\n", g_num_str, (int)(ft_strstr(str,arg) - str) + 1);
		exit(1);
	}			
	printf("Invalid instruction at token [TOKEN][%03i:%03i] INSTRUCTION \"%s\"\n", g_num_str, (int)(ft_strstr(str,command) - str) + 1, command);
	exit(1);
}

void ind_er(char *arg, char *str, char *command)
{
	int num;
	int len_of_num;
	int len_of_str;

	if (!arg)
		return;
	len_of_num = 0;
	len_of_str = ft_strlen(arg);
	if(arg && arg[0] == '-' && (len_of_num = 1))
		num = ft_atoi(arg + 1);
	else
		num = ft_atoi(arg);
	while (num /= 10)
		len_of_num++;
	len_of_num++;	
	if (len_of_num != len_of_str)
		return ;
	printf("Invalid instruction at token [TOKEN][%03i:%03i] INSTRUCTION \"%s\"\n", g_num_str, (int)(ft_strstr(str,command) - str) + 1, command);
	exit(1);
}

void check_maybe_arg(char *str, char *my_str, int i, char *command)
{
	char *arg;
	int i_copy;
	int j;

	j = i;
	i_copy = i;
	arg = arg_cat(my_str, &i);
	reg_er(arg, str, command);
	dir_er(arg, str, command);
	ind_er(arg, str, command);
}

void error_one_arg(char *str, char *command, int i)
{
	
	printf ("Syntax error at token [TOKEN][%03i:%03i] INSTRUCTION \"%s\"\n",g_num_str, i + 1, str);
	exit(1);
}

void put_error(char *str, char *command)
{
	char *my_str;
	int i;
	
	i = -1;
	while (str[++i])
	{
		if ((str[i] < '0' ||  str[i] > '9') && (str[i] <'a' || str[i] > 'z')\
		&& str[i] != ' ' && str[i] != '\t' && str[i] != ':' && str[i] != '%')
		{
			if (str[i] == '#')
				return ;
			printf("Lexical error at [%03i:%03i]\n", g_num_str, i + 1);
			exit(1);
		}
	}
	i = ft_strlen(command) - 1;
	my_str = ft_strstr(str, command);
	check_maybe_arg(str, my_str, i + 1, command);
	while (my_str[++i])
		if (my_str[i] != ' ' && my_str[i] != '\t')
			break;
	if (!my_str[i])
	{
		printf("Syntax error at token [TOKEN][%03i:%03i] ENDLINE\n", g_num_str, (int)ft_strlen(str) + 1);
		exit(1);
	}
	else
		error_one_arg(&my_str[i], command, (int)(ft_strstr(str, &my_str[i]) - str));

}

t_op check_command(char *command, char *str)
{
	int i;

	i = 0;
	while (op_tab[i].name)
	{
		if (!ft_strcmp(command, op_tab[i].name))
			return (op_tab[i]);
		i++;
	}
	put_error(str, command);
	exit(1);
}

void set_data(t_command *c_copy, long long num, char *str, int num_bytes, char *label_name, int bytes)
{
	if (num < 0)
		num = make_positive(num, 2);
	if (g_arg_num == 1 && (c_copy->c_code.one = ft_strdup(str)))
	{
		c_copy->a_code.one.num_of_bytes = bytes;
		c_copy->a_code.one.num_to_code = num;
		c_copy->a_code.one.l_name = label_name;
	}
	else if (g_arg_num == 2 && (c_copy->c_code.two = ft_strdup(str)))
	{
		c_copy->a_code.two.num_of_bytes = bytes;
		c_copy->a_code.two.num_to_code = num;
		c_copy->a_code.two.l_name = label_name;
	}	
	else if (g_arg_num == 3 && (c_copy->c_code.three = ft_strdup(str)))
	{
		c_copy->a_code.three.num_of_bytes = bytes;
		c_copy->a_code.three.num_to_code = num;
		c_copy->a_code.three.l_name = label_name;
	}
}

int check_reg(char *str, int *size, t_command *command)
{
	int i;
	long long reg;
	t_command *c_copy;

	c_copy = command;
	while (c_copy->next)
		c_copy = c_copy->next;		
	i = 1;
	if (str && str[0] != 'r')
		return (0);
	reg = ft_atoi(&str[1]);
	if (reg > 16 || reg <= 0)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	(*size)++;
	set_data(c_copy, reg, ft_strdup("01"), 1, NULL, 1);
	return (1);
}

int check_lable_name(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if ((str[i] < 'a' || str[i] > 'z') && str[i] != '_' && !ft_isdigit(str[i]))
			return (0);
	return (1);
}

int check_duplicates(t_un_label *down, char *name)
{
	t_un_label *copy;

	copy = down;
	while (copy)
	{
		if (!ft_strcmp(name, copy->name))
			return (0);
		copy = copy->next;
	}
	copy = down;
	return (1);
}

void set_dir(t_command *comm, t_op command, long long num, char *label_name, char *str, char *str_orig)
{
	if (g_arg_num == 1 && (comm->c_code.one = ft_strdup("10")))
	{
		comm->a_code.one.num_of_bytes = command.size;
		comm->a_code.one.num_to_code = num;
		comm->a_code.one.l_name = label_name;
	}
	else if (g_arg_num == 2 && (comm->c_code.two = ft_strdup("10")))
	{
		comm->a_code.two.num_of_bytes = command.size;
		comm->a_code.two.num_to_code = num;
		comm->a_code.two.l_name = label_name;
	}
	else if (g_arg_num == 3 && (comm->c_code.three = ft_strdup("10")))
	{
		comm->a_code.three.num_of_bytes = command.size;
		comm->a_code.three.num_to_code = num;
		comm->a_code.three.l_name = label_name;
	}
}

int check_dir(char *str, int *size, t_op command, t_command *comm, char *str_orig)
{
	int i;
	char *lable_name;
	long long num;
	char *value;
	t_command *comm_copy;

	i = -1;
	comm_copy = comm;
	num = -2147483648;
	lable_name = NULL;
	if (str && str[0] != '%')
		return (0);
	value = ft_strsub(str, 1, ft_strlen(str) - 1);
	if (value && value[0] == ':')
	{
		lable_name = ft_strsub(value, 1, ft_strlen(str) - 1);
		if(!check_lable_name(lable_name))
			return (0);
		if (check_duplicates(comm->down_un, lable_name))
		{
			while (comm_copy->next)
				comm_copy = comm_copy->next;
			comm->down_un = add_new_u_l(init_u_label(lable_name, g_num_str, ft_strstr(str_orig, str)- str_orig), comm->down_un);
		}
		free(value);
	}
	else
	{
		num = ft_atoi(value);
		while (value[++i])
			if (!ft_isdigit(value[i]) && value[i] != '-')
				return (0);
			else if (value[i] == '-' && i != 0)
				return (0);
	}
	(*size) += command.size;
	set_dir(comm, command, num, lable_name, str, str_orig);
	return (1);
}

int check_ind(char *str, int *size, t_command *command, char *str_orig)
{
	int num;
	int len_of_num;
	int len_of_str;
	t_command *c_copy;
	int num_copy;
	char *value;
	char *lable_name;

	c_copy = command;
	len_of_num = 0;
	lable_name = NULL;
	while (c_copy->next)
		c_copy = c_copy->next;
	len_of_str = ft_strlen(str);
	if (str && str[0] == ':')
	{
		num_copy = 2147483647;
		lable_name = ft_strsub(str, 1, ft_strlen(str) - 1);
		if(!check_lable_name(lable_name))
			return (0);
		if (check_duplicates(c_copy->down_un, lable_name))
		{
			while (c_copy->next)
				c_copy = c_copy->next;
			c_copy->down_un = add_new_u_l(init_u_label(lable_name, g_num_str, ft_strstr(str_orig, str)- str_orig), c_copy->down_un);
		}
		//free(value);
	}
	else
	{
		if(str && str[0] == '-' && (len_of_num = 1))
			num = ft_atoi(str + 1);
		else
			num = ft_atoi(str);
		num_copy = num;
		while (num /= 10)
			len_of_num++;
		len_of_num++;	
		if (len_of_num != len_of_str)
			return (0);
		if (str[0] == '-')
			num_copy = -num_copy;
	}
	set_data(c_copy, num_copy, ft_strdup("11"), 2, lable_name, 2);
	(*size) += 2;
	return (1);
}

int one_arg(int arg_code, char *str, t_op command, int *size, t_command *comm, char *str_orig)
{
	int error;

	error = 0;
	if (arg_code == 1)
		if (!check_reg(str, size, comm))
			error = 1;
	if (arg_code == 2)
		if (!check_dir(str, size, command, comm, str_orig))
			error = 2;
	if (arg_code == 3)
		if (!check_ind(str, size, comm, str_orig))
			error = 3;
	if (arg_code == 4)
		if (!check_dir(str, size, command, comm, str_orig) &&\
		!check_ind(str, size, comm, str_orig))
			error = 4;
	if (arg_code == 5)
		if (!check_reg(str, size, comm) &&\
		!check_ind(str, size, comm, str_orig))
			error = 5;
	if (arg_code == 6)
		if (!check_reg(str, size, comm)&&\
		!check_dir(str, size, command, comm, str_orig))
			error = 6;
	if (arg_code == 7)
		if (!check_reg(str, size, comm) &&\
		!check_dir(str, size, command, comm, str_orig) &&\
		!check_ind(str, size, comm, str_orig))
			error = 7;
	if (error != 0)
	{
		printf("Args error (%i)\n", error);
		exit(1);
	}
	return (1);
}

int comma_find(char *str, int *i, t_op command, int read)
{
	int comma_found;

	comma_found = 0;
	if (read != command.arg_num)
		while (str[*i])
		{
			if (str[*i] != ' ' && str[*i] != '\t' && str[*i] != ',')
			{
				printf("Comma missed\n");
				exit(1);
			}
			if (str[*i] == ',' && (comma_found = 1))
				break;
			(*i)++;
		}
	/*else
		while (str[*i])
		{
			if (str[*i] != ' ' && str[*i] != '\t' && str[*i] != ';' && str[*i] != '#')
			{
				printf("comma2\n");
				exit(1);
			}
			if (str[*i] == ';' || str[*i] == '#')
				break ;
			(*i)++;
		}*/
	if (!comma_found && read != command.arg_num && command.arg_num != 1)
	{
			printf("Comma missed\n\n");
			exit(1);
	}
	if (str[*i] && str[*i] != '#' && str[*i] != ';')
		(*i)++;
	return (1);
}

int check_end_line(char *str, char *str_orig)
{
	int i;
	int j;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '#' || str[i] == ';')
			return (1);
		if (str[i] != ' ' && str[i] != '\t')
		{
			j = i;
			while (str[j] && str[j] != ' ' && str[j] != '\t')
				j++;
			printf("Syntax error at token [TOKEN][%03i:%03i] \"%s\"\n", g_num_str, (int)(ft_strstr(str_orig, str) - str_orig + 1), str);
			exit(1);
		}
		i++;
	}
	return (1);
}

char *join_cooler(t_command_code code)
{
	char *str_copy_1;
	char *res;

	res = ft_strdup("00");
	str_copy_1 = res;
	if (code.three)
	{
		res = ft_strjoin(code.three, res);
		free(str_copy_1);
	}
	if (code.two)
	{
		str_copy_1 = res;
		res = ft_strjoin(code.two, res);
		free(str_copy_1);
	}
	if (code.one)
	{
		str_copy_1 = res;
		res = ft_strjoin(code.one, res);
		free(str_copy_1);
	}
	return (res);
}

int ft_decimal_code(t_command_code code)
{
	int i;
	int res;
	char *str_b_num;

	i = 0;
	res = 0;
	str_b_num = join_cooler(code);
	while (str_b_num[i])
	{
		if (str_b_num[i] == '1')
			res += pow(2, ((i - 7) * (-1)));
		i++;
	}
	return (res);
}

int check_args(t_op command, char *str, t_command **comm, char *str_orig)
{
	int i;
	char *arg;
	int arg_code;
	int size;
	int read;

	read = 0;
	i = 0;
	if ((*comm)->is_label)
		return (1);
	size = command.cod_octal;
	arg = arg_cat(str, &i);
	arg_code = command.one;
	g_arg_num++;
	one_arg(arg_code, arg, command, &size, *comm, str_orig);
	read++;
	comma_find(str, &i, command, read);
	
	if ((arg_code = command.two) != 0)
	{
		arg = arg_cat(str, &i);
		g_arg_num++;
		one_arg(arg_code, arg, command, &size, *comm, str_orig);
		read++;
		comma_find(str, &i, command, read);
	}
	if ((arg_code = command.three) != 0)
	{
		arg = arg_cat(str, &i);
		g_arg_num++;
		one_arg(arg_code, arg, command, &size, *comm, str_orig);
		read++;
	}
	check_end_line(&str[i], str_orig);
	(*comm)->c_code.result = ft_decimal_code((*comm)->c_code);
	g_arg_num = 0;
	(*comm)->size = size;
	return (1);
}

t_command *check_fill_size(t_command *command, char *str, t_op darling, char *str_orig)
{
	t_command *copy;
	char *arg;
	int i;
	int j;

	j = 0;
	copy = command;
	while(copy->next)
		copy = copy->next;
	copy->index = darling.opcode;
	copy->code_param = darling.cod_octal;
	i = 0;
	if (!copy->prev)
		copy->position = 0;
	else
		copy->position = copy->prev->position + copy->prev->size;
	if (copy->is_label)
		return (copy);
	while(str[i] && ft_strncmp(&str[i], copy->name, ft_strlen(copy->name)))
		i++;
	i += ft_strlen(copy->name);
	while (str[i] && (str[i] == '\t' || str[i] == ' '))
		i++;
	check_args(darling, &str[i], &copy, str_orig);
	return (command);
}

int count_block_size(int fd, char *str, int end, t_command *command)
{
	int i;
	char *constuct;
	t_op darling;
	t_command *c_copy;

	i = end + 1;
	c_copy = command;
	while (c_copy->next)
		c_copy = c_copy->next;
	if(c_copy->is_label)
		command = check_fill_size(command, str, op_tab[16], str);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (!str[i] || str[i] == '#' || str[i] == ';')
		return (0);
	constuct = comm_cat(&str[i], i);
	darling = check_command(constuct, str);
	command = add_c(init_c(darling.name, 0, 0, 0), command);
	command = check_fill_size(command, &str[i], darling, str);
	return (0);
}

int check_line(int fd, char *str, t_command *command, t_i_j n_c_set)
{
	int i;
	char *name;
	int position;
	int end;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != ':')
		i++;
	if (str[i] == ':' && str[i - 1] != '%' && str[i - 1] != ' ' && str[i - 1] != '\t')
	{
		name = label_cat(str, &end);
		command = add_c(init_c(name, 0, 0, 1), command);
		count_block_size(fd, str, end, command);
	}
	else
		count_block_size(fd, str, -1, command);
	return (0);
}

int find_size(t_command *command, char *name, int pos)
{
	int res;
	t_command *copy;

	copy = command;
	while (copy)
	{
		if (copy->name)
			if (!ft_strcmp(copy->name, name) && copy->is_label)
			{
				res = copy->position - pos;
				break;
			}
		copy = copy->next;
	}
	return (res);
}

int find_this_shit(t_command *command, char *name)
{
	t_command *copy;

	copy = command;
	while (copy)
	{
		if (copy->name)
			if (!ft_strcmp(copy->name, name) && copy->is_label)
				return (1);
		copy = copy->next;
	}
	return (0);
}

int lable_is_there(t_command *command)
{
	t_command *c_copy;
	t_un_label *down_copy;

	c_copy = command;
	while (c_copy)
	{
		down_copy = c_copy->down_un;
		while (c_copy->down_un)
		{
				if (!find_this_shit(command, c_copy->down_un->name))
				{	
					printf("No such label %s while attempting to dereference token [TOKEN][%03i:%03i] DIRECT_LABEL \"%s\"\n",\
					c_copy->down_un->name, c_copy->down_un->pos_y,\
					c_copy->down_un->pos_x + 1, ft_strjoin("%:",c_copy->down_un->name));
					exit (1);
				}
				c_copy->down_un = c_copy->down_un->next;
		}
		c_copy->down_un = down_copy;
		c_copy = c_copy->next;
	}
	c_copy = command;
	while (c_copy)
	{
		if (c_copy->a_code.one.l_name)
			c_copy->a_code.one.num_to_code = find_size(command, c_copy->a_code.one.l_name, c_copy->position);
		if (c_copy->a_code.two.l_name)
			c_copy->a_code.two.num_to_code = find_size(command, c_copy->a_code.two.l_name, c_copy->position);
		if (c_copy->a_code.three.l_name)
			c_copy->a_code.three.num_to_code = find_size(command, c_copy->a_code.three.l_name, c_copy->position);
		c_copy = c_copy->next;
	}
	return (1);
}

int code_analyse(int fd, char *str, t_command **comm, t_i_j n_c_set)
{
	t_command *command;
	t_command *c_copy;
	char *my_str;
	int i;

	i = 0;
	command = init_c(NULL, 0, 0, 0);
	check_line(fd, str, command, n_c_set);
	c_copy = command;
	while (c_copy->next && i != 1)
	{
		i++;
		c_copy = c_copy->next;
	}
	if ((!n_c_set.comm_is_set || !n_c_set.name_is_set))
	{
		if (c_copy->is_label == 1)
			printf("Syntax error at token [TOKEN][%03i:%03li] LABEL \"%s:\"\n", g_num_str, (ft_strstr(str, c_copy->name) - str) + 1, c_copy->name);
		else
			printf("Syntax error at token [TOKEN][%03i:%03li] COMMAND \"%s\"\n", g_num_str, (ft_strstr(str, c_copy->name) - str) + 1, c_copy->name);
		exit(1);
	}
	free(str);
	while (get_next_line(fd, &str) != 0)
	{
		g_num_str++;
		if (str && str[0] != '\0' && str[0] != '#')
		check_line(fd, str, command, n_c_set);
		printf ("%s\n", str);
		free(str);
	}
	*comm = command;
	while ((*comm)->next)
		*comm = (*comm)->next;
	if (!lable_is_there(command))
		printf("Pizda prosto");
	*comm = command;
	//while (command->next)
	//	command = command->next;
	return (1);
}
/*
void skip_all_shit(char **str_copy, int fd)
{
	char *str;

	str = *str_copy;
	while (str && (!ft_strncmp(str, "#", 1) || !ft_strcmp(str, "\0")))
	{
		//free(str);
		get_next_line(fd, &str);
		g_num_str++;
	}
}
*/

int check_com_or_name(char *str,char **name, char **comment, t_i_j *n_c_set, int fd)
{
	if (!ft_strncmp(str, ".co", 3))
	{
		if(!check_comment(str, comment, fd))
			return (0);
		n_c_set->comm_is_set = 1;
	}
	else if (!ft_strncmp(str, ".na", 3))
	{
		if(!check_name(str, name, fd))
			return (0);
		n_c_set->name_is_set = 1;
	}
	return (1);
}

int be_valid_dude(int fd, t_command **command, char **name, char **comment)
{
	int i;
	char *str;
	t_i_j n_c_set;

	i = 0;
	n_c_set.name_is_set = 0;
	n_c_set.comm_is_set = 0;
	get_next_line(fd, &str);
	g_num_str++;
	while (str && (!ft_strncmp(str, "#", 1) || !ft_strcmp(str, "\0")))
	{
		free(str);
		get_next_line(fd, &str);
		g_num_str++;
	}
	printf("%s\n",str);
	if (!check_com_or_name(str, name, comment, &n_c_set, fd))
		return (0);
	free(str);
	get_next_line(fd, &str);
	g_num_str++;
	while (str && (!ft_strncmp(str, "#", 1) || !ft_strcmp(str, "\0")))
	{
		free(str);
		get_next_line(fd, &str);
		g_num_str++;
	}
	printf("%s\n",str);
	if (!check_com_or_name(str, name, comment, &n_c_set, fd))
		return (0);
	//free(str);
	if (n_c_set.comm_is_set && n_c_set.name_is_set)
	{
		get_next_line(fd, &str);
		g_num_str++;
	}
	while (str && (!ft_strncmp(str, "#", 1) || !ft_strcmp(str, "\0")))
	{
		free(str);
		if (get_next_line(fd, &str) != 0)
			g_num_str++;
		else
		{
			printf("Syntax error at token [TOKEN][%03i:%03i] END \"(null)\"\n", g_num_str + 1, 1);
			exit(1);
		}
	}
	printf("%s\n",str);
	if (!code_analyse(fd, str, command, n_c_set))
		return (0);
	return (1);
}

int make_cor_file(char *name)
{
	int fd;
	char *name_res;
	char *no_s;
	int i;

	i = 0;
	while (name[i] && name[i] != '.')
		i++;
	no_s = ft_strsub(name, 0, i);
	name_res = ft_strjoin(no_s, ".co");
	fd = open(name_res, O_WRONLY|O_TRUNC|O_CREAT, 0664);
	return (fd);
}

void put_name(int fd, char *name)
{
	int i;
	int name_size;
	char *null;

	i = -1;
	null = ft_strdup("");
	null[0] = 0;
	while (name[++i])
		write(fd, &name[i], 1);
	name_size = i + 3;
	while (++name_size < 128)
		write(fd, &null[0], 1);
}

void put_comment(int fd, char *comment, t_command *command)
{
	int program_len;
	t_command *c_copy;
	char arr[] = {0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0};
	int i;
	int comment_size;
	char *str_binary;
	int beg;
	int end;

	beg = 0;
	end = 8;
	i = -1;
	c_copy = command;
	while (c_copy->next)
		c_copy = c_copy->next;
	program_len = c_copy->position + c_copy->size;
	make_binary(&str_binary, program_len, 12);
	while (++i < sizeof(arr))
	{
		arr[i] = make_decimal(ft_strsub(str_binary, beg , end), 7);
		beg = end;
		end += 8;
	}
	i = -1;
	while (++i < sizeof(arr))
		write(fd, &arr[i], 1);
	i = -1;
	while (comment && comment[++i])
		write(fd, &comment[i], 1);
	comment_size = i - 1;
	while (++comment_size < 2052)
		write(fd, &arr[0], 1);
}

void print_one_byte(long long num, int fd)
{
	char *arr;

	arr = ft_strdup("");
	arr[0] = num;
	write(fd, &arr[0], 1);
}

void print_two_bytes(long long num, int fd)
{
	char *arr;
	int first;
	int second;
	char *str_binary;

	if (num < 0)
		num  = make_positive(num, 2); 
	arr = (char*)malloc(sizeof(char) * 2);
	make_binary(&str_binary, num, 2);
	first = make_decimal(ft_strsub(str_binary, 0, 8), 7);
	second = make_decimal(ft_strsub(str_binary, 8, 16), 7);
	arr[0] = first;
	arr[1] = second;
	write(fd, &arr[0], 1);
	write(fd, &arr[1], 1);
}

void print_fore_bytes(long long num, int fd, int first, int second)
{
	char *arr;
	int third;
	int forth;
	char *str_binary;

	if (num < 0)
		num  = make_positive(num, 4); 
	arr = (char*)malloc(sizeof(char) * 4);
	make_binary(&str_binary, num, 4);
	first = make_decimal(ft_strsub(str_binary, 0, 8), 7);
	second = make_decimal(ft_strsub(str_binary, 8, 16), 7);
	third = make_decimal(ft_strsub(str_binary, 16, 24), 7);
	forth = make_decimal(ft_strsub(str_binary, 24, 32), 7);
	arr[0] = first;
	arr[1] = second;
	arr[2] = third;
	arr[3] = forth;
	write(fd, &arr[0], 1);
	write(fd, &arr[1], 1);
	write(fd, &arr[2], 1);
	write(fd, &arr[3], 1);
}

void write_args(t_args_code args, int fd)
{
	int num_of_arg;
	t_bytes special;
	int first;
	int second;

	num_of_arg = 1;
	while (num_of_arg <= 3)
	{
		if (num_of_arg == 1)
			special = args.one;
		else if (num_of_arg == 2)
			special = args.two;
		else if (num_of_arg == 3)
			special = args.three;
		if (special.num_of_bytes == 1)
			print_one_byte(special.num_to_code, fd);
		else if (special.num_of_bytes == 2)
			print_two_bytes(special.num_to_code, fd);
		else if (special.num_of_bytes == 4)
			print_fore_bytes(special.num_to_code, fd, first, second);
		num_of_arg++;
	}

}

void put_commads(int fd,t_command *command)
{
	t_command *c_copy;
	char arr1[] = {0};
	
	c_copy = command;
	c_copy = c_copy->next;
	while (c_copy)
	{
		if (c_copy->is_label == 0)
		{ 
			arr1[0] = c_copy->index;
			write(fd, &arr1[0], 1);
			if (c_copy->code_param != 1)
			{
				arr1[0] = c_copy->c_code.result;
				write(fd, &arr1[0], 1);
			}
			write_args(c_copy->a_code, fd);
		}
		c_copy = c_copy->next;
	}
}

void make_evil_warrior(t_command *command, char *arg, char *name, char *comment)
{
	char *str;
	int i;
	int fd;
	fd = make_cor_file(arg);
	char arr[] = {0, 234, 131, 243};

	i = -1;
	while (++i < sizeof(arr))
		write(fd, &arr[i], 1);
	printf("%s\n%s\n", name, comment);
	put_name(fd, name);
	put_comment(fd, comment, command);
	put_commads(fd, command);
}

int main(int argv, char **argc)
{
    int fd;
	char *str;
	char *name;
	t_command *command;
	char *comment;
    if (argv != 2)
    {
        printf("Usage ./asm filename\n");
        return (1);
    }
    fd = open(argc[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Can not open file\n");
    	return (0);
	}
	if (!be_valid_dude(fd, &command, &name, &comment))
    {
        printf("Error/Fuck off3");
        return (0);
    }
	make_evil_warrior(command, argc[1], name, comment);
	close(fd);
	return (0);
}
