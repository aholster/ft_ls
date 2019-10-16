/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sortnprocess_err_queue.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/13 13:58:01 by aholster       #+#    #+#                */
/*   Updated: 2019/10/16 16:28:38 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_sorters.h"

static void		find_midpoint(t_list *lst, t_list **const restrict amidpoint)
{
	t_list	*fast;

	fast = lst->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			lst = lst->next;
			fast = fast->next;
		}
	}
	*amidpoint = lst->next;
	lst->next = NULL;
}

static t_list	*reconstitute_lst(t_list *const front_seg,\
					t_list *const back_seg)
{
	if (front_seg == NULL)
	{
		return (back_seg);
	}
	else if (back_seg == NULL)
	{
		return (front_seg);
	}
	else
	{
		if (ft_strcmp(front_seg->content, back_seg->content) >= 0)
		{
			back_seg->next = reconstitute_lst(front_seg, back_seg->next);
			return (back_seg);
		}
		else
		{
			front_seg->next = reconstitute_lst(front_seg->next, back_seg);
			return (front_seg);
		}
	}
}

static void		merge_sort(t_list **const restrict alst)
{
	t_list	*midpoint;

	if (*alst == NULL || (*alst)->next == NULL)
		return ;
	find_midpoint(*alst, &midpoint);
	merge_sort(alst);
	merge_sort(&midpoint);
	*alst = reconstitute_lst(*alst, midpoint);
}

void			ft_sortnprocess_err_queue(t_fstack *const restrict afstack,
					const t_flags *const restrict aflags)
{
	t_list	*restrict	iterator;
	int					ret;
	struct stat			dummy;

	if (((*aflags) & flg_f) == 0)
	{
		merge_sort(&(afstack->err_queue));
	}
	iterator = afstack->err_queue;
	while (iterator != NULL)
	{
		if (((*aflags) & flg_L) > 0)
		{
			ret = lstat(iterator->content, &dummy);
		}
		else
		{
			ret = stat(iterator->content, &dummy);
		}
		dprintf(2, "ft_ls : %s: ", iterator->content);
		perror(NULL);
		iterator = iterator->next;
	}
	ft_lstdel(&(afstack->err_queue), &ft_del);
}
