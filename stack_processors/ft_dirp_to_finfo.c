/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dirp_to_finfo.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 04:52:42 by aholster       #+#    #+#                */
/*   Updated: 2019/12/03 13:02:51 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <sys/types.h>
#include <sys/dir.h>

#include "../incl/ft_stack_sorters.h"

int			process_dirp(const struct dirent *const restrict record,\
				const char *const restrict path,\
				t_finfo_queue *const restrict aqueue,\
				const t_flags aflags)
{
	char			full_path[PATH_MAX + 1];
	struct stat		f_stat;
	int				status;

	if ((aflags & flg_a) == flg_a || record->d_name[0] != '.')
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", path, record->d_name);
		if ((aflags & flg_L) == flg_L)
		{
			status = stat(full_path, &f_stat);
		}
		else
		{
			status = lstat(full_path, &f_stat);
		}
		if (status != -1)
		{
			if (finfo_queue_push(aqueue, record->d_name, &f_stat) == -1)
			{
				return (-1);
			}
		}
	}
	return (1);
}

int			ft_dirp_to_finfo(DIR *const restrict dirp,\
				const char *const restrict path,\
				t_finfo_queue *const restrict aqueue,\
				const t_flags aflags)
{
	struct dirent	*record;

	record = readdir(dirp);
	while (record != NULL)
	{
		if (process_dirp(record, path, aqueue, aflags) == -1)
		{
			finfo_del(aqueue);
			return (-1);
		}
		record = readdir(dirp);
	}
	if (aqueue->head != NULL)
	{
		if ((aflags & flg_f) == 0)
		{
			ft_sort_finfo_stack(aqueue, aflags);
		}
	}
	return (1);
}
