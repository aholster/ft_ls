/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/01/17 10:35:30 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 06:44:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(char const *s1)
{
	char	*output;
	size_t	len;

	len = ft_strlen(s1);
	output = (char *)malloc(sizeof(char) * (len + 1));
	if (output == NULL)
		return (NULL);
	ft_memcpy((void *)output, (const void *)s1, len + 1);
	return (output);
}
