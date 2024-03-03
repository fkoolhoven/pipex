/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:45:37 by felicia           #+#    #+#             */
/*   Updated: 2024/03/03 22:57:55 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>

// =====STRUCTS=================================================================

typedef struct s_var
{
	int		argc;
	char	**envp;
	int		last_command;
	int		inputfile_error;
	int		fd_heredoc;
	char	**path_options;
	int		fd_pipe[2];
	pid_t	child;
}	t_var;

// =====FUNCTIONS===============================================================

int		manage_heredoc(t_var var, char **argv);
int		manage_inputfile(t_var var, char **argv);
void	manage_outputfile(t_var var, char **argv);
void	pipex(t_var var, char **argv);
void	command_not_found(char *invalid_command, char zsh_or_pipex);
void	handle_errors(int exitcode);

#endif