/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:17:16 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/11/02 15:06:37 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_fill(int begin, int end, char *new, char const *s1)
{
	int	i;

	i = 0;
	while (begin <= end)
	{
		new[i] = s1[begin];
		i++;
		begin++;
	}
	new[i] = '\0';
	return (new);
}

static int	ft_findend(int begin, int end, char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0' && end > begin)
	{
		if (s1[end] == set[i])
		{
			end--;
			i = -1;
		}
		i++;
	}
	return (end);
}

static int	ft_findbegin(char const *s1, char const *set)
{
	int	begin;
	int	i;

	begin = 0;
	i = 0;
	while (set[i] != '\0')
	{
		if (s1[begin] == set[i])
		{
			begin++;
			i = -1;
		}
		i++;
	}
	return (begin);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		begin;
	int		end;
	size_t	size;

	begin = ft_findbegin(s1, set);
	end = ft_strlen(s1) - 1;
	size = end + 1;
	end = ft_findend(begin, end, s1, set);
	if (end + 1 == begin)
	{
		new = malloc(sizeof(char));
		*new = '\0';
		return (new);
	}
	size = size - (size - end) - (end - begin) + 5;
	new = malloc(sizeof(char) * size);
	if (new == NULL)
		return (NULL);
	new = ft_fill(begin, end, new, s1);
	return (new);
}
