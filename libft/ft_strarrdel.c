/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrdel.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:03:28 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:45:47 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_strarrdel(char ***ap)
{
	size_t	index;

	index = 0;
	while ((*ap)[index] != NULL)
	{
		ft_strdel(&((*ap)[index]));
		index++;
	}
	free(*ap);
	*ap = NULL;
}
