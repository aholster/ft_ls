/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 01:15:48 by aholster       #+#    #+#                */
/*   Updated: 2019/10/11 03:31:58 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "./libft/libft.h"

int		main(int argc, char **argv)
{
	t_flags		flag_stock;

	if (argc > 0 && ft_strequ(argv[0], "ft_ls") == 1)
	{
		argc--;
		argv++;
	}
	if (argc != 0)
		ft_flag_parser(&argc, &argv, &flag_stock);
	return (1);
}
