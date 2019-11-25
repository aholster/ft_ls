/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putmem.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/04/05 15:35:32 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:49:54 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putmem(char *mem, size_t len)
{
	write(1, mem, len);
}
