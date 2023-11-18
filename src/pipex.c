
#include "../includes/pipex.h"

// char	*find_path(char **envp)
// {
// 	while (ft_strncmp("PATH", *envp, 4))
// 		envp++;
// 	return (*envp + 5);
// }

// void	close_pipes(t_pipex *pipex)
// {
// 	close(pipex->tube[0]);
// 	close(pipex->tube[1]);
// }

// void	boby(char **av, char **envp, t_pipex *pipex)
// {
// 	if (pipex->infile > 0)
// 	{
// 		pipex->pid1 = fork();
// 		if (pipex->pid1 == 0)
// 			first_child(*pipex, av, envp);
// 	}
// 	pipex->pid2 = fork();
// 	if (pipex->pid2 == 0)
// 		second_child(*pipex, av, envp);
// 	close_pipes(pipex);
// 	waitpid(pipex->pid1, NULL, 0);
// 	waitpid(pipex->pid2, &pipex->bob, 0);
// 	parent_free(pipex);
// 	close(0);
// 	close(1);
// 	close(2);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_pipex	pipex;

// 	if (ac != 5)
// 		return (msg(ERR_INPUT));
// 	pipex.infile = open(av[1], O_RDONLY);
// 	if (pipex.infile < 0)
// 		perror(av[1]);
// 	pipex.outfile = open(av[ac - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
// 	if (pipex.outfile < 0)
// 		msg_error(ERR_OUTFILE);
// 	if (pipe(pipex.tube) < 0)
// 		msg_error(ERR_PIPE);
// 	pipex.paths = find_path(envp);
// 	pipex.cmd_paths = ft_strsplit(pipex.paths, ':');
// 	boby(av, envp, &pipex);
// 	exit(WEXITSTATUS(pipex.bob));
// }


char *find_path(char **envp) {
    while (ft_strncmp("PATH", *envp, 4))
        envp++;
    return (*envp + 5);
}

void close_pipe_fds(t_pipex *pipe_info) {
    close(pipe_info->pipe_fd[0]);
    close(pipe_info->pipe_fd[1]);
}

void execute_pipex(char **argv, char **envp, t_pipex *pipe_info) {
    if (pipe_info->input_fd > 0) {
        pipe_info->child_pid1 = fork();
        if (pipe_info->child_pid1 == 0)
            first_child_process(*pipe_info, argv, envp);
    }
    pipe_info->child_pid2 = fork();
    if (pipe_info->child_pid2 == 0)
        second_child_process(*pipe_info, argv, envp);
    close_pipe_fds(pipe_info);
    waitpid(pipe_info->child_pid1, NULL, 0);
    waitpid(pipe_info->child_pid2, &pipe_info->exit_status, 0);
    parent_cleanup(pipe_info);
    close(0);
    close(1);
    close(2);
}

int main(int argc, char **argv, char **envp) {
    t_pipex pipe_info;

    if (argc != 5)
        return print_message(ERR_INPUT);
    pipe_info.input_fd = open(argv[1], O_RDONLY);
    if (pipe_info.input_fd < 0)
        perror(argv[1]);
    pipe_info.output_fd = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
    if (pipe_info.output_fd < 0)
        handle_error(ERR_OUTFILE);
    if (pipe(pipe_info.pipe_fd) < 0)
        handle_error("Pipe error\n");
    pipe_info.env_paths = find_path(envp);
    pipe_info.command_directories = ft_strsplit(pipe_info.env_paths, ':');
    execute_pipex(argv, envp, &pipe_info);
    exit(WEXITSTATUS(pipe_info.exit_status));
}