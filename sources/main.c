/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:42:48 by felicia           #+#    #+#             */
/*   Updated: 2023/01/31 21:52:18 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	**find_path(t_var var)
{
	char	*full_path_variable;
	char	**path_options;
	int		i;

	i = 0;
	while (var.envp[i] != NULL)
	{
		if (ft_strnstr(var.envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (var.envp[i] == NULL)
		return (NULL);
	full_path_variable = ft_substr(var.envp[i], 5, ft_strlen(var.envp[i]) - 5);
	path_options = ft_split(full_path_variable, ':');
	free(full_path_variable);
	i = 0;
	while (path_options[i] != NULL)
	{
		path_options[i] = ft_straddchar(path_options[i], '/');
		i++;
	}
	return (path_options);
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

void	manage_outputfile(int argc, char **argv)
{
	int	fd2;

	fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		perror("zsh: output");
		exit (1);
	}
	if (fd2 >= 0)
		if (dup2(fd2, STDOUT_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
}

int	here_doc(char **argv)
{
	char	*next_line;
	char	*limiter;
	int		fd_heredoc;

	fd_heredoc = open("heredoc", O_CREAT | O_RDWR | O_TRUNC | O_EXCL, 0644);
	if (fd_heredoc < 0)
		handle_errors(EXIT_FAILURE);
	limiter = ft_strjoin(argv[2], "\n");
	next_line = get_next_line(0);
	while (ft_strncmp(next_line, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(next_line, fd_heredoc);
		next_line = get_next_line(0);
	}
	if (dup2(fd_heredoc, STDIN_FILENO) < 0)
		handle_errors(EXIT_FAILURE);
	return (fd_heredoc);
}


int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	if (argc < 5)
	{
		ft_putendl_fd("Error message: Too few arguments", 1);
		exit(EXIT_FAILURE);
	}
	var.argc = argc;
	var.last_command = argc - 2;
	var.envp = envp;
	var.fd_heredoc = -1;
	var.path_options = find_path(var);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		var.fd_heredoc = here_doc(argv);
	var.inputfile_error = manage_inputfile(var, argv);
	manage_outputfile(argc, argv);
	pipex(var, argv);
	return (0);
}
