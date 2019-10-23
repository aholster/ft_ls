/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_file_to_txt.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/10/23 19:26:26 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"

void	ft_process_file_to_txt(t_fstack *const restrict afstack,\
			t_list **const restrict aout_stack,\
			int	*const restrict longest_name_len,\
			const t_flags *const restrict aflags)
{
	const t_finfo *restrict	iterator;
	t_list					*new;
	int						namelen;

	iterator = afstack->ndir_stack;
	while (iterator != NULL)
	{
		namelen = (int)ft_strlen(iterator->s_name);
		if (namelen + 1 > *longest_name_len)
			*longest_name_len = namelen + 1;
		new = ft_lstnew(iterator->s_name, ft_strlen(iterator->s_name) + 1);
		if (new == NULL)
		{
			ft_lstdel(aout_stack, &ft_del);
			ft_error_cleanup(afstack);
		}
		ft_lstadd(aout_stack, new);
		iterator = iterator->next;
	}
	(void)aflags;
}
