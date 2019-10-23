/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_ndir_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:40:04 by aholster       #+#    #+#                */
/*   Updated: 2019/10/23 19:26:50 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"

void	ft_process_ndir_stack(t_fstack *const restrict afstack,\
			const t_flags *const restrict aflags)
{
	t_list					*out_stack;
	t_list					*new;
	int						longest_name;

	out_stack = NULL;
	longest_name = 0;

	ft_process_file_to_txt(afstack, &out_stack, &longest_name, aflags);

	printf("biggest bloc is %d\n", longest_name);
	while (out_stack != NULL)
	{
		new = out_stack;
		printf("%-*s!\n", longest_name, new->content);
		ft_lstdelone(&new, &ft_del);
		out_stack = out_stack->next;
	}
}
