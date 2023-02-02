/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:08:14 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/02/02 11:50:41 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	parent_process(t_var var, int command)
{
	int		waitstatus;
	int		statuscode;

	if (command != var.last_command)
	{
		if (dup2(var.fd_pipe[0], STDIN_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
		close(var.fd_pipe[0]);
		close(var.fd_pipe[1]);
	}
	else if (command == var.last_command)
	{
		waitpid(var.child, &waitstatus, 0);
		statuscode = WEXITSTATUS(waitstatus);
		exit (statuscode);
	}
}

void	execute_command(t_var var, char **argv, int command)
{
	char	**command_options;
	int		i;
	char	*try_path;

	command_options = ft_split_q(argv[command], ' ');
	if (var.path_options == NULL)
		command_not_found(command_options[0], 'z');
	if (access(command_options[0], X_OK) == 0)
		execve(command_options[0], command_options, var.envp);
	i = 0;
	while (var.path_options[i] != NULL)
	{
		try_path = ft_strjoin(var.path_options[i], command_options[0]);
		if (access(try_path, X_OK) == 0)
			execve(try_path, command_options, var.envp);
		free(try_path);
		i++;
	}
	command_not_found(command_options[0], 'p');
}

void	child_process(t_var var, int command, char **argv)
{
	if (var.inputfile_error == 1)
		exit (1);
	if (command != var.last_command)
	{
		if (dup2(var.fd_pipe[1], STDOUT_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
		close(var.fd_pipe[0]);
		close(var.fd_pipe[1]);
	}
	execute_command(var, argv, command);
}

void	pipex(t_var var, char **argv)
{
	int		command;

	if (var.fd_heredoc >= 0)
		command = 3;
	else
		command = 2;
	while (command < var.argc - 1)
	{
		if (command != var.last_command && pipe(var.fd_pipe) < 0)
			handle_errors(EXIT_FAILURE);
		var.child = fork();
		if (var.child < 0)
			handle_errors(EXIT_FAILURE);
		if (var.child == 0)
			child_process(var, command, argv);
		else
			parent_process(var, command);
		var.inputfile_error = 0;
		if (var.fd_heredoc >= 0)
			unlink("heredoc");
		command++;
	}
}
