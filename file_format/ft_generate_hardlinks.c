/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_hardlinks.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:22:30 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 15:40:05 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"

int			ft_generate_hardlinks(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char	numbuf[24];
	int		status;

	status = snprintf(numbuf, sizeof(numbuf), "%hu", afile->stat.st_nlink);
	if (status == -1)
	{
		return (-1);
	}
	else if (ft_fvec_enter_comp(afile->fvect, f_nlnk,\
					numbuf, (size_t)status + 1) == -1)
	{
		return (-1);
	}
	else if (status + 1 > acaps->hlink_len)
	{
		acaps->hlink_len = status + 1;
	}
	(void)aflags;
	return (1);
}
