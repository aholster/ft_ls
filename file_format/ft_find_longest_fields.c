/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_longest_fields.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:50:00 by aholster       #+#    #+#                */
/*   Updated: 2019/11/12 05:28:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static void	gid_uid_len(const t_finfo *const restrict afinfo,\
				t_longests *const restrict amin_fields)
{
	int				uidlen;
	int				gidlen;
	struct group	*gname;
	struct passwd	*uname;

	uname = getpwuid(afinfo->stat.st_uid);
	if (uname != NULL)
		uidlen = (int)ft_strlen(uname->pw_name);
	else
		uidlen = (int)ft_ull_len(afinfo->stat.st_uid, 10);
	if (uidlen > amin_fields->uname_len)
		amin_fields->uname_len = uidlen;
	gname = getgrgid(afinfo->stat.st_gid);
	if (gname != NULL)
		gidlen = (int)ft_strlen(gname->gr_name);
	else
		gidlen = (int)ft_ull_len(afinfo->stat.st_uid, 10);
	if (gidlen > amin_fields->gname_len)
		amin_fields->gname_len = gidlen;
}

static void	find_long_format_fields(const t_finfo *restrict lst_iterator,\
				t_longests *const restrict amin_fields)
{
	int						namelen;
	ino_t					inode;
	nlink_t					hlinks;

	hlinks = 0;
	inode = 0;
	while (lst_iterator != NULL)
	{
		namelen = (int)ft_strlen(lst_iterator->s_name);
		if (namelen + 1 > amin_fields->fname_len)
		{
			amin_fields->fname_len = namelen + 1;
		}
		if (lst_iterator->stat.st_ino > inode)
		{
			inode = lst_iterator->stat.st_ino;
		}
		if (lst_iterator->stat.st_nlink > hlinks)
		{
			hlinks = lst_iterator->stat.st_nlink;
		}
		gid_uid_len(lst_iterator, amin_fields);
		lst_iterator = lst_iterator->next;
	}
	amin_fields->hlink_len = ft_ull_len(hlinks, 10);
	amin_fields->inode_len = ft_ull_len(inode, 10);
}

static void	find_inode_fields(const t_finfo *restrict lst_iterator,\
				t_longests *const restrict amin_fields)
{
	int						namelen;
	uint64_t				inode;

	inode = 0;
	while (lst_iterator != NULL)
	{
		namelen = (int)ft_strlen(lst_iterator->s_name);
		if (namelen + 1 > amin_fields->fname_len)
		{
			amin_fields->fname_len = namelen + 1;
		}
		if (lst_iterator->stat.st_ino > inode)
		{
			inode = lst_iterator->stat.st_ino;
		}
		lst_iterator = lst_iterator->next;
	}
	amin_fields->inode_len = ft_ull_len(inode, 10);
}

static void	find_basic_fields(const t_finfo *restrict lst_iterator,\
				t_longests *const restrict amin_fields)
{
	int						namelen;

	while (lst_iterator != NULL)
	{
		namelen = (int)ft_strlen(lst_iterator->s_name);
		if (namelen + 1 > amin_fields->fname_len)
		{
			amin_fields->fname_len = namelen + 1;
		}
		lst_iterator = lst_iterator->next;
	}
}

void		ft_find_longest_fields(const t_finfo *restrict finfo_stack,\
				t_longests *const restrict amin_fields,\
				int *const restrict amax_len,\
				const t_flags *const restrict aflags)
{
	ft_bzero(amin_fields, sizeof(t_longests));
	if (((*aflags) & flg_l) > 0)
	{
		find_long_format_fields(finfo_stack, amin_fields);
	}
	else if (((*aflags) & flg_i) > 0)
	{
		find_inode_fields(finfo_stack, amin_fields);
		*amax_len = amin_fields->fname_len + amin_fields->inode_len;
	}
	else
	{
		find_basic_fields(finfo_stack, amin_fields);
		*amax_len = amin_fields->fname_len;
	}
}
