/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sorter_method.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 15:00:18 by aholster       #+#    #+#                */
/*   Updated: 2019/12/07 13:14:58 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_stack_sorters.h"
#include "../ft_ls.h"

static t_sortcode	lexical_sort(const t_finfo *const restrict pri_node,\
						const t_finfo *const restrict sec_node,\
						const t_flags aflags)
{
	const char *const restrict pri_name = pri_node->s_name;
	const char *const restrict sec_name = sec_node->s_name;

	if (ft_strcmp(pri_name, sec_name) >= 0)
	{
		return (cor_order);
	}
	else
	{
		return (bad_order);
	}
	(void)aflags;
}

static t_sortcode	chrono_sort(const t_finfo *const restrict pri_node,\
						const t_finfo *const restrict sec_node,\
						const t_flags aflags)
{
	const struct timespec *pri_time;
	const struct timespec *sec_time;

	ft_relevant_time(&pri_time, &(pri_node->stat), aflags);
	ft_relevant_time(&sec_time, &(sec_node->stat), aflags);
	if (pri_time->tv_sec == sec_time->tv_sec)
	{
		if (pri_time->tv_sec == sec_time->tv_sec)
		{
			return (lexical_sort(pri_node, sec_node, aflags));
		}
		else if (pri_time->tv_nsec < sec_time->tv_nsec)
			return (cor_order);
		else
			return (bad_order);
	}
	else
	{
		if (pri_time->tv_sec < sec_time->tv_sec)
			return (cor_order);
		else
			return (bad_order);
	}
}

t_decider			ft_sorter_method(const t_flags aflags)
{
	if ((aflags & flg_t) > 0)
	{
		return (&chrono_sort);
	}
	else
	{
		return (&lexical_sort);
	}
}
