/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:32:25 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/02/01 15:15:02 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	manage_outputfile(t_var var, char **argv)
{
	int	fd2;

	if (var.fd_heredoc >= 0)
		fd2 = open(argv[var.argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd2 = open(argv[var.argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		perror("zsh: output");
		exit (1);
	}
	if (fd2 >= 0)
		if (dup2(fd2, STDOUT_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
}

int	manage_inputfile(t_var var, char **argv)
{
	int	fd1;
	int	inputfile_error;

	inputfile_error = 0;
	if (var.fd_heredoc >= 0)
		return (inputfile_error);
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
	{
		perror("pipex: input");
		inputfile_error = 1;
	}
	if (fd1 >= 0)
		if (dup2(fd1, STDIN_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
	return (inputfile_error);
}

int	manage_heredoc(char **argv)
{
	char	*next_line;
	char	*limiter;
	int		fd_heredoc;

	fd_heredoc = open("heredoc", O_CREAT | O_RDWR | O_EXCL, 0644);
	if (fd_heredoc < 0)
		handle_errors(EXIT_FAILURE);
	limiter = ft_strjoin(argv[2], "\n");
	next_line = get_next_line(0);
	while (ft_strncmp(next_line, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(next_line, fd_heredoc);
		free(next_line);
		next_line = get_next_line(0);
	}
	free(next_line);
	free(limiter);
	close(fd_heredoc);
	fd_heredoc = open("heredoc", O_RDONLY);
	if (dup2(fd_heredoc, STDIN_FILENO) < 0)
		handle_errors(EXIT_FAILURE);
	return (fd_heredoc);
}
