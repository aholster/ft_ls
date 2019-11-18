/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_generate_name.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/13 08:10:29 by aholster       #+#    #+#                */
/*   Updated: 2019/11/18 22:23:19 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

int			ft_generate_name(const t_finfo *const restrict afile,\
				t_compcaps *const restrict acaps,\
				const t_flags aflags)
{
	const size_t	len = ft_strlen(afile->s_name);

	if (ft_fvec_enter_comp(afile->fvect, f_name,\
			afile->s_name, len + 1) == -1)
	{
		return (-1);
	}
	else if ((int)len > acaps->fname_len)
	{
		acaps->fname_len = len;
	}
	(void)aflags;
	return (1);
}
