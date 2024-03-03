/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:58:12 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/11/03 17:28:54 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_convert(size_t size, int n, char *s)
{
	while (size > 0 && n != 0)
	{
		size--;
		s[size] = 48 + (n % 10);
		n = n / 10;
	}
	return (s);
}

static	char	*ft_edge(char *s, int n, size_t size)
{
	s[0] = '-';
	s[size - 1] = '8';
	n = 214748364;
	while (size > 0 && n != 0)
	{
		size--;
		s[size - 1] = 48 + (n % 10);
		n = n / 10;
	}
	return (s);
}

static size_t	ft_calc_size(int n)
{
	size_t	size;

	size = 0;
	while (n != 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	size;

	if (n == 0)
		size = 1;
	else
		size = ft_calc_size(n);
	if (n < 0)
		size = size + 1;
	s = malloc(sizeof(char) * size + 1);
	if (s == NULL)
		return (NULL);
	s[size] = '\0';
	if (n == 0)
		s[0] = 48;
	if (n == -2147483648)
		return (s = ft_edge(s, n, size));
	if (n < 0)
	{
		s[0] = '-';
		n = n * -1;
	}
	s = ft_convert(size, n, s);
	return (s);
}
