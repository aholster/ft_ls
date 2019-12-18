/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_dir_stack.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:34:08 by aholster       #+#    #+#                */
/*   Updated: 2019/12/18 15:08:17 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf/ft_printf.h"
#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>
#include <sys/dir.h>

#include "../incl/ft_stack_processors.h"

static void	print_status(const t_finfo *restrict iter)
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
		ft_printf("total %llu\n", total_blocks);
	}
}

static int	trim_down_to_dirs(t_finfo_queue *const restrict record_queue,\
				const t_flags aflags)
{
	t_finfo		*trail;
	t_finfo		**manipulator;
	char const	*name;

	manipulator = &(record_queue->head);
	while (*manipulator != NULL)
	{
		name = (*manipulator)->s_name;
		if (S_ISDIR((*manipulator)->stat.st_mode) == 1 &&\
				ft_strequ(name, ".") == 0 && ft_strequ(name, "..") == 0)
			manipulator = &((*manipulator)->next);
		else
		{
			trail = *manipulator;
			*manipulator = (*manipulator)->next;
			finfo_lstdelone(&trail);
		}
		record_queue->tail = *manipulator;
	}
	if (record_queue->head != NULL)
	{
		write(1, "\n", 1);
	}
	return (ft_process_dir_stack(record_queue, 0, aflags));
}

static int	record_handler(DIR *const restrict dirp,\
				const char *const restrict path,\
				const t_flags aflags)
{
	t_finfo_queue	record_queue;
	int				status;

	ft_bzero(&record_queue, sizeof(t_finfo_queue));
	if (ft_dirp_to_finfo(dirp, path, &record_queue, aflags) == -1)
	{
		return (-1);
	}
	if (record_queue.head != NULL)
	{
		if ((aflags & flg_l) == flg_l)
		{
			print_status(record_queue.head);
		}
		status = ft_process_ndir_stack(record_queue.head, aflags);
		if (status != -1 && (aflags & flg_R) == flg_R)
		{
			if (trim_down_to_dirs(&record_queue, aflags) == -1)
				status = -1;
		}
		finfo_del(&record_queue);
		return (status);
	}
	return (1);
}

static int	access_directory(const char *const restrict name,\
				const char *const restrict path,\
				const t_flags aflags)
{
	DIR		*current_dir;
	int		ret;

	current_dir = opendir(path);
	if (current_dir == NULL)
	{
		ft_dprintf(2, "ft_ls: %s: ", name);
		perror(NULL);
		return (1);
	}
	else
	{
		ret = record_handler(current_dir, path, aflags);
		closedir(current_dir);
		if (ret == -1)
		{
			return (-1);
		}
		return (1);
	}
}

int			ft_process_dir_stack(t_finfo_queue *const restrict dir_queue,\
				const int is_singledir,\
				const t_flags aflags)
{
	const t_finfo	*dir_lst;

	dir_lst = dir_queue->head;
	while (dir_lst != NULL)
	{
		if (is_singledir == 0)
		{
			ft_printf("%s:\n", dir_lst->s_path);
		}
		if (access_directory(dir_lst->s_name, dir_lst->s_path, aflags) == -1)
		{
			finfo_del(dir_queue);
			return (-1);
		}
		dir_lst = dir_lst->next;
		if (dir_lst != NULL)
		{
			write(1, "\n", 1);
		}
	}
	finfo_del(dir_queue);
	return (1);
}
