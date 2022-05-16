/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 22:32:09 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/13 20:52:12 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static void	ft_skip_spaces(const char **str)
{
	while (**str == ' ' || **str == '\t' || **str == '\n'
		|| **str == '\v' || **str == '\f' || **str == '\r')
		(*str)++;
}

static	int	ft_get_sign(const char **str)
{
	if (**str == '-')
	{
		(*str)++;
		return (1);
	}
	if (**str == '+')
		(*str)++;
	return (0);
}

static long long int	ft_str_to_num(const char **str, int *ndigit)
{
	long int	num;

	num = 0;
	while (ft_isdigit(**str))
	{
		num = num * 10 + (**str - '0');
		(*ndigit)++;
		(*str)++;
	}
	return (num);
}

int	ft_atoi(const char *str, bool *err)
{
	int				is_neg;
	int				ndigit;
	long long int	num;

	num = 0;
	is_neg = 0;
	ndigit = 0;
	ft_skip_spaces(&str);
	is_neg = ft_get_sign(&str);
	num = ft_str_to_num(&str, &ndigit);
	if (ndigit > 18 || !is_neg && num > INT_MAX || is_neg && num < INT_MIN)
	{
		*err = true;
		return (0);
	}
	if (is_neg)
		num *= -1;
	return ((int)num);
}
