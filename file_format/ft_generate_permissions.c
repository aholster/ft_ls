/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_permissions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 05:36:07 by aholster       #+#    #+#                */
/*   Updated: 2019/11/11 22:02:49 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/xattr.h>

#include <sys/acl.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static void	identify_filetype(const mode_t file_type, char *const restrict abuf)
{
	if (S_ISBLK(file_type) == 1)
		*abuf = 'b';
	else if (S_ISCHR(file_type) == 1)
		*abuf = 'c';
	else if (S_ISDIR(file_type) == 1)
		*abuf = 'd';
	else if (S_ISLNK(file_type) == 1)
		*abuf = 'l';
	else if (S_ISSOCK(file_type) == 1)
		*abuf = 's';
	else if (S_ISFIFO(file_type) == 1)
		*abuf = 'p';
	else if (S_ISREG(file_type) == 1)
		*abuf = '-';
	else if (S_ISWHT(file_type) == 1)
		*abuf = 'w';
	else
		*abuf = 'U';
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
	identify_filetype(file_mode & S_IFMT, buf);
	ft_memcpy(buf + 1, perm_table[file_mode & ALLPERMS], 9);
	find_xattr(buf + 10, cur_file->s_name);
	buf[11] = ' ';
	ft_memcpy(aholder, buf, PERMLST_LEN);
	*aoffset += PERMLST_LEN;
}
