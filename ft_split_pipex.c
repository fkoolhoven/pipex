/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:29:34 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/01/19 16:36:58 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_free(char **grid)
{
	int	i;

	i = 0;
	while (grid[i] != '\0')
	{
		free(grid[i]);
		i++;
	}
	free(grid);
	return (NULL);
}

static int	ft_calc_strl(char **nxt_str, char c) //write this better
{
	int	strlength;

	strlength = 0;
	if (**nxt_str != '\0')
	{
		while (**nxt_str != '\0' && **nxt_str == c)	
			(*nxt_str)++;
		while (**nxt_str != c && **nxt_str != '\0')
		{
			(*nxt_str)++;
			strlength++;
		}
	}
	return (strlength);
}

static int	ft_calc_nbr_of_strings(char const *s, char c)
{
	int	i;
	int	stringCount;

	stringCount = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
			stringCount++;
		while (s[i] != c && s[i + 1])
			i++;
		i++;
	}
	return (stringCount);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**grid;
	int		nbr_of_strings;
	char	*nxt_str;
	int		strlength;
	int		y;

	nbr_of_strings = ft_calc_nbr_of_strings(s, c);
	grid = (char **)malloc(sizeof(char *) * (nbr_of_strings + 1));
	if (grid == NULL)
		return (NULL);
	y = 0;
	nxt_str = (char *)s;
	strlength = 0;
	while (y < nbr_of_strings)
	{
		strlength = ft_calc_strl(&nxt_str, c);
		grid[y] = (char *)malloc(sizeof(char) * strlength + 1);
		if (grid[y] == NULL)
			return (ft_free(grid));
		ft_strlcpy(grid[y], nxt_str - strlength, strlength + 1);
		y++;
	}
	grid[y] = NULL;
	return (grid);
}
