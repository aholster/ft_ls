/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_params.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 09:43:25 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 11:31:41 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#include <sys/stat.h>

//#include "./incl/ft_finfo.h"
static void	ft_list_error(t_finfo *restrict *const restrict andir_stack,\
				t_finfo *restrict *const restrict adir_stack)
{
	perror("ft_ls");
	finfo_lstdel(andir_stack);
	finfo_lstdel(adir_stack);
	exit(-1);
}

// static int	ft_pass_to_err(t_list *restrict *const restrict aerr_sort)
// {
	
// }

static void	add_to_stack(t_finfo *restrict *const restrict new_node,\
				t_finfo *restrict *const restrict andir_stack,\
				t_finfo *restrict *const restrict adir_stack,\
				const t_flags *const restrict aflags)
{
	if (((*aflags) & flg_d) == 0 && S_ISDIR((*new_node)->inf.st_mode) == 1)
	{
		finfo_lstadd(adir_stack, (*new_node));
	}
	else
	{
		finfo_lstadd(andir_stack, (*new_node));
	}
	(*new_node) = NULL;
}

void		ft_sort_params(char **restrict argv,\
				t_finfo *restrict *const restrict andir_stack,\
				t_finfo *restrict *const restrict adir_stack,\
				const t_flags *const restrict aflags)
{
	struct stat			stat_info;
	int					ret;
	t_finfo	*restrict	new_node;
//	t_list	*restrict	err_sort;

	while (argv[0] != NULL)
	{
		ret = lstat(argv[0], &stat_info);
		if (ret == 0)
		{
			new_node = finfo_lstnew(argv[0], &stat_info);
			if (new_node == NULL)
			{
				ft_list_error(andir_stack, adir_stack);
			}
			add_to_stack(&new_node, andir_stack, adir_stack, aflags);
		}
		else
		{
			// if (pass_to_err(&err_sort));
			// {
				
			// }
			dprintf(2, "ft_ls: %s: ", argv[0]);
			perror(NULL);
		}
		argv++;
	}
}
