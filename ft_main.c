/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_main.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 01:15:48 by aholster       #+#    #+#                */
/*   Updated: 2019/10/11 13:35:40 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
//#include "./libft/libft.h"
#include "./incl/ft_arg_struct.h"

static void	add_base_dir(t_list *restrict *const restrict adir_list)
{
	*adir_list = ft_lstnew(".", 2);
	if (*adir_list == NULL)
	{
		perror("ft_ls");
		exit(-1);
	}
}

int			main(int argc, char **argv)
{
	t_flags		flag_stock;
	t_list		*ndir_list = NULL;
	t_list		*dir_list = NULL;
	t_argstruct	args;

	if (argc == 0)
	{
		dprintf(2, "%s\n", USAGE);
		exit(-1);
	}
	else
	{
		args.argc = argc - 1;
		args.argv = argv + 1;
		if (argc != 0)
		{
			ft_flag_parser(&args, &flag_stock);
			if (argc != 0)
				ft_sort_params(&args, &ndir_list, &dir_list, &flag_stock);
		}
		else
			add_base_dir(&dir_list);
		//
		//
		//runqueue
		//	linelimit
		ft_lstdel(&ndir_list, &ft_del);
		ft_lstdel(&dir_list, &ft_del);
	}
	return (1);
}
