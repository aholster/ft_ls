/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_permissions.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/05 05:36:07 by aholster       #+#    #+#                */
/*   Updated: 2019/12/10 06:39:38 by aholster      ########   odam.nl         */
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
		*abuf = '?';
}

/*
** return U should by all means be totally unreachable
*/

static void	find_xattr(char *const restrict abuf,\
				const char *const restrict file_path)
{
	ssize_t	status;
	acl_t	acl;

	status = listxattr(file_path, NULL, 0, XATTR_NOFOLLOW);
	if (status <= 0)
	{
		acl = acl_get_file(file_path, ACL_TYPE_EXTENDED);
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

static char		g_perm_table[4096][10] = {
	[0][0] = 'N',
};

int			ft_generate_permissions(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char			buf[PERM_LEN];
	const mode_t	file_mode = afile->stat.st_mode;

	if (g_perm_table[0][0] == 'N')
	{
		ft_init_permissions_table(g_perm_table);
	}
	identify_filetype(file_mode & S_IFMT, buf);
	ft_memcpy(buf + 1, g_perm_table[file_mode & ALLPERMS], 9);
	find_xattr(buf + 10, afile->s_path);
	buf[11] = '\0';
	if (ft_fvec_enter_comp(afile, f_perm, buf, PERM_LEN) == -1)
	{
		return (-1);
	}
	else
	{
		(void)aflags;
		(void)acaps;
		return (1);
	}
}
