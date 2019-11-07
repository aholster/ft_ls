/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_permissions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 05:36:07 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 07:54:12 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"

#include <sys/xattr.h>

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

static void	permissions_tbl(char *const restrict abuf,\
				const mode_t perm_modes)
{
	const char lookup_tbl[8][4] = {
		[0] = "---",
		[1] = "--x",
		[2] = "-w-",
		[3] = "-wx",
		[4] = "r--",
		[5] = "r-x",
		[6] = "rw-",
		[7] = "rwx",
	};

	ft_memcpy(abuf + 6, lookup_tbl[(perm_modes & S_IRWXO)], 3);
	if ((S_ISVTX & perm_modes) > 0)
	{
		if ((S_IXOTH & perm_modes) > 0)
			abuf[8] = 't';
		else
			abuf[8] = 'T';
	}
	ft_memcpy(abuf + 3, lookup_tbl[(perm_modes & S_IRWXG) >> 3], 3);
	if ((S_ISGID & perm_modes) > 0)
	{
		if ((S_IXGRP & perm_modes) > 0)
			abuf[5] = 's';
		else
			abuf[5] = 'S';
	}
	ft_memcpy(abuf, lookup_tbl[(perm_modes & S_IRWXU) >> 6], 3);
	if ((S_ISUID & perm_modes) > 0)
	{
		if ((S_IXUSR & perm_modes) > 0)
			abuf[2] = 's';
		else
			abuf[2] = 'S';
	}
}

static int	find_xattr(char *const restrict abuf,\
				const char *const restrict file_name)
{
	ssize_t	status;

	status = listxattr(file_name, NULL, 0, XATTR_NOFOLLOW);
	if (status == -1)
	{
		return (-1);
	}
	else if (status == 0)
	{
		*abuf = ' ';
	}
	else
	{
		*abuf = '@';
	}
	return (0);
}

int			ft_generate_permissions(char *const restrict aholder,\
				size_t *const restrict aoffset,\
				const t_finfo *const restrict cur_file)
{
	char			buf[PERMLST_LEN];
	const mode_t	file_mode = cur_file->stat.st_mode;

	buf[0] = identify_filetype(file_mode & S_IFMT);
	permissions_tbl(buf + 1, file_mode);
	if (find_xattr(buf + 10, cur_file->s_name) == -1)
	{
		return (-1);
	}
	buf[11] = ' ';
	ft_memcpy(aholder, buf, PERMLST_LEN);
	*aoffset += PERMLST_LEN;
	return (0);
}
