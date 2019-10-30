/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sorter_method.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 15:00:18 by aholster       #+#    #+#                */
/*   Updated: 2019/10/14 17:52:44 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_sorters.h"

static t_sortcode	lexical_sort(const t_finfo *const restrict pri_node,\
						const t_finfo *const restrict sec_node)
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
}

static t_sortcode	chrono_modif_sort(const t_finfo *const restrict pri_node,\
						const t_finfo *const restrict sec_node)
{
	const struct timespec *const pri_time = (&pri_node->inf.st_mtimespec);
	const struct timespec *const sec_time = (&sec_node->inf.st_mtimespec);

	if (pri_time->tv_sec == sec_time->tv_sec)
	{
		// if (pri_time->tv_nsec == sec_time->tv_nsec)
		// {
		// 	if (ft_strcmp(pri_node->s_name, sec_node->s_name) >= 0)
		// 		return (bad_order);
		// 	else
		// 		return (cor_order);
		// }
		if (pri_time->tv_nsec <= sec_time->tv_nsec)
			return (bad_order);
		else
			return (cor_order);
	}
	else
	{
		if (pri_time->tv_sec <= sec_time->tv_sec)
			return (bad_order);
		else
			return (cor_order);
	}
}

static t_sortcode	chrono_access_sort(const t_finfo *const restrict pri_node,\
						const t_finfo *const restrict sec_node)
{
	const struct timespec *const pri_time = (&pri_node->inf.st_atimespec);
	const struct timespec *const sec_time = (&sec_node->inf.st_atimespec);

	if (pri_time->tv_sec == sec_time->tv_sec)
	{
		// if (pri_time->tv_nsec == sec_time->tv_nsec)
		// {
		// 	if (ft_strcmp(pri_node->s_name, sec_node->s_name) >= 0)
		// 		return (bad_order);
		// 	else
		// 		return (cor_order);
		// }
		if (pri_time->tv_nsec <= sec_time->tv_nsec)
			return (bad_order);
		else
			return (cor_order);
	}
	else
	{
		if (pri_time->tv_sec <= sec_time->tv_sec)
			return (bad_order);
		else
			return (cor_order);
	}
}

t_decider			ft_sorter_method(const t_flags *const restrict aflags)
{
	if (((*aflags) & flg_t) > 0)
	{
		if (((*aflags) & flg_u) > 0)
		{
			return (&chrono_access_sort);
		}
		else
		{
			return (&chrono_modif_sort);
		}
	}
	else
	{
		return (&lexical_sort);
	}
}