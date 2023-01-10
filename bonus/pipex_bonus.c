/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:05:06 by cormiere          #+#    #+#             */
/*   Updated: 2023/01/10 12:05:47 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	creat_pipes(t_ppxb *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_nmbs - 1)
	{
		if (pipe(pipex->pipe + 2 * i) < 0)
			parent_free(pipex);
		i++;
	}
}

void	close_pipes(t_ppxb *pipex)
{
	int	i;

	i = 0;
	while (i < (pipex->pipe_nmbs))
	{
		close(pipex->pipe[i]);
		i++;
	}
}

void	pipex2(char **argv, char **envp, t_ppxb *pipex)
{
	int	i;

	i = 0;
	pipex->env_path = find_path(envp);
	pipex->cmd_paths = ft_split(pipex->env_path, ':');
	if (!pipex->cmd_paths)
		pipe_free(pipex);
	creat_pipes(pipex);
	pipex->idx = -1;
	while (++(pipex->idx) < pipex->cmd_nmbs)
		child(*pipex, argv, envp, pipex->idx);
	close_pipes(pipex);
	while (i < pipex->cmd_nmbs)
	{
		waitpid(pipex->pid[i], &pipex->bob, 0);
		i++;
	}
	parent_free(pipex);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_ppxb	pipex;

	if (argc < args_in(argv[1], &pipex))
		return (msg(ERR_INPUT));
	get_infile(argv, &pipex);
	get_outfile(argv[argc - 1], &pipex);
	pipex.cmd_nmbs = argc - 3 - pipex.here_doc;
	pipex.pid = malloc(sizeof(pid_t) * pipex.cmd_nmbs);
	if (!pipex.pid)
		write(2, "malloc fail\n", 12);
	pipex.pipe_nmbs = 2 * (pipex.cmd_nmbs - 1);
	pipex.pipe = malloc(sizeof(int) * pipex.pipe_nmbs);
	if (!pipex.pipe)
		msg_error(ERR_PIPE);
	pipex2(argv, envp, &pipex);
	if (WIFEXITED(pipex.bob))
		return (WEXITSTATUS(pipex.bob));
	return (1);
}
