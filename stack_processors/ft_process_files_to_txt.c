/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 10:16:59 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../incl/ft_stack_processors.h"
#include "../libft/libft.h"

static int	create_out_stack(t_finfo *restrict *const restrict afinfo_stack,\
					t_compcaps *const restrict acaps,\
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
		finfo_lstdelone(&current);
		if (new == NULL)
		{
			return (-1);
		}
		if ((int)new->content_size > longest)
		{
			longest = (int)new->content_size;
		}
		ft_lstadd(aout_stack, new);
	}
	acaps->max_len = longest;
	return (1);
}

int			ft_process_files_to_txt(\
				t_finfo *restrict *const restrict afinfo_stack,\
				t_list **const restrict aout_stack,\
				t_print_widths *const restrict awidths,\
				const t_flags aflags)
{
	t_compcaps	caps;
	t_unifier	method;

	ft_bzero(&caps, sizeof(t_compcaps));
	if (ft_create_components(*afinfo_stack, &caps, aflags) == -1)
	{
		return (-1);
	}
	else
	{
		method = ft_unifier_method(aflags);
		if (create_out_stack(afinfo_stack, &caps, aout_stack, method) == -1)
		{
			return (-1);
		}
		else
		{
			awidths->byt_width = caps.max_len;
			if ((aflags & flg_G) == flg_G)
				awidths->vis_width = awidths->byt_width - COLOR_LEN;
			else
				awidths->vis_width = awidths->byt_width;
			return (1);
		}
	}
}
