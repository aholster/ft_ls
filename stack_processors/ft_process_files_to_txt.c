/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/12/07 05:35:43 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

static int	create_out_stack(const t_finfo *restrict finfo_iter,\
					const t_compcaps *const restrict acaps,\
					t_list **const restrict aout_stack,\
					const t_flags aflags)
{
	const t_unifier	method = ft_unifier_method(aflags);
	t_list			*new;
	int				longest;

	longest = 0;
	while (finfo_iter != NULL)
	{
		new = method(finfo_iter->fvect, acaps);
		if (new == NULL)
		{
			return (-1);
		}
		if ((int)new->content_size > longest)
		{
			longest = new->content_size;
		}
		ft_lstaddend(aout_stack, new);
		finfo_iter = finfo_iter->next;
	}
	return (longest);
}

int			ft_process_files_to_txt(\
				t_finfo *const restrict afinfo_lst,\
				t_list **const restrict aout_stack,\
				int *const restrict amax_len,\
				const t_flags aflags)
{
	t_compcaps	caps;
	int			holder;

	ft_bzero(&caps, sizeof(t_compcaps));
	if (ft_create_components(afinfo_lst, &caps, aflags) == -1)
	{
		return (-1);
	}
	else
	{
		holder = create_out_stack(afinfo_lst, &caps, aout_stack, aflags);
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
