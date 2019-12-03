/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_dir_stack.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:34:08 by aholster       #+#    #+#                */
/*   Updated: 2019/12/03 13:13:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/dir.h>

#include "../incl/ft_stack_processors.h"

static int	print_status(const t_finfo *restrict iter)
{
	unsigned long long	total_blocks;

	if (iter != NULL)
	{
		total_blocks = 0;
		while (iter != NULL)
		{
			total_blocks += iter->stat.st_blocks;
			iter = iter->next;
		}
		if (printf("total %llu\n", total_blocks) == -1)
		{
			return (-1);
		}
	}
	return (1);
}

static int	create_dir_lst(const t_finfo *restrict file_lst,\
				const char *const restrict path,\
				t_finfo_queue *const restrict adir_queue)
{
	char	full_path[PATH_MAX + 1];

	while (file_lst != NULL)
	{
		if (S_ISDIR(file_lst->stat.st_mode) == 1)
		{
			snprintf(full_path, sizeof(full_path), "%s/%s",\
					path, file_lst->s_name);
			if (finfo_queue_push(adir_queue, full_path, &(file_lst->stat)) == -1)
			{
				return (-1);
			}
		}
		file_lst = file_lst->next;
	}
	return (1);
}

static int	recursive_trav(DIR *const restrict dirp,\
				const char *const restrict path,\
				const t_flags aflags)
{
	t_finfo_queue	file_queue;
	t_finfo_queue	dir_queue;
	int				status;

	ft_bzero(&file_queue, sizeof(t_finfo_queue));
	if (ft_dirp_to_finfo(dirp, path, &file_queue, aflags) == -1)
	{
		return (-1);
	}
	if (file_queue.head != NULL)
	{
		if ((aflags & flg_l) == flg_l)
		{
			print_status(file_queue.head);
		}
		ft_bzero(&dir_queue, sizeof(t_finfo_queue));
		if (create_dir_lst(file_queue.head, path, &dir_queue) == -1)
		{
			finfo_del(&dir_queue);
			return (-1);
		}
		status = ft_process_ndir_stack(&file_queue.head, aflags);
		finfo_del(&file_queue);
		if (status == -1)
		{
			finfo_del(&dir_queue);
			return (-1);
		}
		if (dir_queue.head != NULL)
		{
			write(1, "\n", 1);
			if (ft_process_dir_stack(&dir_queue, 0, aflags) == -1)
			{
				finfo_del(&dir_queue);
				return (-1);
			}
			finfo_del(&dir_queue);
		}
	}
	return (1);
}

static int	non_recursive_trav(DIR *const restrict dirp,\
				const char *const restrict path,\
				const t_flags aflags)
{
	t_finfo_queue	file_queue;
	int				status;

	ft_bzero(&file_queue, sizeof(t_finfo_queue));
	if (ft_dirp_to_finfo(dirp, path, &file_queue, aflags) == -1)
	{
		return (-1);
	}
	if (file_queue.head != NULL)
	{
		if ((aflags & flg_l) == flg_l)
		{
			print_status(file_queue.head);
		}
		status = ft_process_ndir_stack(&file_queue.head, aflags);
		finfo_del(&file_queue);
		if (status == -1)
		{
			return (-1);
		}
	}
	return (1);
}

static int	iter_dirfinfo(const t_finfo *restrict dir_lst,\
				const int is_singledir,\
				const t_flags aflags)
{
	DIR		*current_dir;
	int		ret;

	while (dir_lst != NULL)
	{
		if (is_singledir == 0)
		{
			printf("%s:\n", dir_lst->s_name);
		}
		current_dir = opendir(dir_lst->s_name);
		if (current_dir == NULL)
		{
			dprintf(2, "ft_ls: %s: %s\n", dir_lst->s_name, strerror(errno));
		}
		else
		{
			if ((aflags & flg_R) == flg_R)
			{
				ret = recursive_trav(current_dir, dir_lst->s_name, aflags);
			}
			else
			{
				ret = non_recursive_trav(current_dir, dir_lst->s_name, aflags);
			}
			closedir(current_dir);
			if (ret == -1)
				return (-1);
		}
		dir_lst = dir_lst->next;
		if (dir_lst != NULL)
		{
			write(1, "\n", 1);
		}
	}
	return (1);
}

int		ft_process_dir_stack(t_finfo_queue *const restrict dir_queue,\
				const int is_singledir,\
				const t_flags aflags)
{
	int	status;

	status = iter_dirfinfo(dir_queue->head, is_singledir, aflags);
	finfo_del(dir_queue);
	if (status == -1)
	{
		return (-1);
	}
	return (1);
}
