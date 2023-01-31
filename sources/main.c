/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:42:48 by felicia           #+#    #+#             */
/*   Updated: 2023/01/31 17:00:47 by fkoolhov         ###   ########.fr       */
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

int	manage_files(int argc, char **argv)
{
	int	fd1;
	int	fd2;
	int	inputfile_error;

	inputfile_error = 0;
	fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
	{
		perror("pipex: input");
		inputfile_error = 1;
	}
	fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		close (fd1);
		perror("zsh: output");
		exit (1);
	}
	if (fd1 >= 0)
		if (dup2(fd1, STDIN_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
	if (fd2 >= 0)
		if (dup2(fd2, STDOUT_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
	return (inputfile_error);
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
	var.path_options = find_path(var);
	var.inputfile_error = manage_files(argc, argv);
	pipex(var, argv);
	exit(EXIT_SUCCESS);
}
