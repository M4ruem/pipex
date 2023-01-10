/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:46:44 by cormiere          #+#    #+#             */
/*   Updated: 2023/01/10 12:05:52 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->tube[0]);
	close(pipex->tube[1]);
}

void	boby(char *argv[], char *envp[], t_pipex *pipex)
{
	if (pipex->infile > 0)
	{
		pipex->pid1 = fork();
		if (pipex->pid1 == 0)
			first_child(*pipex, argv, envp);
	}
	pipex->pid2 = fork();
	if (pipex->pid2 == 0)
		second_child(*pipex, argv, envp);
	close_pipes(pipex);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, &pipex->bob, 0);
	parent_free(pipex);
	close(0);
	close(1);
	close(2);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	if (argc != 5)
		return (msg(ERR_INPUT));
	pipex.infile = open(argv[1], O_RDONLY);
	if (pipex.infile < 0)
		msg_inf(argv[1]);
	pipex.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pipex.outfile < 0)
		msg_error(ERR_OUTFILE);
	if (pipe(pipex.tube) < 0)
		msg_error(ERR_PIPE);
	pipex.paths = find_path(envp);
	pipex.cmd_paths = ft_strsplit(pipex.paths, ':');
	boby(argv, envp, &pipex);
	exit(WEXITSTATUS(pipex.bob));
}
