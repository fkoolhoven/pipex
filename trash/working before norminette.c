/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working before norminette.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:42:48 by felicia           #+#    #+#             */
/*   Updated: 2023/01/30 13:13:38 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	handle_errors(int exitcode)
{
	if (errno)
		perror("Error message");
	exit(exitcode);
}

void	parent_process(int command, int argc, int fd_pipe[2], int infile_error, pid_t child)
{
	int		waitstatus;
	int		statuscode;
	int		LAST_COMMAND;

	LAST_COMMAND = argc - 2;
	if (command != LAST_COMMAND) // rewrite to LAST_COMMAND maybe in struct?
	{
		if (dup2(fd_pipe[0], STDIN_FILENO) < 0) // remove this check maybe?
			handle_errors(EXIT_FAILURE);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	if (command == LAST_COMMAND)
	{
		waitpid(child, &waitstatus, 0);
		statuscode = WEXITSTATUS(waitstatus);
		exit (statuscode);
	}
	infile_error = 0;
}

void	command_not_found(char *invalid_command, char zsh_or_pipex)
{
	if (zsh_or_pipex == 'z')
	{
		ft_putstr_fd("zsh: command not found: ", STDERR_FILENO);
		ft_putendl_fd(invalid_command, STDERR_FILENO);
	}
	else if (zsh_or_pipex == 'p')
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(invalid_command, STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	exit (127);
}

void	execute_command(char **argv, char **path_options, int command, char **envp)
{
	char	**command_options;
	int		i;
	char	*try_path;

	command_options = ft_split_pipex(argv[command], ' ');
	i = 0;
	if (path_options == NULL)
		command_not_found(command_options[0], 'z');
	while (path_options[i] != NULL)
	{
		try_path = ft_strjoin(path_options[i], command_options[0]);
		if (access(try_path, X_OK) == 0)
		{	
			//fprintf(stderr, "do we get here?\nlast_command = %i", LAST_COMMAND);
			execve(try_path, command_options, envp);
		}
		free(try_path);
		i++;
	}
	command_not_found(command_options[0], 'p');
}

void	child_process(int command, int argc, int fd_pipe[2], char **argv, char **path_options, char **envp, int infile_error) // too many argcs
{
	int		LAST_COMMAND;

	if (infile_error == 1)
		exit (1);
	LAST_COMMAND = argc - 2;
	if (command != LAST_COMMAND) // rewrite to LAST_COMMAND maybe in struct? REWIRTE OUT OF LOOP? IS IT POSSIBLE? WHY DID I DO IT IN THE FIRST PLACE, because of statuscode or something?
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) < 0)
			handle_errors(EXIT_FAILURE);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	execute_command(argv, path_options, command, envp);
}

int	manage_files(int argc, char **argv)
{
	int	fd1;
	int	fd2;
	int	infile_error;

	infile_error = 0;
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd1 < 0)
	{
		perror("pipex: input");
		infile_error = 1;
	}
	if (fd2 < 0)
	{
		perror("zsh: output");
		exit (1);
	}
	if (fd1 >= 0)
		dup2(fd1, STDIN_FILENO); // check for err?
	if (fd2 >= 0)
		dup2(fd2, STDOUT_FILENO);
	return (infile_error);
}

void	fork_process(int argc, char **argv, char **path_options, char **envp)
{
	int		fd_pipe[2];
	int		command;
	pid_t	child;
	int		LAST_COMMAND;
	int		infile_error;

	LAST_COMMAND = argc - 2;
	command = 2;
	infile_error = manage_files(argc, argv);
	while (command < argc - 1)
	{
		if (command != LAST_COMMAND && pipe(fd_pipe) < 0) // rewrite to LAST_COMMAND maybe in struct?
			handle_errors(EXIT_FAILURE);
		child = fork();
		if (child < 0)
			handle_errors(EXIT_FAILURE);
		if (child == 0)
			child_process(command, argc, fd_pipe, argv, path_options, envp, infile_error);
		else
			parent_process(command, argc, fd_pipe, infile_error, child);
		infile_error = 0;
		command++;
	}
}

char	**find_path(char **envp)
{
	char 	*PATH;
	char	**path_options;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			break;
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
	PATH = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	path_options = ft_split(PATH, ':');
	free(PATH);
	i = 0;
	while (path_options[i] != NULL)
	{
		path_options[i] = ft_strjoin_pipex(path_options[i], "/");
		i++;
	}
	return (path_options);
}

int main(int argc, char **argv, char **envp)
{
	char	**path_options;

	if (argc < 5)
	{
		ft_putendl_fd("Error message: Too few arguments", 1);
		exit(EXIT_FAILURE);
	}	
	path_options = find_path(envp);
	fork_process(argc, argv, path_options, envp);
	// close files ALSO WHEN ERROR OCCURS IN MANAGE FILES?
	exit(EXIT_SUCCESS);
}
