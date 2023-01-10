/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:46:24 by cormiere          #+#    #+#             */
/*   Updated: 2023/01/09 12:21:08 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	first_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[1], 1);
	close(pipex.tube[1]);
	close(pipex.tube[0]);
	dup2(pipex.infile, 0);
	close(pipex.infile);
	close(pipex.outfile);
	pipex.cmd_args = ft_strsplit(argv[2], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		parent_free(&pipex);
		close(0);
		close(1);
		close(2);
		exit(127);
	}
	parent_free(&pipex);
	execve(pipex.cmd, pipex.cmd_args, envp);
	child_free(&pipex);
	close(0);
	close(1);
	close(2);
	exit (1);
}

void	second_child(t_pipex pipex, char *argv[], char *envp[])
{
	dup2(pipex.tube[0], 0);
	close(pipex.tube[0]);
	close(pipex.tube[1]);
	dup2(pipex.outfile, 1);
	close(pipex.outfile);
	close(pipex.infile);
	pipex.cmd_args = ft_strsplit(argv[3], ' ');
	pipex.cmd = get_cmd(pipex.cmd_paths, pipex.cmd_args[0]);
	if (!pipex.cmd)
	{
		child_free(&pipex);
		msg(ERR_CMD);
		parent_free(&pipex);
		close(0);
		close(1);
		close(2);
		exit(127);
	}
	parent_free(&pipex);
	execve(pipex.cmd, pipex.cmd_args, envp);
	child_free(&pipex);
	close(0);
	close(1);
	close(2);
	exit (1);
}
