/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:45:37 by felicia           #+#    #+#             */
/*   Updated: 2023/01/31 17:00:43 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>

// -----structs--------------

typedef struct s_var
{
	int		argc;
	char	**envp;
	int		last_command;
	int		inputfile_error;
	char	**path_options;
	int		fd_pipe[2];
	pid_t	child;
}	t_var;

// -----functions------------

char	**ft_split_q(char const *s, char c);
char	*ft_straddchar(char *s1, char c);
void	command_not_found(char *invalid_command, char zsh_or_pipex);
void	handle_errors(int exitcode);
void	pipex(t_var var, char **argv);

#endif