/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gannemar <gannemar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 15:47:02 by gannemar          #+#    #+#             */
/*   Updated: 2022/05/17 15:47:05 by gannemar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_str_len(long int num)
{
	size_t	str_len;

	str_len = 0;
	while (num != 0)
	{
		str_len++;
		num /= 10;
	}
	return (str_len);
}

static void	to_str(long int num, char *str, size_t idx)
{
	if (num >= 10)
		to_str(num / 10, str, --idx);
	else
		idx--;
	str[idx] = '0' + (num % 10);
}

static char	*handle_null(void)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	long int	num;
	int			is_neg;
	char		*str;
	size_t		str_len;

	num = n;
	is_neg = 0;
	if (num == 0)
		return (handle_null());
	if (num < 0)
	{
		is_neg = 1;
		num *= -1;
	}
	str_len = get_str_len(num) + is_neg;
	str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (!str)
		return (NULL);
	if (is_neg)
		str[0] = '-';
	to_str(num, str, str_len);
	str[str_len] = '\0';
	return (str);
}
