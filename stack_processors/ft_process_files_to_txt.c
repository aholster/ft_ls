/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/12/07 05:16:05 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static int	create_out_stack(t_finfo *restrict *const restrict afinfo_stack,\
					const t_compcaps *const restrict acaps,\
					t_list **const restrict aout_stack,\
					const t_unifier method)
{
	t_list		*new;
	t_finfo		*current;
	int			longest;

	longest = 0;
	while (*afinfo_stack != NULL)
	{
		current = finfo_stack_pop(afinfo_stack);
		new = method(current->fvect, acaps);
		// finfo_lstdelone(&current);
		if (new == NULL)
		{
			return (-1);
		}
		if ((int)new->content_size > longest)
		{
			longest = new->content_size;
		}
		ft_lstaddend(aout_stack, new);
	}
	return (longest);
}

int			ft_process_files_to_txt(\
				t_finfo *restrict *const restrict afinfo_stack,\
				t_list **const restrict aout_stack,\
				int *const restrict amax_len,\
				const t_flags aflags)
{
	t_compcaps	caps;
	t_unifier	method;
	int			holder;

	ft_bzero(&caps, sizeof(t_compcaps));
	if (ft_create_components(*afinfo_stack, &caps, aflags) == -1)
	{
		return (-1);
	}
	else
	{
		method = ft_unifier_method(aflags);
		holder = create_out_stack(afinfo_stack, &caps, aout_stack, method);
		if (holder == -1)
		{
			return (-1);
		}
		else
		{
			*amax_len = holder;
			return (1);
		}
	}
}
