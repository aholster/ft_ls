/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag_arg_extract.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/03 21:32:51 by aholster       #+#    #+#                */
/*   Updated: 2019/11/11 22:02:49 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_flag_parser.h"
#include <limits.h>

void	ft_flag_arg_extract(const char *const restrict format,\
			size_t *const restrict aindex,\
			t_writer *const restrict clipb)
{
	t_flag *const restrict	flags = clipb->flags;
	int						num;

	(void)format;
	num = va_arg(clipb->args, int);
	if (num < 0)
	{
		flags->padding = ((-num) & UINT_MAX);
		ft_turn_on_flag('-', flags);
	}
	else
	{
		flags->padding = num;
	}
	*aindex += 1;
}
