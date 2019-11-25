/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmem_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 15:37:04 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:49:59 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putmem_fd(char *mem, size_t len, const int fd)
{
	write(fd, mem, len);
}
