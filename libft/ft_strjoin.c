/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:44:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2022/10/17 20:06:05 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_prefix;
	size_t	len_suffix;
	char	*ptr;
	int		i;
	int		j;

	len_prefix = ft_strlen(s1);
	len_suffix = ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len_prefix + len_suffix) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i++] != '\0')
		ptr[i - 1] = s1[i - 1];
	while (s2[j] != '\0')
	{
		ptr[i - 1] = s2[j];
		i++;
		j++;
	}
	ptr[i - 1] = '\0';
	return (ptr);
}
