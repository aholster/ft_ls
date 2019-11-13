/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_uid.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 06:56:56 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 12:50:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <pwd.h>
#include <uuid/uuid.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static char	*fillin_uid(const uid_t st_uid,\
				char numbuf[16],\
				size_t *const restrict asize,\
				const t_flags aflags)
{
	struct passwd	*uname;

	uname = getpwuid(st_uid);
	if (uname == NULL || (aflags & flg_n) > 0)
	{
		*asize = snprintf(numbuf, 16, "%u", st_uid);
		return (numbuf);
	}
	else
	{
		*asize = ft_strlen(uname->pw_name);
		return (uname->pw_name);
	}
}

int			ft_generate_uid(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char			*uidstr;
	char			numbuf[16];
	size_t			size;

	if ((aflags & flg_g) > 0)
	{
		uidstr = "";
		size = 0;
	}
	else
	{
		uidstr = fillin_uid(afile->stat.st_uid, numbuf, &size, aflags);
		if ((int)size + 1 > acaps->uname_len)
		{
			acaps->uname_len = size + 1;
		}
	}
	if (ft_fvec_enter_comp(afile->fvect, f_uid, uidstr, size + 1) == -1)
	{
		return (-1);
	}
	return (1);
}
