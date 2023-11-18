
#include "../includes/pipex.h"

// static char *get_cmd(char **paths, char *cmd) {
//     char *tmp, *command;

//     if (access(cmd, X_OK) == 0)
//         return strdup(cmd);

//     while (*paths) {
//         tmp = ft_strjoin(*paths, "/");
//         command = ft_strjoin(tmp, cmd);
//         free(tmp);
//         if (access(command, X_OK) == 0)
//             return command;
//         free(command);
//         paths++;
//     }
//     return NULL;
// }

// static void execute_command(t_pipex *pipex, char *cmd_line, char **envp) {
//     pipex->cmd_args = ft_strsplit(cmd_line, ' ');
//     pipex->cmd = get_cmd(pipex->cmd_paths, pipex->cmd_args[0]);
//     if (!pipex->cmd) {
//         child_free(pipex);
//         msg(ERR_CMD);
//         parent_free(pipex);
//         exit(127);
//     }
//     execve(pipex->cmd, pipex->cmd_args, envp);
//     child_free(pipex);
//     parent_free(pipex);
//     exit(1);
// }

// void first_child(t_pipex pipex, char **av, char **envp) {
//     dup2(pipex.tube[1], STDOUT_FILENO);
//     close(pipex.tube[0]);
//     close(pipex.tube[1]);
//     dup2(pipex.infile, STDIN_FILENO);
//     execute_command(&pipex, av[2], envp);
// }

// void second_child(t_pipex pipex, char **av, char **envp) {
//     dup2(pipex.tube[0], STDIN_FILENO);
//     close(pipex.tube[0]);
//     close(pipex.tube[1]);
//     dup2(pipex.outfile, STDOUT_FILENO);
//     execute_command(&pipex, av[3], envp);
// }

static char *find_executable_path(char **paths, char *command) {
    char *temp, *full_path;

    if (access(command, X_OK) == 0)
        return strdup(command);

    while (*paths) {
        temp = ft_strjoin(*paths, "/");
        full_path = ft_strjoin(temp, command);
        free(temp);
        if (access(full_path, X_OK) == 0)
            return full_path;
        free(full_path);
        paths++;
    }
    return NULL;
}

static void execute_command(t_pipex *pipe_info, char *command_line, char **envp) {
    pipe_info->command_args = ft_strsplit(command_line, ' ');
    pipe_info->command_path = find_executable_path(pipe_info->command_directories, pipe_info->command_args[0]);
    if (!pipe_info->command_path) {
        child_cleanup(pipe_info);
        print_message(ERR_CMD);
        parent_cleanup(pipe_info);
        exit(127);
    }
    execve(pipe_info->command_path, pipe_info->command_args, envp);
    child_cleanup(pipe_info);
    parent_cleanup(pipe_info);
    exit(1);
}

void first_child_process(t_pipex pipe_info, char **av, char **envp) {
    dup2(pipe_info.pipe_fd[1], STDOUT_FILENO);
    close(pipe_info.pipe_fd[0]);
    close(pipe_info.pipe_fd[1]);
    dup2(pipe_info.input_fd, STDIN_FILENO);
    execute_command(&pipe_info, av[2], envp);
}

void second_child_process(t_pipex pipe_info, char **av, char **envp) {
    dup2(pipe_info.pipe_fd[0], STDIN_FILENO);
    close(pipe_info.pipe_fd[0]);
    close(pipe_info.pipe_fd[1]);
    dup2(pipe_info.output_fd, STDOUT_FILENO);
    execute_command(&pipe_info, av[3], envp);
}