/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 13:15:12 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"
#include <limits.h>

static int	ft_long_format(t_finfo *restrict afile,\
				t_list **aout_stack,\
				t_compcaps *const restrict acaps,\
				int *const restrict amax_len)
{
	char *restrict		s;
	size_t *restrict	i;
	char				*output_line;
	int					len;

	while (afile != NULL)
	{
		s = afile->fvect->svec;
		i = afile->fvect->indices;
		len = asprintf(&output_line, "%s%*s %-*s %-*s %*s %s %s",\
					s + i[f_perm],\
					acaps->hlink_len, s + i[f_nlnk],\
					acaps->uname_len, s + i[f_uid],\
					acaps->gname_len, s + i[f_gid],\
					acaps->fsize_len, s + i[f_size],\
					s + i[f_date], s + i[f_name]);
		if (len < 0)
		{
			return (-1);
		}
		else if (len > *amax_len)
		{
			*amax_len = len;
		}
		len = ft_lst_stack_push(aout_stack, output_line, (size_t)len + 1);
		free(output_line);
		if (len == -1)
		{
			return (-1);
		}
		afile = afile->next;
	}
	return (1);
}

static int	ft_basic_format(t_finfo *restrict afile,\
				t_list **aout_stack,\
				int *const restrict amax_len)
{
	char	*output_line;
	int		len;

	while (afile != NULL)
	{
		len = asprintf(&output_line, "%s",\
				afile->fvect->svec + afile->fvect->indices[f_name]);
		if (len < 0)
		{
			return (-1);
		}
		else if (len > *amax_len)
		{
			*amax_len = len;
		}
		len = ft_lst_stack_push(aout_stack, output_line, (size_t)len + 1);
		free(output_line);
		if (len == -1)
		{
			return (-1);
		}
		afile = afile->next;
	}
	return (1);
}

static int	ft_inode_format(t_finfo *restrict afile,\
				t_list **aout_stack,\
				t_compcaps *const restrict acaps,\
				int *const restrict amax_len)
{
	(void)acaps;
	return (ft_basic_format(afile, aout_stack, amax_len));
}

int			ft_process_files_to_txt(\
				t_finfo *restrict *const restrict afinfo_stack,\
				t_list **const restrict aout_stack,\
				int *const restrict amax_len,\
				const t_flags aflags)
{
	int			ret;
	t_compcaps	caps;

	ft_bzero(&caps, sizeof(t_compcaps));
	if (ft_create_components(*afinfo_stack, &caps, aflags) == -1)
	{
		return (-1);
	}
	else
	{
		if ((aflags & flg_l) > 0)
		{
			ret = ft_long_format(*afinfo_stack, aout_stack, &caps, amax_len);
		}
		else if ((aflags & flg_i) > 0)
		{
			ret = ft_inode_format(*afinfo_stack, aout_stack, &caps, amax_len);
		}
		else
		{
			ret = ft_basic_format(*afinfo_stack, aout_stack, amax_len);
		}
		return (ret);
	}
}
