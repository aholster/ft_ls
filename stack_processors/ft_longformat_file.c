/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_longformat_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:23:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/02 15:02:48 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"
#include <limits.h>

int			ft_long_format_file(const t_finfo *const restrict cur_file,\
				t_list **const restrict aout_stack,\
				const t_longests *const restrict amin_fields,\
				const t_flags *const restrict aflags)
{
	char	holder[PATH_MAX + MAX_INODE_LEN + MAX_TIMELEN + 1001];
	size_t	offset;
	int		status;

	offset = 0;
	if (generate_time(holder, &offset, &(cur_file->stat), aflags) == -1)
	{
		return (-1);
	}
	status = snprintf(holder + offset, sizeof(holder) - offset,\
				"%s", cur_file->s_name);
	if (status == -1)
	{
		return (-1);
	}
	else if (ft_lst_stack_push(aout_stack, holder, status + offset + 1) == -1)
	{
		return (-1);
	}
	(void)amin_fields;
	return (0);
}
