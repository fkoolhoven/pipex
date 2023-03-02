/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 11:32:25 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/02/02 12:58:26 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	manage_outputfile(t_var var, char **argv)
{
	int	fd_out;

	if (var.fd_heredoc >= 0)
		fd_out = open(argv[var.argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd_out = open(argv[var.argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		ft_putstr_fd("zsh: ", STDERR_FILENO);
		perror(argv[var.argc - 1]);
		exit (EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		handle_errors(EXIT_FAILURE);
}

int	manage_inputfile(t_var var, char **argv)
{
	int	fd_in;
	int	inputfile_error;

	inputfile_error = 0;
	if (var.fd_heredoc >= 0)
		return (inputfile_error);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(argv[1]);
		inputfile_error = 1;
	}
	if (fd_in >= 0)
		if (dup2(fd_in, STDIN_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
	return (inputfile_error);
}

void	input_to_heredoc(int fd_heredoc, char *limiter)
{
	char	*next_line;

	ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
	next_line = get_next_line(STDIN_FILENO);
	while (ft_strncmp(next_line, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd("pipe heredoc> ", STDOUT_FILENO);
		ft_putstr_fd(next_line, fd_heredoc);
		free(next_line);
		next_line = get_next_line(STDIN_FILENO);
	}
	free(next_line);
	free(limiter);
}

int	manage_heredoc(t_var var, char **argv)
{
	char	*limiter;
	int		fd_heredoc;

	if (var.argc < 6)
	{
		ft_putendl_fd("Error message: Too few arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	fd_heredoc = open("heredoc", O_CREAT | O_RDWR | O_EXCL, 0644);
	if (fd_heredoc < 0)
		handle_errors(EXIT_FAILURE);
	limiter = ft_strjoin(argv[2], "\n");
	input_to_heredoc(fd_heredoc, limiter);
	close(fd_heredoc);
	fd_heredoc = open("heredoc", O_RDONLY);
	if (dup2(fd_heredoc, STDIN_FILENO) < 0)
		handle_errors(EXIT_FAILURE);
	return (fd_heredoc);
}
