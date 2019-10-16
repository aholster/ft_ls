/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_ndir_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:40:04 by aholster       #+#    #+#                */
/*   Updated: 2019/10/16 19:39:47 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"

void	ft_process_ndir_stack(t_fstack *const restrict afstack,\
			const t_flags *const restrict aflags)
{
	t_list					*res_lst;
	t_list					*new;
	int						biggest_bloc;
	int						namelen;
	const t_finfo *restrict	iterator;

	iterator = afstack->ndir_stack;//create output stack
	res_lst = NULL;
	biggest_bloc = 0;
	while (iterator != NULL)
	{
		namelen = (int)ft_strlen(iterator->s_name);
		// if ((namelen % 4) != 0)
		// {
		// 	namelen = namelen / 4 + 1;
		// }
		// else
		// {
		// 	namelen = namelen / 4;
		// }
		if (namelen > biggest_bloc)
			biggest_bloc = namelen;
		new = ft_lstnew(iterator->s_name, ft_strlen(iterator->s_name) + 1);
		if (new == NULL)
		{
			ft_lstdel(&res_lst, &ft_del);
			ft_error_cleanup(afstack);
		}
		ft_lstadd(&res_lst, new);
		iterator = iterator->next;
	}
	printf("biggest bloc is %d\n", biggest_bloc);
	while (res_lst != NULL)//readout and cleanup
	{
		new = res_lst;
		printf("%-*s!\n", biggest_bloc + 1, new->content);
		ft_lstdelone(&new, &ft_del);
		res_lst = res_lst->next;
	}
	(void)aflags;
}
