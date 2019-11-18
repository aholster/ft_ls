/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_dir_stack.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:34:08 by aholster       #+#    #+#                */
/*   Updated: 2019/11/18 21:14:18 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/dir.h>

#include "../incl/ft_stack_processors.h"

static int	ft_dirp_to_finfostack(DIR *const restrict dirp,\
				t_finfo *restrict *const restrict afinfo_stack,\
				const t_flags aflags)
{
	struct dirent	*record;
	struct stat		f_stat;
	int				status;

	record = readdir(dirp);
	while (record != NULL)
	{
		if ((aflags & flg_L) > 0)
		{
			status = stat(record->d_name, &f_stat);
		}
		else
		{
			status = lstat(record->d_name, &f_stat);
		}
		if (status == 0)
		{
			if (finfo_stack_push(afinfo_stack, record->d_name, &f_stat) == -1)
			{
				return (-1);
			}
		}
		record = readdir(dirp);
	}
	return (1);
}

static char	*tlist_popnstrip(t_list **const restrict astack)
{
	t_list			*first_node;
	char *restrict	stxt;

	if (*astack != NULL)
	{
		first_node = ft_lst_stack_pop(astack);
		stxt = first_node->content;
		ft_bzero(first_node, sizeof(t_list));
		free(first_node);
		return (stxt);
	}
	else
	{
		return (NULL);
	}
}

static int	ft_dirp_process(DIR *const restrict dirp,\
				const t_flags aflags)
{
	t_finfo	*dir_stats;
	t_list	*product;
	char	*cur_txt;
	int		temp;

	dir_stats = NULL;
	if (ft_dirp_to_finfostack(dirp, &dir_stats, aflags) == -1)
	{
		finfo_lstdel(&dir_stats);
		return (-1);
	}
	if (ft_process_files_to_txt(&dir_stats, &product, &temp, aflags) == -1)
	{
		ft_lstdel(&product, &ft_del);
		finfo_lstdel(&dir_stats);
		return (-1);
	}
	while (product != NULL)
	{
		cur_txt = tlist_popnstrip(&product);
		printf("%s\n", cur_txt);
		free(cur_txt);
	}
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
			if (ft_dirp_process(current_dir, aflags) == -1)
			{
				ft_error_cleanup(afstack);
			}
		}
		iterator = iterator->next;
	}
}
