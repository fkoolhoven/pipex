/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:29:34 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/10/18 19:33:08 by fkoolhov         ###   ########.fr       */
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

static void	ft_calc_strl(char **nxt_str, int *strl, char c)
{
	*strl = 0;
	while (**nxt_str != '\0')
	{
		if (**nxt_str != c)
		{
			while (**nxt_str != c && **nxt_str != '\0')
			{
				(*nxt_str)++;
				(*strl)++;
			}
			return ;
		}		
		if (**nxt_str == '\0')
		{
			break ;
		}
		(*nxt_str)++;
	}
}

static int	ft_calc_nbr_of_strings(char const *s, char c)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			y++;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
			}
		}
		if (s[i] == '\0')
		{
			break ;
		}
		i++;
	}
	return (y);
}

char	**ft_split(char const *s, char c)
{
	char	**grid;
	int		nbr_of_strings;
	char	*nxt_str;
	int		strl;
	int		y;

	nbr_of_strings = ft_calc_nbr_of_strings(s, c);
	grid = (char **)malloc(sizeof(char *) * (nbr_of_strings + 1));
	if (grid == NULL)
		return (NULL);
	y = 0;
	nxt_str = (char *)s;
	strl = 0;
	while (y < nbr_of_strings)
	{
		ft_calc_strl(&nxt_str, &strl, c);
		grid[y] = (char *)malloc(sizeof(char) * strl + 1);
		if (grid[y] == NULL)
			return (ft_free(grid));
		ft_strlcpy(grid[y], nxt_str - strl, strl + 1);
		y++;
	}
	grid[y] = NULL;
	return (grid);
}
