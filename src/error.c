
#include "../includes/pipex.h"

// int	msg(char *err)
// {
// 	write(2, err, ft_strlen(err));
// 	return (1);
// }

// void	msg_error(char *err)
// {
// 	perror(err);
// 	close(0);
// 	close(1);
// 	close(2);
// 	exit (1);
// }

int print_message(char *message) {
    write(2, message, strlen(message));
    return 1;
}

void handle_error(char *error_message) {
    perror(error_message);
    close(0);
    close(1);
    close(2);
    exit(1);
}