/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_dir_stack.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:34:08 by aholster       #+#    #+#                */
/*   Updated: 2019/12/01 01:29:26 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/dir.h>

#include "../incl/ft_stack_processors.h"
#include "../incl/ft_stack_sorters.h"

#include <limits.h>

static int	ft_dirp_to_finfostack(DIR *const restrict dirp,\
				const char *const restrict path,\
				t_finfo *restrict *const restrict afinfo_stack,\
				t_finfo **const restrict adir_stack,\
				const t_flags aflags)
{
	char			full_path[PATH_MAX + 1];
	struct dirent	*record;
	struct stat		f_stat;
	int				status;

	record = readdir(dirp);
	while (record != NULL)
	{
		if ((aflags & flg_a) == flg_a || record->d_name[0] != '.')
		{
			snprintf(full_path, sizeof(full_path), "%s/%s", path, record->d_name);
			if ((aflags & flg_L) > 0)
			{
				status = stat(full_path, &f_stat);
			}
			else
			{
				status = lstat(full_path, &f_stat);
			}
			if (status == 0)
			{
				if (finfo_stack_push(afinfo_stack, record->d_name, &f_stat) == -1)
				{
					return (-1);
				}
				if ((aflags & flg_R) == flg_R && S_ISDIR(f_stat.st_mode) == 1)
				{
					if (finfo_stack_push(adir_stack, record->d_name, &f_stat) == -1)
					{
						return (-1);
					}
				}
			}
		}
		record = readdir(dirp);
	}
	return (1);
}

static int	ft_dirp_process(DIR *const restrict dirp,\
				const char *const restrict path,\
				const t_flags aflags)
{
	t_finfo	*dir_stack = NULL;

	t_finfo	*dir_stats;
	t_list	*product;
	int		max_len;
	int		status;

	dir_stats = NULL;
	if (ft_dirp_to_finfostack(dirp, path, &dir_stats, &dir_stack, aflags) == -1)
	{
		finfo_lstdel(&dir_stack);

		finfo_lstdel(&dir_stats);
		return (-1);
	}
	if ((aflags & flg_f) == 0)
	{
		ft_sort_finfo_stack(&dir_stats, aflags);
	}


	unsigned long long	total_size;
	t_finfo				*iter;
	total_size = 0;
	iter = dir_stats;
	while (iter != NULL)
	{
		total_size += iter->stat.st_blocks;
		iter = iter->next;
	}
	printf("total: %llu\n", total_size);


	status = ft_process_files_to_txt(&dir_stats, &product, &max_len, aflags);
	finfo_lstdel(&dir_stats);
	if (status == -1)
	{
		finfo_lstdel(&dir_stack);

		ft_lstdel(&product, &ft_del);
		return (-1);
	}
	status = ft_printer(product, max_len, aflags);
	ft_lstdel(&product, &ft_del);

	t_fstack temp;
	ft_bzero(&temp, sizeof(t_fstack));
	temp.dir_stack = dir_stack;
	ft_process_dir_stack(&temp, 0, aflags);

	finfo_lstdel(&dir_stack);
	return (status);
}

static int	non_recurse_trav(const t_finfo *restrict dir_stack,\
				const int is_singledir,\
				const t_flags aflags)
{
	DIR		*current_dir;
	int		ret;

	while (dir_stack != NULL)
	{
		if (is_singledir == 0)
		{
			printf("%s:\n", dir_stack->s_name);
		}
		current_dir = opendir(dir_stack->s_name);
		if (current_dir == NULL)
		{
			dprintf(2, "ft_ls: %s: %s\n", dir_stack->s_name, strerror(errno));
		}
		else
		{
			ret = ft_dirp_process(current_dir, dir_stack->s_name, aflags);
			closedir(current_dir);
			if (ret == -1)
			{
				return (-1);
			}
		}
		dir_stack = dir_stack->next;
	}
	return (1);
}

void		ft_process_dir_stack(t_fstack *const restrict afstack,\
				const int is_singledir,\
				const t_flags aflags)
{
	int	status;

	if ((aflags & flg_R) == flg_R)
	{
		// status = recursive_trav();
		status = -1;
	}
	else
	{
		status = non_recurse_trav(afstack->dir_stack, is_singledir, aflags);
		finfo_lstdel(&(afstack->dir_stack));
	}
	if (status == -1)
	{
		ft_error_cleanup(afstack);
	}
}
