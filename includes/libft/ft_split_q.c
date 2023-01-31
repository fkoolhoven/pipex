/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_q.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:01:57 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/01/31 17:02:32 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **result)
{
	int	i;

	i = 0;
	while (result[i] != '\0')
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

static int	ft_use_quotes_as_delimiter(char **next_str)
{
	char	quotes_type;
	int		strlength;

	quotes_type = **next_str;
	strlength = 0;
	(*next_str)++;
	while (**next_str != quotes_type && **next_str != '\0')
	{
		strlength++;
		(*next_str)++;
	}
	return (strlength);
}

static int	ft_calc_strl(char **next_str, char c)
{
	int		strlength;

	strlength = 0;
	while (**next_str != '\0' && **next_str == c)
		(*next_str)++;
	if (**next_str == '\'' || **next_str == '\"')
		return (ft_use_quotes_as_delimiter(next_str));
	while (**next_str != c && **next_str != '\0')
	{
		(*next_str)++;
		strlength++;
	}
	return (strlength);
}

static int	ft_calc_nbr_of_strings(char const *s, char c)
{
	int		i;
	int		string_count;

	string_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			string_count++;
			break ;
		}
		if (s[i] != c)
			string_count++;
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (string_count);
}

char	**ft_split_q(char const *s, char c)
{
	char	**result;
	int		nbr_of_strings;
	char	*next_str;
	int		strlength;
	int		i;

	nbr_of_strings = ft_calc_nbr_of_strings(s, c);
	result = (char **)malloc(sizeof(char *) * (nbr_of_strings + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	strlength = 0;
	while (i < nbr_of_strings)
	{
		strlength = ft_calc_strl(&next_str, c);
		result[i] = (char *)malloc(sizeof(char) * strlength + 1);
		if (result[i] == NULL)
			return (ft_free(result));
		ft_strlcpy(result[i], next_str - strlength, strlength + 1);
		i++;
	}
	result[i] = NULL;
	return (result);
}
