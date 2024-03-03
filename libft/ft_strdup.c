/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:58:44 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/10/17 14:29:26 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	strlen;
	char	*ptr;
	char	*storage;

	strlen = ft_strlen(s1);
	ptr = malloc(sizeof(char) * strlen + 1);
	if (ptr == NULL)
		return (NULL);
	storage = ptr;
	while (*s1 != '\0')
	{
		*ptr = *s1;
		s1++;
		ptr++;
	}
	*ptr = '\0';
	return (storage);
}
