/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_finfo_stack.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 13:03:36 by aholster       #+#    #+#                */
/*   Updated: 2019/11/20 09:41:59 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_stack_sorters.h"

static void		find_midpoint(t_finfo *lst,\
					t_finfo **const restrict amidpoint)
{
	t_finfo	*fast;

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

static t_finfo	*reconstitute_lst(t_finfo *const front_seg,\
					t_finfo *const back_seg,\
					const t_decider method,\
					const t_flags aflags)
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
		if (method(front_seg, back_seg, aflags) == cor_order)
		{
			front_seg->next = reconstitute_lst(front_seg->next, back_seg,\
												method, aflags);
			return (front_seg);
		}
		else
		{
			back_seg->next = reconstitute_lst(front_seg, back_seg->next,\
												method, aflags);
			return (back_seg);
		}
	}
}

static void		finfo_merge_sort(t_finfo **const restrict alst,\
					const t_decider method,\
					const t_flags aflags)
{
	t_finfo	*midpoint;

	if (*alst == NULL || (*alst)->next == NULL)
		return ;
	find_midpoint(*alst, &midpoint);
	finfo_merge_sort(alst, method, aflags);
	finfo_merge_sort(&midpoint, method, aflags);
	*alst = reconstitute_lst(*alst, midpoint, method, aflags);
}

void			ft_sort_finfo_stack(\
					t_finfo *restrict *const restrict afinfo_stack,\
					const t_flags aflags)
{
	t_decider			method;

	if ((aflags & flg_r) == 0)
	{
		method = ft_sorter_method(aflags);
	}
	else
	{
		method = ft_sorter_method_rev(aflags);
	}
	finfo_merge_sort((t_finfo **const restrict)afinfo_stack, method, aflags);
}
