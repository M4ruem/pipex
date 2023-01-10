/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:04:38 by cormiere          #+#    #+#             */
/*   Updated: 2023/01/09 16:37:55 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	msg_pipe(char *arg)
{
	write(2, ERR_CMD, ft_strlen(ERR_CMD));
	write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

void	msg_error(char *err)
{
	perror(err);
}
