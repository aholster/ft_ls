/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmemendl_fd.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 15:38:58 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:49:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putmemendl_fd(char *mem, size_t len, const int fd)
{
	write(fd, mem, len);
}
