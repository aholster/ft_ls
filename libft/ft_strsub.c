/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsub.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/14 19:18:45 by aholster       #+#    #+#                */
/*   Updated: 2019/11/20 09:14:54 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	total_len;

	total_len = ft_strlen(s);
	if (start > total_len)
	{
		ft_segdefault();
		return (NULL);
	}
	else
	{
		if (start + len <= total_len)
		{
			str = ft_memdup(s + start, len + 1);
		}
		else
		{
			str = ft_memdup(s + start, (total_len + 1) - start);
		}
		return (str);
	}
}
