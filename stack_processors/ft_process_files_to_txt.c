/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/10/24 18:59:14 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"

static void	find_largest_fields(t_finfo *restrict lst_iterator,\
				t_longests *const restrict amin_fields)
{
	int						namelen;

	while (lst_iterator != NULL)
	{
		namelen = (int)ft_strlen(lst_iterator->s_name);
		if (namelen + 1 > amin_fields->fname)
		{
			amin_fields->fname = namelen + 1;
		}
		lst_iterator = lst_iterator->next;
	}
}

int			ft_process_files_to_txt(\
				t_finfo *restrict *const restrict afinfo_stack,\
				t_list **const restrict aout_stack,\
				int *const restrict abiggest_len,\
				const t_flags *const restrict aflags)
{
	const t_finfo *restrict	iterator;
	t_finfo					*trail;
	t_list					*new;
	char					holder[1028];
	int						namelen;
	t_longests		min_fields;

	ft_bzero(&min_fields, sizeof(t_longests));
	find_largest_fields(*afinfo_stack, &min_fields);
	*abiggest_len = min_fields.fname;
	iterator = *afinfo_stack;
	*afinfo_stack = NULL;
	while (iterator != NULL)
	{
		namelen = snprintf(holder, sizeof(holder),\
			"%s", iterator->s_name);
		if (namelen == -1)
			return (-1);
		new = ft_lstnew(holder, namelen + 1);
		if (new == NULL)
		{
			return (-1);
		}
		ft_lstadd(aout_stack, new);
		trail = (t_finfo *)iterator;
		iterator = iterator->next;
		finfo_lstdelone(&trail);
	}
	(void)aflags;
	return (1);
}
