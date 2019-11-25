/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strarrnew.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 17:49:47 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:55:04 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_strarrnew(size_t size)
{
	char	**str;

	str = (char **)ft_calloc(sizeof(char *), size + 1);
	if (str == NULL)
	{
		return (NULL);
	}
	else
	{
		return (str);
	}
}
