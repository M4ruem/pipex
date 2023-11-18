/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 10:45:10 by cormiere          #+#    #+#             */
/*   Updated: 2023/01/08 15:36:22 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include "../libft/libft.h"

# define ERR_INFILE "Infile"
# define ERR_PIPE "Pipe"
# define ERR_CMD "Command not found\n"

// typedef struct s_pipex
// {
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int		tube[2];
// 	int		infile;
// 	int		outfile;
// 	char	*paths;
// 	char	**cmd_paths;
// 	char	**cmd_args;
// 	char	*cmd;
// 	int		bob;
// }t_pipex;

#define ERR_INPUT "Usage: pipex infile cmd1 cmd2 outfile\n"
#define ERR_CMD "Command not found\n"
#define ERR_OUTFILE "Error opening outfile\n"
#define MAX_PATH_LENGTH 4096

typedef struct s_pipex {
    pid_t child_pid1;
    pid_t child_pid2;
    int pipe_fd[2];
    int input_fd;
    int output_fd;
    char *env_paths;
    char **command_directories;
    char **command_args;
    char *command_path;
    int exit_status;
} t_pipex;

/* childs.c */
void first_child_process(t_pipex pipe_info, char **av, char **envp);
void second_child_process(t_pipex pipe_info, char **av, char **envp);

/* free.c */
void	parent_cleanup(t_pipex *pipex);
void	child_cleanup(t_pipex *pipex);

/* error.c */
void	handle_error(char *err);
int		print_message(char *err);

#endif
