/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_range.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/31 21:33:15 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:44:31 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	*ft_range(int min, int max)
{
	int *res;
	int cur;

	cur = min;
	if (min >= max)
		return (0);
	res = (int *)malloc(sizeof(int) * (max - min));
	if (res == NULL)
		return (NULL);
	while (cur <= max)
	{
		res[cur - min] = cur;
		cur++;
	}
	return (res);
}
