/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/02/18 16:02:34 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:44:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memdup(const void *src, const size_t len)
{
	size_t		index;
	char		*ret;

	index = 0;
	ret = (char *)malloc(sizeof(char) * len);
	if (ret == NULL)
	{
		return (NULL);
	}
	else
	{
		ft_memcpy(ret, src, len);
		return ((void *)ret);
	}
}
