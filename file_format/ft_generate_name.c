/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_name.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:10:29 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 16:30:29 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
		['\\'] = "\\\\",
		['\"'] = "\\\"",
	};
	size_t	index;
	size_t	tardex;

	index = 0;
	tardex = 0;
	if ((aflags & (flg_w | flg_q)) > 0)
	{
		ft_memcpy(name_buf, afile->s_name, afile->s_namelen + 1);
		*atext_len += afile->s_namelen;
	}
	if ((aflags & flg_q) > 0)
	{
		replace_with_question(name_buf);
	}
	else if ((aflags & (flg_B | flg_b)) > 0)
	{
		while (index + 1 < afile->s_namelen)
		{
			if (ft_isprint(afile->s_name[index]) == 1)
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
				snprintf(name_buf + tardex, MAX_NAMELEN - tardex,\
					"\\%.3hho", afile->s_name[index]);
				tardex += 4;
			}
			index++;
		}
		name_buf[tardex] = '\0';
		*atext_len = tardex;
	}
	return (1);
}

int			ft_generate_name(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char			name[MAX_NAMELEN];
	size_t			text_len;

	text_len = 0;
	// ft_bzero(name, sizeof(name));
	if (write_name(afile, name, &text_len, aflags) == -1)
	{
		return (-1);
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
