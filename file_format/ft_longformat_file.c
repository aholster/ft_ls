/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_longformat_file.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:23:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/11 22:52:45 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include <limits.h>

#include "../libft/libft.h"

static void	ft_hardlink_count(char *const restrict aholder,\
				size_t *const restrict aoffset,\
				const struct stat *const restrict astat,\
				const t_longests *const restrict amin_fields)
{
	const int	hlink_width = amin_fields->hlink_len;

	sprintf(aholder, "%*hu ", hlink_width, astat->st_nlink);
	*aoffset += hlink_width + 1;
}

int			ft_long_format_file(const t_finfo *const restrict cur_file,\
				t_list **const restrict aout_stack,\
				const t_longests *const restrict amin_fields,\
				const t_flags *const restrict aflags)
{
	char	holder[PATH_MAX + MAX_INODE_LEN + MAX_HLINK_LEN + MAX_DATELEN + PERMLST_LEN + 1001];
	size_t	offset;
	int		status;
	const struct stat *const restrict astat = &(cur_file->stat);

	offset = 0;
	ft_generate_permissions(holder + offset, &offset, cur_file);
	ft_hardlink_count(holder + offset, &offset, astat, amin_fields);
	if (ft_generate_gid_uid(holder + offset, &offset, astat, amin_fields) == -1)
	{
		return (-1);
	}
	offset += sprintf(holder + offset, "%8llu ", astat->st_size);
	if (ft_generate_time(holder + offset, &offset, astat, aflags) == -1)
	{
		return (-1);
	}
	status = sprintf(holder + offset, "%s", cur_file->s_name);
	if (status == -1)
	{
		return (-1);
	}
	if (ft_lst_stack_push(aout_stack, holder, status + offset + 1) == -1)
	{
		return (-1);
	}
	return (0);
}
