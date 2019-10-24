/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/10/24 19:34:10 by aholster      ########   odam.nl         */
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
	t_list					*new;
	t_finfo *restrict		cur_file;
	char					holder[1028];
	int						namelen;
	t_longests		min_fields;

	ft_bzero(&min_fields, sizeof(t_longests));
	find_largest_fields(*afinfo_stack, &min_fields);
	*abiggest_len = min_fields.fname;
	*afinfo_stack = NULL;
	cur_file = finfo_stack_pop(afinfo_stack);
	while (cur_file != NULL)
	{
		namelen = snprintf(holder, sizeof(holder),\
			"%s", cur_file->s_name);
		if (namelen == -1)
			return (-1);
		new = ft_lstnew(holder, namelen + 1);
		if (new == NULL)
		{
			return (-1);
		}
		ft_lstadd(aout_stack, new);
		finfo_lstdelone(&cur_file);
		cur_file = finfo_stack_pop(afinfo_stack);
	}
	(void)aflags;
	return (1);
}
