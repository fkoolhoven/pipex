/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:42:48 by felicia           #+#    #+#             */
/*   Updated: 2023/01/19 16:45:52 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	handle_errors(int exitcode)
{
	char	*err_msg;

	err_msg = strerror(errno);
	// ft_putendl_fd(err_msg, STDERR_FILENO);
	
	
	// command not found = 127
	if (errno)
	{
		fprintf(stderr, "errno = %i\n", errno);
		perror("Error message");
	}
	// close files in here? have to pass fd's then
	exit(exitcode);
}

void	execute_command(char **argv, char **possible_paths, int command, char **envp)
{
	char	**command_options;
	int		i;
	char	*try_path;

	command_options = ft_split_pipex(argv[command], ' '); // going wrong here
	// int	x = 0;
	// while (command_options[x] != NULL)
	// {
	// 	fprintf(stderr, "command_options[%i] = %s\n", x, command_options[x]);
	// 	x++;
	// }
	i = 0;
	while (possible_paths[i] != NULL)
	{
		try_path = ft_strjoin(possible_paths[i], command_options[0]); // rewrite for awk?
		if (access(try_path, X_OK) == 0)
			execve(try_path, command_options, envp);
		free(try_path);
		i++;
	}
	fprintf(stderr, "failure at command\n");
	// handle_errors(127);
}

void	parent_process(int command, int argc, int fd_pipe[2])
{
	int		waitStatus;
	int		statusCode;

	wait(&waitStatus);
	if (WIFEXITED(waitStatus))
	{
		statusCode = WEXITSTATUS(waitStatus);
		if (statusCode != 0)
		{
			fprintf(stderr, "Child statusCode is not zero! Statuscode = %i\n", statusCode);
			handle_errors(statusCode);
		}
	}
	if (command < argc - 2) // rewrite to LAST_COMMAND maybe in struct?
	{
		if (dup2(fd_pipe[0], STDIN_FILENO) < 0)
		{
			fprintf(stderr, "failure at duplicating stdin in fork_process\n");
			handle_errors(EXIT_FAILURE);
		}	
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
}

void	child_process(int command, int argc, int fd_pipe[2], char **argv, char **possible_paths, char **envp) // too many argcs
{
	if (command < argc - 2) // rewrite to LAST_COMMAND maybe in struct?
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) < 0)
		{
			fprintf(stderr, "failure at duplicating stdout in fork_process\n");
			handle_errors(EXIT_FAILURE);
		}
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	execute_command(argv, possible_paths, command, envp);
}

void	fork_process(int argc, char **argv, char **possible_paths, char **envp)
{
	int		fd_pipe[2];
	int		command;
	pid_t	child;

	command = 2;
	while (command < argc - 1)
	{
		if (command < argc - 2 && pipe(fd_pipe) < 0) // rewrite to LAST_COMMAND maybe in struct?
		{
			fprintf(stderr, "failure at piping\n");
			handle_errors(EXIT_FAILURE);
		}
		child = fork();
		if (child < 0)
		{
			fprintf(stderr, "failure at fork_process\n");
			handle_errors(EXIT_FAILURE);
		}
		if (child == 0)
			child_process(command, argc, fd_pipe, argv, possible_paths, envp);
		else
			parent_process(command, argc, fd_pipe);
		command++;
	}
}

char	**find_path(char **envp)
{
	char 	*PATH;
	char	**possible_paths;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5)) // check for memory leak
			break;
		i++;
	}
	PATH = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5); // check for memory leak
	possible_paths = ft_split(PATH, ':'); // check for memory leak
	i = 0;
	while (possible_paths[i] != NULL)
	{
		possible_paths[i] = ft_strjoin(possible_paths[i], "/"); // will cause memory leak!!!
		i++;
	}
	free(PATH);
	return (possible_paths);
}

void	manage_files(int argc, char **argv)
{
	int	fd1;
	int	fd2;

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0 || fd2 < 0)
	{
		fprintf(stderr, "failure at opening files\n");
		handle_errors(EXIT_FAILURE);
	}
	if (dup2(fd1, STDIN_FILENO) < 0 || dup2(fd2, STDOUT_FILENO) < 0)
	{
		fprintf(stderr, "failure at duplicating fd1 or fd 2\n");
		handle_errors(EXIT_FAILURE);
	}
}

int main(int argc, char **argv, char **envp)
{
	char	**possible_paths;

	if (argc < 5)
	{
		fprintf(stderr, "failure at argcount\n");
		handle_errors(EXIT_FAILURE);
	}
	manage_files(argc, argv);
	possible_paths = find_path(envp);
	fork_process(argc, argv, possible_paths, envp);
	// close files ALSO WHEN ERROR OCCURS IN MANAGE FILES?
	exit(EXIT_SUCCESS);
}
