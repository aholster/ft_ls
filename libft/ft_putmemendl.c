/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmemendl.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 15:35:31 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:49:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putmemendl(char *mem, size_t len)
{
	write(1, mem, len);
}
