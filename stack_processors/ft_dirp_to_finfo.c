/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dirp_to_finfo.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/02 04:52:42 by aholster       #+#    #+#                */
/*   Updated: 2019/12/07 05:17:22 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/dir.h>

#include "../incl/ft_stack_sorters.h"

static int	rec_stat(const char *const restrict full_path,\
				struct stat *const restrict astat,\
				const t_flags aflags)
{
	if ((aflags & flg_L) == flg_L)
	{
		return (stat(full_path, astat));
	}
	else
	{
		return (lstat(full_path, astat));
	}
}

static int	process_dirp(const struct dirent *const restrict rec,\
				const char *const restrict path,\
				t_finfo_queue *const restrict aqueue,\
				const t_flags aflags)
{
	char			full_path[PATH_MAX + 1];
	struct stat		f_stat;

	if ((aflags & flg_a) == flg_a || rec->d_name[0] != '.')
	{
		ft_snprintf(full_path, sizeof(full_path), "%s/%s", path, rec->d_name);
		if (rec_stat(full_path, &f_stat, aflags) == -1)
		{
			ft_dprintf(2, "ft_ls: %s: ", rec->d_name);
			perror(NULL);
		}
		else
		{
			if (finfo_queue_push(aqueue, path, rec->d_name, &f_stat) == -1)
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
