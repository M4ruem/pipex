
#include "../includes/pipex.h"

// void	parent_free(t_pipex *pipex)
// {
// 	int	i;

// 	i = 0;
// 	close(pipex->infile);
// 	close(pipex->outfile);
// 	while (pipex->cmd_paths[i])
// 	{
// 		free(pipex->cmd_paths[i]);
// 		i++;
// 	}
// 	free(pipex->cmd_paths);
// }

// void	child_free(t_pipex *pipex)
// {
// 	int	i;

// 	i = 0;
// 	while (pipex->cmd_args[i])
// 	{
// 		free(pipex->cmd_args[i]);
// 		i++;
// 	}
// 	free(pipex->cmd_args);
// 	free(pipex->cmd);
// }

void parent_cleanup(t_pipex *pipe_info) {
    int i;

    i = 0;
    close(pipe_info->input_fd);
    close(pipe_info->output_fd);
    while (pipe_info->command_directories[i]) {
        free(pipe_info->command_directories[i]);
        i++;
    }
    free(pipe_info->command_directories);
}

void child_cleanup(t_pipex *pipe_info) {
    int i;

    i = 0;
    while (pipe_info->command_args[i]) {
        free(pipe_info->command_args[i]);
        i++;
    }
    free(pipe_info->command_args);
    free(pipe_info->command_path);
}