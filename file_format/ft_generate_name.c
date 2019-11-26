/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_name.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:10:29 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 11:26:13 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

/*
** ex fx cx dx bx eg ed ab ag ac ad
*/

static void	insert_color(const t_finfo *const restrict afile,\
				char *const restrict name_buf,\
				size_t *const restrict aindex)
{
	const mode_t	file_mode = afile->stat.st_mode;

	*aindex += 7;
	if (S_ISDIR(file_mode) == 1)
	{
		ft_memcpy(name_buf, "\033[34;0m", 7);
	}
	else
	{
		ft_memcpy(name_buf, "\033[0;00m", 7);
	}
}

int			ft_generate_name(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	char	name[MAX_NAMELEN];
	size_t	text_len;
	size_t	color_len;

	color_len = 0;
	if ((aflags & flg_G) == flg_G)
	{
		insert_color(afile, name, &color_len);
	}
	ft_memcpy(name + color_len, afile->s_name, afile->s_name_len);
	text_len = afile->s_name_len;
	if ((aflags & flg_G) == flg_G)
	{
		ft_memcpy(name + text_len + color_len, "\033[0m", 4);
		color_len += 4;
	}
	name[text_len + color_len] = '\0';
	if (ft_fvec_enter_comp(afile, f_name, name, text_len + color_len + 1) == -1)
	{
		return (-1);
	}
	if ((int)text_len > acaps->fname_len)
	{
		acaps->fname_len = (int)text_len;
	}
	afile->fvect->color_len = color_len;
	return (1);
}
