/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sorter_method_rev.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 15:00:16 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 09:12:31 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_stack_sorters.h"
#include "../ft_ls.h"

static t_sortcode	rev_chrono_sort(const t_finfo *const restrict pri_node,\
						const t_finfo *const restrict sec_node,\
						const t_flags aflags)
{
	const struct timespec *pri_time;
	const struct timespec *sec_time;

	ft_relevant_time(&pri_time, &(pri_node->stat), aflags);
	ft_relevant_time(&sec_time, &(sec_node->stat), aflags);
	if (pri_time->tv_sec == sec_time->tv_sec)
	{
		if (pri_time->tv_nsec <= sec_time->tv_nsec)
			return (bad_order);
		else
			return (cor_order);
	}
	else
	{
		if (pri_time->tv_sec < sec_time->tv_sec)
			return (bad_order);
		else
			return (cor_order);
	}
}

static t_sortcode	rev_lexical_sort(const t_finfo *const restrict pri_node,\
						const t_finfo *const restrict sec_node,\
						const t_flags aflags)
{
	const char *const restrict pri_name = pri_node->s_name;
	const char *const restrict sec_name = sec_node->s_name;

	if (ft_strcmp(pri_name, sec_name) >= 0)
	{
		return (bad_order);
	}
	else
	{
		return (cor_order);
	}
	(void)aflags;
}

t_decider			ft_sorter_method_rev(const t_flags aflags)
{
	if ((aflags & flg_t) > 0)
	{
		return (&rev_chrono_sort);
	}
	else
	{
		return (&rev_lexical_sort);
	}
}
