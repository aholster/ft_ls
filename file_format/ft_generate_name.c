/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_name.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:10:29 by aholster       #+#    #+#                */
/*   Updated: 2019/12/07 04:38:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../ft_printf/ft_printf.h"
#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static void	suffix_name(const t_finfo *const restrict afile,\
				char name_buf[MAX_NAMELEN],\
				size_t *const restrict atext_len,\
				const t_flags aflags)
{
	if ((aflags & flg_p) == flg_p && S_ISDIR(afile->stat.st_mode))
	{
		name_buf[*atext_len] = '/';
		*atext_len += 1;
	}
	else if ((aflags & flg_F) == flg_F)
	{
		*atext_len += 1;
		if (S_ISLNK(afile->stat.st_mode))
			name_buf[*atext_len] = '@';
		else if (S_ISFIFO(afile->stat.st_mode))
			name_buf[*atext_len] = '|';
		else if (S_ISSOCK(afile->stat.st_mode))
			name_buf[*atext_len] = '=';
		else if (S_ISWHT(afile->stat.st_mode))
			name_buf[*atext_len] = '%';
		else if ((afile->stat.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) != 0)
			name_buf[*atext_len] = '*';
		else
		{
			*atext_len -= 1;
		}
	}
}

static void	suffix_destination(const t_finfo *const restrict afile,\
				char name_buf[MAX_NAMELEN],\
				size_t *const restrict alen,\
				const t_flags aflags)
{
	ssize_t	ret;
	char	dest[PATH_MAX + 5];

	ft_strcpy(dest, " -> ");
	ret = readlink(afile->s_path, dest + 4, sizeof(dest) - 4);
	if (ret == -1)
	{
		ft_dprintf(2, "ft_ls: %s: ", afile->s_name);
		perror(NULL);
	}
	else
	{
		dest[ret + 4] = '\0';
		*alen += ft_format_name(dest, ret + 5, name_buf + *alen, aflags);
	}
}

int			ft_generate_name(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char			name_buf[MAX_NAMELEN];
	size_t			len;

	len = ft_format_name(afile->s_name, afile->s_namelen, name_buf, aflags);
	if ((aflags & (flg_p | flg_F)) > 0)
	{
		suffix_name(afile, name_buf, &len, aflags);
	}
	if ((aflags & flg_l) == flg_l && S_ISLNK(afile->stat.st_mode) == 1)
	{
		suffix_destination(afile, name_buf, &len, aflags);
	}
	name_buf[len] = '\0';
	if (ft_fvec_enter_comp(afile, f_name, name_buf, len + 1) == -1)
	{
		return (-1);
	}
	else if ((int)len > acaps->fname_len)
	{
		acaps->fname_len = len;
	}
	return (1);
}
