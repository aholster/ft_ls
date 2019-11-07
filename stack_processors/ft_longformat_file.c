/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_longformat_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:23:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 07:28:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"
#include <limits.h>

int			ft_long_format_file(const t_finfo *const restrict cur_file,\
				t_list **const restrict aout_stack,\
				const t_longests *const restrict amin_fields,\
				const t_flags *const restrict aflags)
{
	char	holder[PATH_MAX + MAX_INODE_LEN + MAX_TIMELEN + PERMLST_LEN + 1001];
	size_t	oset;
	int		status;

	oset = 0;
	if (ft_generate_permissions(holder + oset, &oset, cur_file) == -1)
	{
		return (-1);
	}
	if (ft_generate_time(holder + oset, &oset, &(cur_file->stat), aflags) == -1)
	{
		return (-1);
	}
	status = snprintf(holder + oset, sizeof(holder) - oset,\
				"%s", cur_file->s_name);
	if (status == -1)
	{
		return (-1);
	}
	else if (ft_lst_stack_push(aout_stack, holder, status + oset + 1) == -1)
	{
		return (-1);
	}
	(void)amin_fields;
	return (0);
}
