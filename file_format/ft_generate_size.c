/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_size.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:25:41 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 15:40:14 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"

int			ft_generate_size(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char	numbuf[24];
	int		status;

	status = snprintf(numbuf, sizeof(numbuf), "%llu", afile->stat.st_size);
	if (status == -1)
	{
		return (-1);
	}
	else if (ft_fvec_enter_comp(afile->fvect, f_size, numbuf,\
				(size_t)status + 1) == -1)
	{
		return (-1);
	}
	else if (status > acaps->fsize_len)
	{
		acaps->fsize_len = status;
	}
	(void)aflags;
	return (1);
}
