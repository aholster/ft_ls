/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_ndir_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:40:04 by aholster       #+#    #+#                */
/*   Updated: 2019/10/14 14:04:01 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_sorters.h"

void	ft_process_ndir_stack(t_fstack *const restrict afstack,\
			const t_flags *const restrict aflags)
{
	t_list					*res_lst;
	t_list					*new;
	const t_finfo *restrict	iterator;

	if (((*aflags) & flg_f) == 0)
	{
		ft_sort_finfo_stack(&(afstack->ndir_stack), aflags);
	}
	iterator = afstack->ndir_stack;//create output stack
	res_lst = NULL;
	new = NULL;
	while (iterator != NULL)
	{
		new = ft_lstnew(iterator->s_name, ft_strlen(iterator->s_name) + 1);
		if (new == NULL)
		{
			ft_lstdel(&res_lst, &ft_del);
			ft_error_cleanup(afstack);
		}
		ft_lstadd(&res_lst, new);
		iterator = iterator->next;
	}
	while (res_lst != NULL)//readout and cleanup
	{
		new = res_lst;
		printf("%s\n", new->content);
		ft_lstdelone(&new, &ft_del);
		res_lst = res_lst->next;
	}
}
