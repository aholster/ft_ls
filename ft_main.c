/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 01:15:48 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 09:30:13 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//#include "./incl/ft_finfo.h"
int			main(int argc, char **argv)
{
	t_flags				flag_stock;
	t_finfo *restrict	ndir_stack;
	t_finfo *restrict	dir_stack;

	if (argc == 0)
	{
		dprintf(2, USAGE);
		exit(-1);
	}
	else
	{
		argc--;
		argv++;
		if (argc != 0)
		{
			ft_flag_parser(&argc, &argv, &flag_stock);
			if (argc != 0)
			{
				ft_sort_params(argv, &ndir_stack, &dir_stack, &flag_stock);
			}
		}
		ft_run_stacks(&ndir_stack, &dir_stack, &flag_stock);
	}
	return (1);
}
