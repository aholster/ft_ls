/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_inode.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:17:32 by aholster       #+#    #+#                */
/*   Updated: 2019/12/07 03:44:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"

#include "../incl/ft_file_format.h"

int			ft_generate_inode(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char	numbuf[24];
	int		status;

	status = ft_snprintf(numbuf, sizeof(numbuf), "%llu", afile->stat.st_ino);
	if (status == -1)
	{
		return (-1);
	}
	else if (ft_fvec_enter_comp(afile, f_inode,\
					numbuf, (size_t)status + 1) == -1)
	{
		return (-1);
	}
	else if (status > acaps->inode_len)
	{
		acaps->inode_len = status;
	}
	(void)aflags;
	return (1);
}
