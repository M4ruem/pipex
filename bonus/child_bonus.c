/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:04:54 by cormiere          #+#    #+#             */
/*   Updated: 2023/01/10 16:10:58 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

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
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static void	sub_dup2(int zero, int first)
{
	if (zero != -1)
		dup2(zero, 0);
	if (first != -1)
		dup2(first, 1);
}

void	minichild(t_ppxb *p, char **argv, char **envp)
{
	p->cmd_args = ft_split(argv[2 + p->here_doc + p->idx], ' ');
	p->cmd = get_cmd(p->cmd_paths, p->cmd_args[0]);
	if (!p->cmd)
	{
		msg_pipe(p->cmd_args[0]);
		child_free(p);
		parent_free(p);
		exit(127);
	}
	if (p->infile != -1)
		execve(p->cmd, p->cmd_args, envp);
}

void	maxchild(t_ppxb p, char **argv, char **envp, int i)
{
	if (!p.pid[i])
	{
		if (p.idx == 0)
			sub_dup2(p.infile, p.pipe[1]);
		else if (p.idx == p.cmd_nmbs - 1)
		{
			if (p.outfile < 0)
			{
				msg_error(ERR_OUTFILE);
				exit (1);
			}
			sub_dup2(p.pipe[2 * p.idx - 2], p.outfile);
		}
		else
			sub_dup2(p.pipe[2 * p.idx - 2], p.pipe[2 * p.idx + 1]);
		close_pipes(&p);
		minichild(&p, argv, envp);
		if (i != 0)
			execve(p.cmd, p.cmd_args, envp);
		child_free(&p);
		parent_free(&p);
		exit (1);
	}
}

void	child(t_ppxb p, char **argv, char **envp, int i)
{
	p.pid[i] = fork();
	if (p.pid[i] == -1)
	{
		child_free(&p);
		exit (1);
	}
	maxchild(p, argv, envp, i);
}
