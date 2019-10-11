/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort_params.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 09:43:25 by aholster       #+#    #+#                */
/*   Updated: 2019/10/11 15:08:26 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
//#include "./libft/libft.h"
#include "./incl/ft_arg_struct.h"

#include <sys/stat.h>
#include <errno.h>
void	ft_sort_params(t_argstruct *const restrict args,\
			t_list **const restrict andir_list,\
			t_list **const restrict adir_list,\
			t_flags *const restrict aflags)
{
	struct stat	stat_info;

	while (args->argc != 0)
	{
		printf("entry: %s\n", args->argv[0]);
		if (lstat(args->argv[0], &stat_info) == 0)
		{
			printf("inode: %lld, mode %x\n", stat_info.st_ino, stat_info.st_mode);
			if (S_ISDIR(stat_info.st_mode) == 1)
				printf("is dir!\n");
			else if (S_ISREG(stat_info.st_mode) == 1)
				printf("is regular file!\n");
			else if (S_ISLNK(stat_info.st_mode) == 1)
				printf("is symlink!\n");
			else
				printf("is something else?!\n");
		}
		else
		{
			const char *holder = strerror(ENOENT);
			
			dprintf(2, "ft_ls: %s: %s\n", args->argv[0], holder);
		}
		args->argv++;
		args->argc--;
	}
	(void)andir_list;
	(void)adir_list;
	(void)aflags;
}
