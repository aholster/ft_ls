/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_name.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:10:29 by aholster       #+#    #+#                */
/*   Updated: 2019/11/25 16:22:44 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static int	utfbasic(const char *const restrict str)
{
	if ((*str & 0xe0) == 0xc0 && (str[1] & 0xc0) == 0x80)
	{
		return (1);
	}
	else if ((*str & 0xf0) == 0xe0 && (str[1] & 0xc0) == 0x80\
			&& (str[2] & 0xc0) == 0x80)
	{
		return (1);
	}
	else if ((*str & 0xf8) == 0xf0 && (str[1] & 0xc0) == 0x80\
			&& (str[2] & 0xc0) == 0x80 && (str[3] & 0xc0) == 0x80)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

static int	replace_nonprint(const t_finfo *const restrict afile,\
				size_t len,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char						buffer[MAX_NAMELEN];
	const char *const restrict	file_name = afile->s_name;
	size_t						index;
	size_t						buf_index;

	index = 0;
	buf_index = 0;
	while (index < len)
	{
		if (ft_isprint(file_name[index]) == 1)
		{
			buffer[buf_index] = file_name[index];
			buf_index++;
		}
		else if (utfbasic(file_name + index) == 1)
		{
			(void)index;
		}
		else
		{
			if ((aflags & flg_q) == flg_q)
			{
				buffer[buf_index] = '?';
				buf_index++;
			}
			else
			{
				snprintf(buffer + buf_index, sizeof(buffer) - buf_index,\
					"\\%.3hho", file_name[index]);
				buf_index += 4;
			}
		}
		index++;
	}
	buffer[buf_index] = '\0';
	if (ft_fvec_enter_comp(afile, f_name,\
			buffer, buf_index + 1) == -1)
	{
		return (-1);
	}
	if ((int)len > acaps->fname_len)
	{
		acaps->fname_len = len;
	}
	return (1);
}

int			ft_generate_name(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	const size_t	len = ft_strlen(afile->s_name);

	if ((aflags & flg_w) == flg_w)
	{
		if (ft_fvec_enter_comp(afile, f_name,\
				afile->s_name, len + 1) == -1)
		{
			return (-1);
		}
		else if ((int)len > acaps->fname_len)
		{
			acaps->fname_len = len;
		}
		return (1);
	}
	else
	{
		return (replace_nonprint(afile, len, acaps, aflags) == -1);
	}
}
