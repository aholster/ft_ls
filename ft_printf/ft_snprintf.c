/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_snprintf.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/09/13 15:19:17 by aholster       #+#    #+#                */
/*   Updated: 2019/09/18 18:30:35 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "./incl/ft_internals.h"

int	ft_snprintf(char *str, size_t size, const char *restrict format, ...)
{
	va_list	args;
	int		holder;

	va_start(args, format);
	holder = ft_vsnprintf(str, size, format, args);
	va_end(args);
	return (holder);
}
