/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:17:01 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/11/02 18:03:36 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	strlen;

	strlen = ft_strlen(s);
	if (start >= strlen)
	{
		ptr = malloc(sizeof(char));
		*ptr = '\0';
		return (ptr);
	}
	if (len > strlen)
		ptr = malloc(sizeof(char) * strlen + 1 - start);
	else
		ptr = malloc(sizeof(char) * len + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
