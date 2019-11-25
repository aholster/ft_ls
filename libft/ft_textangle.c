/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_textangle.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/24 18:02:21 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:45:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	**ft_textangle(size_t x, size_t y, char c)
{
	char	**rectangle;
	size_t	index;

	index = 0;
	rectangle = (char **)malloc(sizeof(char *) * y + 1);
	if (rectangle == NULL)
		return (NULL);
	rectangle[y] = NULL;
	while (index < y)
	{
		rectangle[index] = ft_stralloc(x, c);
		if (rectangle[index] == NULL)
		{
			ft_strarrdel(&rectangle);
			return (NULL);
		}
		index++;
	}
	return (rectangle);
}
