/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 01:15:48 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 07:03:39 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		flag_stock = 0;
		argc--;
		argv++;
		if (argc != 0)
		{
			ft_flag_parser(&argc, &argv, &flag_stock);
			if (argc != 0)
			{
				ft_sort_params(argv, &fil_stack, flag_stock);
			}
		}
		stack_minimum_assert(&fil_stack, flag_stock);
		ft_run_stacks(&fil_stack, flag_stock);
	}
	return (1);
}
