/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_permissions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 05:36:07 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 12:39:32 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_long_format.h"

#include <sys/xattr.h>

#include <sys/acl.h>

static char	identify_filetype(const mode_t file_type)
{
	if ((S_IFDIR == file_type) > 0)
		return ('d');
	else if ((S_IFREG == file_type) > 0)
		return ('-');
	else if ((S_IFLNK == file_type) > 0)
		return ('l');
	else if ((S_IFIFO == file_type) > 0)
		return ('p');
	else if ((S_IFBLK == file_type) > 0)
		return ('b');
	else if ((S_IFSOCK == file_type) > 0)
		return ('s');
	else if ((S_IFWHT == file_type) > 0)
		return ('w');
	else
		return ('U');
}

/*
** return U should by all means be totally unreachable
*/

static void	find_xattr(char *const restrict abuf,\
				const char *const restrict file_name)
{
	ssize_t	status;
	acl_t	acl;

	status = listxattr(file_name, NULL, 0, XATTR_NOFOLLOW);
	if (status <= 0)
	{
		acl = acl_get_file(file_name, ACL_TYPE_EXTENDED);
		if (acl != NULL)
		{
			*abuf = '+';
			acl_free(acl);
		}
		else
		{
			*abuf = ' ';
		}
	}
	else if (status > 0)
	{
		*abuf = '@';
	}
}

void		ft_generate_permissions(char *const restrict aholder,\
				size_t *const restrict aoffset,\
				const t_finfo *const restrict cur_file)
{
	static char		perm_table[4096][10] = {[0][0] = 'N'};
	char			buf[PERMLST_LEN];
	const mode_t	file_mode = cur_file->stat.st_mode;

	if (perm_table[0][0] == 'N')
	{
		init_permissions_table(perm_table);
	}
	buf[0] = identify_filetype(file_mode & S_IFMT);
	ft_memcpy(buf + 1, perm_table[file_mode & ALLPERMS], 9);
	find_xattr(buf + 10, cur_file->s_name);
	buf[11] = ' ';
	ft_memcpy(aholder, buf, PERMLST_LEN);
	*aoffset += PERMLST_LEN;
}
