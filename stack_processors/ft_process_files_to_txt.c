/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/11/18 22:45:20 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../incl/ft_file_format.h"
#include "../libft/libft.h"

int			ft_process_files_to_txt(\
				t_finfo *restrict *const restrict afinfo_stack,\
				t_list **const restrict aout_stack,\
				int *const restrict amax_len,\
				const t_flags aflags)
{
	int			ret;
	t_compcaps	caps;
	t_unifier	method;
	t_finfo		*current;

	ft_bzero(&caps, sizeof(t_compcaps));
	if (ft_create_components(*afinfo_stack, &caps, aflags) == -1)
	{
		return (-1);
	}
	else
	{
		method = ft_unifier_method(aflags);
		while (*afinfo_stack != NULL)
		{
			current = finfo_stack_pop(afinfo_stack);
			ret = method(current->fvect, &caps, aout_stack);
			if (ret == -1)
			{
				finfo_lstdelone(&current);
				return (-1);
			}
			else if (ret > *amax_len)
			{
				*amax_len = ret;
			}
			finfo_lstdelone(&current);
		}
		finfo_lstdel(afinfo_stack);
		return (1);
	}
}
