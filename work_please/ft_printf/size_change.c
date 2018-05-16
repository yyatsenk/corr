/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_change.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 17:00:17 by yyatsenk          #+#    #+#             */
/*   Updated: 2018/02/01 17:00:19 by yyatsenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	l_type(char *format, char ***str, t_typer type, intmax_t num)
{
	if (format[0] == 'l' && format[1] && format[1] != 'l')
	{
		if (type == u)
			**str = ft_itoa_l_u((unsigned long int)num);
		else if (type == o || type == O)
			**str = ft_itoa_base_l_u((long int)num, 8, 0);
		else if (type == x)
			**str = ft_itoa_base_l_u((long int)num, 16, 0);
		else if (type == X)
			**str = ft_itoa_base_l_u((long int)num, 16, 1);
		else
			**str = ft_itoa_l((long int)num);
		return (1);
	}
	else
		return (0);
}

static int	hh_type(char *format, char ***str, t_typer type, intmax_t num)
{
	if (format[0] == 'h' && format[1] && format[1] == 'h')
	{
		if (type == u)
			**str = ft_itoa_base((unsigned char)num, 10, 0);
		else if (type == U)
			**str = ft_itoa_base_u_short((unsigned short)num, 10, 0);
		else if (type == D)
			**str = ft_itoa_base_u_short((unsigned short)num, 10, 0);
		else if (type == o)
			**str = ft_itoa_base((unsigned char)num, 8, 0);
		else if (type == O)
			**str = ft_itoa_base_u_short((unsigned short)num, 8, 0);
		else if (type == x)
			**str = ft_itoa_base((unsigned char)num, 16, 0);
		else if (type == X)
			**str = ft_itoa_base((unsigned char)num, 16, 1);
		else
			**str = ft_itoa_l((signed char)num);
		return (1);
	}
	else
		return (0);
}

static int	ll_type(char *format, char ***str, t_typer type, intmax_t num)
{
	if (!ft_strncmp(format, "ll", 2))
	{
		if (type == u)
			**str = ft_itoa_l_l_u((unsigned long long int)num);
		else if (type == o || type == O)
			**str = ft_itoa_base_u_l_l((unsigned long long int)num, 8, 0);
		else if (type == x)
			**str = ft_itoa_base_u_l_l((unsigned long long int)num, 16, 0);
		else if (type == X)
			**str = ft_itoa_base_u_l_l((unsigned long long int)num, 16, 1);
		else
			**str = ft_itoa_l_l((long long int)num);
		return (1);
	}
	return (0);
}

static int	z_type(char *format, char ***str, t_typer type, intmax_t num)
{
	if (format[0] == 'z')
	{
		if (type == u)
			**str = ft_itoa_base_u_l_l((unsigned long long)num, 10, 0);
		else if (type == U)
			**str = ft_itoa_base_u_l_l((unsigned long long)num, 10, 0);
		else if (type == O || type == o)
			**str = ft_itoa_base_u_l_l((unsigned long long)num, 8, 0);
		else if (type == x)
			**str = ft_itoa_base_u_l_l((unsigned long long)num, 16, 0);
		else if (type == X)
			**str = ft_itoa_base_u_l_l((unsigned long long)num, 16, 1);
		else
			**str = ft_itoa_base_ssize((ssize_t)num, 10, 0);
		return (1);
	}
	return (0);
}

int			mod_norm_help(char *format, char **str, t_typer type, intmax_t num)
{
	if (l_type(format, &str, type, num))
		return (1);
	else if (hh_type(format, &str, type, num))
		return (1);
	else if (ll_type(format, &str, type, num))
		return (1);
	else if (format[0] == 'j')
	{
		if (type == u)
			*str = ft_itoa_l_l_u((unsigned long long int)num);
		else if (type == o || type == O)
			*str = ft_itoa_base_u_l_l((unsigned long long int)num, 8, 0);
		else if (type == x)
			*str = ft_itoa_base_u_l_l((unsigned long long int)num, 16, 0);
		else if (type == X)
			*str = ft_itoa_base_u_l_l((unsigned long long int)num, 16, 1);
		else
			*str = ft_itoa_l_l((long long int)num);
		return (1);
	}
	else if (z_type(format, &str, type, num))
		return (1);
	return (0);
}
