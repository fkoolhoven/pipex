/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:07:20 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/01/30 13:33:53 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	handle_errors(int exitcode)
{
	if (errno)
		perror("Error message");
	exit(exitcode);
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
