/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_name.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:10:29 by aholster       #+#    #+#                */
/*   Updated: 2019/11/27 13:46:32 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static void	replace_with_question(char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isprint(str[index]) == 0)
		{
			str[index] = '?';
		}
		index++;
	}
}

static int	write_name(const t_finfo *const restrict afile,\
				char name_buf[MAX_NAMELEN],\
				size_t *const restrict atext_len,\
				const t_flags aflags)
{
	const char	*ascii_escape_table[255] = {
		['\0'] = "\\0",
		['\r'] = "\\r",
		['\n'] = "\\n",
		['\v'] = "\\v",
		['\a'] = "\\a",
		['\b'] = "\\b",
		['\f'] = "\\f",
		['\t'] = "\\t",
		['\"'] = "\\\"",
		['\\'] = "\\\\",
	};
	size_t	index;
	size_t	tardex;

	index = 0;
	tardex = 0;
	if ((aflags & (flg_w | flg_q)) > 0)
	{
		ft_memcpy(name_buf, afile->s_name, afile->s_namelen);
		*atext_len += afile->s_namelen - 1;
	}
	if ((aflags & flg_q) > 0)
	{
		replace_with_question(name_buf);
	}
	else if ((aflags & (flg_B | flg_b)) > 0)
	{
		while (index + 1 < afile->s_namelen)
		{
			if (ft_isprint(afile->s_name[index]) == 1 && afile->s_name[index] != '\\')
			{
				name_buf[tardex] = afile->s_name[index];
				tardex += 1;
			}
			else if ((aflags & flg_b) == flg_b && ascii_escape_table[(unsigned char)afile->s_name[index]] != NULL)
			{
				ft_memcpy(name_buf + tardex,\
					ascii_escape_table[(unsigned char)afile->s_name[index]], 2);
				tardex += 2;
			}
			else
			{
				sprintf(name_buf + tardex, "\\%.3hho", afile->s_name[index]);
				tardex += 4;
			}
			index++;
		}
		*atext_len = tardex;
	}
	return (1);
}

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
				size_t *const restrict atext_len)
{
	ssize_t	ret;

	ret = readlink(afile->s_name, name_buf + *atext_len, MAX_NAMELEN - *atext_len);
	if (ret != -1)
	{
		*atext_len += ret;
	}
	else
	{
		afile->fvect->err_id = errno;
		dprintf(2, "ft_ls: %s:", afile->s_name);
		perror(NULL);
	}
}

int			ft_generate_name(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char			name[MAX_NAMELEN];
	size_t			text_len;

	text_len = 0;
	if (write_name(afile, name, &text_len, aflags) == -1)
	{
		return (-1);
	}
	suffix_name(afile, name, &text_len, aflags);
	name[text_len] = '\0';
	if ((aflags & flg_l) == flg_l && S_ISLNK(afile->stat.st_mode))
	{
		suffix_destination(afile, name, &text_len);
	}
	if (ft_fvec_enter_comp(afile, f_name, name, text_len + 1) == -1)
	{
		return (-1);
	}
	else if ((int)text_len > acaps->fname_len)
	{
		acaps->fname_len = text_len;
	}
	return (1);
}
