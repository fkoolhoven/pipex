/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:29:48 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/01/31 16:31:10 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddchar(char *s1, char c)
{
	size_t	len_prefix;
	char	*new_string;

	len_prefix = ft_strlen(s1);
	new_string = malloc(sizeof(char) * (len_prefix + 1) + 1);
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s1, len_prefix + 2);
	free (s1);
	new_string[len_prefix] = c;
	new_string[len_prefix + 1] = '\0';
	return (new_string);
}
