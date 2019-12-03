/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_ndir_stack.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/14 10:40:04 by aholster       #+#    #+#                */
/*   Updated: 2019/12/02 22:38:22 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/ft_stack_processors.h"

int		ft_process_ndir_stack(t_finfo **const restrict afinfo_lst,\
				const t_flags aflags)
{
	t_list					*product;
	int						max_len;
	int						status;

	product = NULL;
	max_len = 0;
	if (ft_process_files_to_txt(afinfo_lst, &product, &max_len, aflags) == -1)
	{
		ft_lstdel(&product, &ft_del);
		return (-1);
	}
	status = ft_printer(product, max_len, aflags);
	ft_lstdel(&product, &ft_del);
	if (status == -1)
	{
		return (-1);
	}
	return (1);
}
