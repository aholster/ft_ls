/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_ndir_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:40:04 by aholster       #+#    #+#                */
/*   Updated: 2019/11/12 05:28:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_stack_processors.h"
#include <sys/ioctl.h>

static void	find_term_width(int *const restrict width)
{
	struct winsize termfo;

	ioctl(0, TIOCGWINSZ, &termfo);
	*width = termfo.ws_row;
}

static char	*tlist_popnstrip(t_list **const restrict astack)
{
	t_list			*first_node;
	char *restrict	stxt;

	if (*astack != NULL)
	{
		first_node = ft_lst_stack_pop(astack);
		stxt = first_node->content;
		ft_bzero(first_node, sizeof(t_list));
		free(first_node);
		return (stxt);
	}
	else
	{
		return (NULL);
	}
}

void		ft_process_ndir_stack(t_fstack *const restrict afstack,\
				const t_flags *const restrict aflags)
{
	t_list					*out_stack;
	char *restrict			cur_txt;
	int						max_len;
	int						term_width;

	out_stack = NULL;
	max_len = 0;
	if (ft_process_files_to_txt(&(afstack->ndir_stack),\
		&out_stack, &max_len, aflags) == -1)
	{
		ft_lstdel(&out_stack, &ft_del);
		ft_error_cleanup(afstack);
	}
	find_term_width(&term_width);
	while (out_stack != NULL)
	{
		cur_txt = tlist_popnstrip(&out_stack);
		printf("%s\n", cur_txt);
		free(cur_txt);
	}
}
