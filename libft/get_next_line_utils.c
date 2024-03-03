/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:14:53 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/01/31 20:48:59 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_and_ret_null(char *str1, char *str2)
{
	free (str1);
	free (str2);
	return (NULL);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	length;

	length = 0;
	if (!s)
		return (0);
	while (s[length] != '\0')
		length++;
	return (length);
}

char	*ft_strjoin_gnl(char *result, char *buffer)
{
	size_t	len_prefix;
	size_t	len_suffix;
	char	*ptr;
	int		i;
	int		j;

	if (!result || !buffer)
		return (NULL);
	len_prefix = ft_strlen_gnl(result);
	len_suffix = ft_strlen_gnl(buffer);
	ptr = ft_calloc_bzero(len_prefix + len_suffix + 1, sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (result[i++] != '\0')
		ptr[i - 1] = result[i - 1];
	while (buffer[j] != '\0')
	{
		ptr[i - 1] = buffer[j];
		i++;
		j++;
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr != (char)c)
	{
		if (*ptr == '\0')
			return (ptr);
		ptr++;
	}
	return (ptr);
}

char	*ft_calloc_bzero(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;
	size_t	n;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	n = count * size;
	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			ptr[i] = 0;
			i++;
		}	
	}
	return (ptr);
}
