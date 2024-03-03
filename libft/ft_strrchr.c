/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:05:43 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/11/01 22:26:49 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	*storage;

	c = (char)c;
	ptr = (char *)s;
	storage = ptr;
	while (*ptr != '\0')
	{
		if (*ptr == c)
		{
			storage = ptr;
		}
		ptr++;
		if (*ptr == c)
		{
			storage = ptr;
		}
	}
	if (*storage != c && c != '\0')
		return (NULL);
	return (storage);
}
