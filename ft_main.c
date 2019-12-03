/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 01:15:48 by aholster       #+#    #+#                */
/*   Updated: 2019/12/03 05:53:17 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <unistd.h>

#include "ft_ls.h"

static void	set_default_flags(t_flags *const restrict aflags)
{
	const int	atty = isatty(1);

	if ((*aflags & (flg_m | flg_1 | flg_l | flg_C | flg_x)) == 0)
	{
		if (atty == 1)
		{
			*aflags |= flg_C;
		}
		else
		{
			*aflags |= flg_1;
		}
	}
	if ((*aflags & (flg_q | flg_w | flg_B | flg_b)) == 0)
	{
		if (atty == 1)
		{
			*aflags |= flg_q;
		}
		else
		{
			*aflags |= flg_w;
		}
	}
}

static void	stack_minimum_assert(t_fstack *const restrict afstack,\
				const t_flags aflags)
{
	char	*fake_argv[2];

	if (afstack->ndir_queue.head == NULL &&\
		afstack->dir_queue.head == NULL &&\
		afstack->err_queue.head == NULL)
	{
		fake_argv[0] = ".";
		fake_argv[1] = NULL;
		ft_sort_params(fake_argv, afstack, aflags);
	}
}

int			main(int argc, char **argv)
{
	t_flags				flag_stock;
	t_fstack			file_queues;

	if (argc == 0)
	{
		dprintf(2, USAGE);
		exit(-1);
	}
	else
	{
		ft_bzero(&file_queues, sizeof(t_fstack));
		flag_stock = basic;
		if (argc != 1)
		{
			ft_flag_parser(&argc, &argv, &flag_stock);
			if (argc != 0)
			{
				ft_sort_params(argv, &file_queues, flag_stock);
			}
		}
		set_default_flags(&flag_stock);
		stack_minimum_assert(&file_queues, flag_stock);
		ft_run_stacks(&file_queues, flag_stock);
	}
	return (0);
}
