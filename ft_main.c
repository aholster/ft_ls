/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 01:15:48 by aholster       #+#    #+#                */
/*   Updated: 2019/11/30 23:45:34 by aholster      ########   odam.nl         */
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

	if (afstack->ndir_stack == NULL &&\
		afstack->dir_stack == NULL &&\
		afstack->err_queue == NULL)
	{
		fake_argv[0] = ".";
		fake_argv[1] = NULL;
		ft_sort_params(fake_argv, afstack, aflags);
	}
}

int			main(int argc, char **argv)
{
	t_flags				flag_stock;
	t_fstack			fil_stack;

	if (argc == 0)
	{
		dprintf(2, USAGE);
		exit(-1);
	}
	else
	{
		flag_stock = basic;
		if (argc != 1)
		{
			ft_flag_parser(&argc, &argv, &flag_stock);
			if (argc != 0)
			{
				ft_sort_params(argv, &fil_stack, flag_stock);
			}
		}
		set_default_flags(&flag_stock);
		stack_minimum_assert(&fil_stack, flag_stock);
		ft_run_stacks(&fil_stack, flag_stock);
	}
	return (0);
}
