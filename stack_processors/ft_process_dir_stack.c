/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_dir_stack.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:34:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 10:12:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/dir.h>

#include "../incl/ft_stack_processors.h"
#include "../incl/ft_stack_sorters.h"

#include <limits.h>

static int	ft_dirp_to_finfostack(DIR *const restrict dirp,\
				const char *const restrict path,\
				t_finfo *restrict *const restrict afinfo_stack,\
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
	t_finfo			*dir_stats;
	t_list			*product;
	t_print_widths	widths;

	dir_stats = NULL;
	ft_bzero(&widths, sizeof(t_print_widths));
	if (ft_dirp_to_finfostack(dirp, path, &dir_stats, aflags) == -1)
	{
		finfo_lstdel(&dir_stats);
		return (-1);
	}
	if ((aflags & flg_f) != flg_f)
	{
		ft_sort_finfo_stack(&dir_stats, aflags);
	}
	if (ft_process_files_to_txt(&dir_stats, &product, &widths, aflags) == -1)
	{
		ft_lstdel(&product, &ft_del);
		finfo_lstdel(&dir_stats);
		return (-1);
	}
	finfo_lstdel(&dir_stats);
	if (ft_printer(product, &widths, aflags) == -1)
	{
		ft_lstdel(&product, &ft_del);
		return (-1);
	}
	ft_lstdel(&product, &ft_del);
	return (1);
}

void		ft_process_dir_stack(t_fstack *const restrict afstack,\
				const t_flags aflags)
{
	DIR					*current_dir;
	t_finfo *restrict	iterator;

	iterator = afstack->dir_stack;
	while (iterator != NULL)
	{
		current_dir = opendir(iterator->s_name);
		if (current_dir == NULL)
		{
			perror("ft_ls");
		}
		else
		{
			if (ft_dirp_process(current_dir, iterator->s_name, aflags) == -1)
			{
				ft_error_cleanup(afstack);
			}
			closedir(current_dir);
		}
		iterator = iterator->next;
	}
}
