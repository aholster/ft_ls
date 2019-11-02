/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/11/02 08:03:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"
#include <limits.h>

static int	ft_inode_file(const t_finfo *const restrict cur_file,\
				t_list **const restrict aout_stack,\
				const t_longests *const restrict amin_fields)
{
	char	holder[PATH_MAX + MAX_INODE_LEN + 1];
	int		status;

	status = snprintf(holder, sizeof(holder), "%*llu %s",\
		amin_fields->inode, cur_file->stat.st_ino, cur_file->s_name);
	if (status == -1)
	{
		return (-1);
	}
	else if (ft_lst_stack_push(aout_stack, holder, status + 1) == -1)
	{
		return (-1);
	}
	return (0);
}

static int	ft_basic_file(const t_finfo *const restrict cur_file,\
				t_list **const restrict aout_stack)
{
	char	holder[PATH_MAX + 1];
	int		status;

	status = snprintf(holder, sizeof(holder), "%s", cur_file->s_name);
	if (status == -1)
	{
		return (-1);
	}
	else if (ft_lst_stack_push(aout_stack, holder, status + 1) == -1)
	{
		return (-1);
	}
	return (0);
}

int			ft_process_files_to_txt(\
				t_finfo *restrict *const restrict afinfo_stack,\
				t_list **const restrict aout_stack,\
				int *const restrict amax_reclen,\
				const t_flags *const restrict aflags)
{
	t_finfo *restrict		cur_file;
	int						ret_status;
	t_longests				min_fields;

	ft_find_longest_fields(*afinfo_stack, &min_fields, aflags);
	*amax_reclen = min_fields.fname;//change this to be full entry len
	cur_file = finfo_stack_pop(afinfo_stack);
	while (cur_file != NULL)
	{
		if (((*aflags) & flg_l) > 0)
		{
			ret_status = ft_long_format_file(cur_file, aout_stack, &min_fields, aflags);
		}
		else if (((*aflags) & flg_i) > 0)
		{
			ret_status = ft_inode_file(cur_file, aout_stack, &min_fields);
		}
		else
		{
			ret_status = ft_basic_file(cur_file, aout_stack);
		}
		finfo_lstdelone(&cur_file);
		if (ret_status == -1)
		{
			return (-1);
		}
		cur_file = finfo_stack_pop(afinfo_stack);
	}
	return (1);
}
