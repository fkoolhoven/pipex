/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:21:12 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/01/31 20:48:57 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_line(char *buffer, int strlen, int start)
{
	char	*line;
	int		x;

	line = ft_calloc_bzero(strlen + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	x = 0;
	while (strlen-- > 0)
		line[x++] = buffer[start++];
	return (line);
}

char	*get_line_mine(char *buffer)
{
	int			start;
	int			strlen;
	char		*line;
	static int	i;

	start = i;
	strlen = 0;
	if (i == -1 || *buffer == '\0')
	{
		i = 0;
		return (NULL);
	}	
	while (buffer[i] && buffer[i] != '\n')
	{
		strlen++;
		i++;
	}
	if (buffer[i] == '\n')
		strlen++;
	if (buffer[i++] == '\0' && start != 0 && strlen == 0)
		return (NULL);
	if (buffer[i - 1] == '\0')
		i = -1;
	line = create_line(buffer, strlen, start);
	return (line);
}

char	*add_bytes(char *old_result, char *temp_buffer, int bytes_read)
{
	char	*new_result;

	if (bytes_read == -1)
	{
		get_line_mine("\0");
		return (free_and_ret_null(old_result, NULL));
	}
	temp_buffer[bytes_read] = '\0';
	new_result = ft_strjoin_gnl(old_result, temp_buffer);
	if (new_result == NULL)
		return (free_and_ret_null(old_result, new_result));
	free (old_result);
	return (new_result);
}

char	*read_line(int fd, char *result)
{
	char	*temp_buffer;
	int		bytes_read;

	if (!result)
		result = ft_calloc_bzero(1, 1);
	if (result == NULL)
		return (NULL);
	temp_buffer = ft_calloc_bzero(BUFFER_SIZE + 1, sizeof(char));
	if (temp_buffer == NULL)
		return (free_and_ret_null(result, NULL));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		result = add_bytes(result, temp_buffer, bytes_read);
		if (result == NULL)
			return (free_and_ret_null(temp_buffer, NULL));
		if (*ft_strchr(temp_buffer, '\n') == '\n')
			break ;
	}
	if (*temp_buffer == '\0' && *result == '\0')
		return (free_and_ret_null(temp_buffer, result));
	free(temp_buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (buffer == NULL)
	{
		get_line_mine("\0");
		return (NULL);
	}	
	line = get_line_mine(buffer);
	if (line == NULL)
	{
		get_line_mine("\0");
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	return (line);
}
