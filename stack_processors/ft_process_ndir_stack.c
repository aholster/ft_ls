/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_ndir_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:40:04 by aholster       #+#    #+#                */
/*   Updated: 2019/10/24 19:00:15 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"
#include <sys/ioctl.h>

static void	find_term_width(int *const restrict width)
{
	struct winsize termfo;

	ioctl(0, TIOCGWINSZ, &termfo);
	*width = termfo.ws_row;
}

void	ft_process_ndir_stack(t_fstack *const restrict afstack,\
			const t_flags *const restrict aflags)
{
	t_list					*txtstk;
	t_list					*trail;
	int						longest_full_entry;
	int						term_width;
	int						entry_len;
	unsigned short			entries;

	txtstk = NULL;
	longest_full_entry = 0;
	if (ft_process_files_to_txt(&(afstack->ndir_stack), &txtstk, &longest_full_entry, aflags) == -1)
	{
		ft_lstdel(&txtstk, &ft_del);
		ft_error_cleanup(afstack);
	}
	entry_len = txtstk->content_size;
	find_term_width(&term_width);
	entries = 1;
	// while (txtstk != NULL)
	// {
	// 	trail = txtstk;
	// 	printf("%s", trail->content);
	// 	entries += 1;
	// 	if (entry_len * entries >= term_width)
	// 	{
	// 		printf("\n");
	// 		entries = 0;
	// 	}
	// 	ft_lstdelone(&trail, &ft_del);
	// 	txtstk = txtstk->next;
	// }
	while (txtstk != NULL)
	{
		printf("%s\n", txtstk->content);
		trail = txtstk;
		ft_lstdelone(&trail, &ft_del);
		txtstk = txtstk->next;
	}
}
