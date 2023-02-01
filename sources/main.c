/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:42:48 by felicia           #+#    #+#             */
/*   Updated: 2023/02/01 17:21:16 by fkoolhov         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_var	var;

	if (argc < 5)
	{
		ft_putendl_fd("Error message: Too few arguments", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	var.argc = argc;
	var.last_command = argc - 2;
	var.envp = envp;
	var.fd_heredoc = -1;
	var.path_options = find_path(var);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		var.fd_heredoc = manage_heredoc(var, argv);
	var.inputfile_error = manage_inputfile(var, argv);
	manage_outputfile(var, argv);
	pipex(var, argv);
	return (0);
}
