/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_gid_uid.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 12:14:16 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 16:59:34 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

#include "./../incl/ft_long_format.h"

int		ft_generate_gid_uid(char *const restrict aholder,\
			size_t *const restrict aoffset,\
			const struct stat *const restrict stat,\
			const t_longests *const restrict amin_fields)
{
	char			buf[MAX_UIDGID_LEN];
	int				index;
	struct group	*gname;
	struct passwd	*uname;

	index = 0;
	uname = getpwuid(stat->st_uid);
	if (uname != NULL)
	{
		index = sprintf(buf, "%*s  ", amin_fields->uname_len, uname->pw_name);
	}
	else
	{
		index = sprintf(buf, "%*u  ", amin_fields->uname_len, stat->st_uid);
	}
	if (index >= 0)
		*aoffset += index;
	else
		return (-1);
	gname = getgrgid(stat->st_gid);
	if (gname != NULL)
	{
		index = sprintf(buf + index, "%*s  ", amin_fields->gname_len, gname->gr_name);
	}
	else
	{
		index = sprintf(buf + index, "%*u  ", amin_fields->gname_len, stat->st_gid);
	}
	if (index >= 0)
		*aoffset += index;
	else
		return (-1);
	ft_memcpy(aholder, buf, ft_strlen(buf));
	return (1);
}
