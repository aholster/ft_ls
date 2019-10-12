/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_params.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 09:43:25 by aholster       #+#    #+#                */
/*   Updated: 2019/10/12 12:25:17 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <errno.h>
#include <sys/stat.h>

static void	add_to_stack(const char *const restrict entry_name,\
				const struct stat *const restrict astat_info,\
				t_list **const restrict andir_stack,\
				t_list **const restrict adir_stack)
{
	t_list	*new_node;

	new_node = ft_lstnew(entry_name, ft_strlen(entry_name));
	if (new_node == NULL)
	{
		perror("ft_ls");
		ft_lstdel(andir_stack, &ft_del);
		ft_lstdel(adir_stack, &ft_del);
		exit(-1);
	}
	if (S_ISDIR(astat_info->st_mode) == 1)
	{
		ft_lstadd(adir_stack, new_node);
	}
	else
	{
		ft_lstadd(andir_stack, new_node);
	}
}

void		ft_sort_params(char **restrict argv,\
				t_list **const restrict andir_stack,\
				t_list **const restrict adir_stack,\
				t_flags *const restrict aflags)
{
	struct stat	stat_info;
	int			ret;

	while (argv[0] != NULL)
	{
		ret = lstat(argv[0], &stat_info);
		if (ret == 0)
		{
			add_to_stack(argv[0], &stat_info, andir_stack, adir_stack);
		}
		else
		{
			dprintf(2, "ft_ls: %s: ", argv[0]);
			perror(NULL);
		}
		argv++;
	}
	(void)aflags;//remove later
}

/*
**		(void)aflags;//present for future -H, -L or -P
**		if ()//some flag if thingy?
**			ret = stat(argv[0], &stat_info);
**		else
**			ret = lstat(argv[0], &stat_info);
*/
