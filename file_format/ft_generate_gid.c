/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_gid.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 07:22:37 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 12:51:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <grp.h>
#include <uuid/uuid.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static char	*fillin_gid(const gid_t st_gid,\
				char numbuf[16],\
				size_t *const restrict asize,\
				const t_flags aflags)
{
	struct group	*gname;

	gname = getgrgid(st_gid);
	if (gname == NULL || (aflags & flg_n) > 0)
	{
		*asize = snprintf(numbuf, 16, "%u", st_gid);
		return (numbuf);
	}
	else
	{
		*asize = ft_strlen(gname->gr_name);
		return (gname->gr_name);
	}
}

int			ft_generate_gid(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char			*gidstr;
	char			numbuf[16];
	size_t			size;

	if ((aflags & flg_o) > 0)
	{
		gidstr = "";
		size = 0;
	}
	else
	{
		gidstr = fillin_gid(afile->stat.st_gid, numbuf, &size, aflags);
		if ((int)size + 1 > acaps->gname_len)
		{
			acaps->gname_len = size + 1;
		}
	}
	if (ft_fvec_enter_comp(afile->fvect, f_gid, gidstr, size + 1) == -1)
	{
		return (-1);
	}
	return (1);
}
