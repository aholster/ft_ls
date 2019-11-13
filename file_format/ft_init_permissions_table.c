/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_init_permissions_table.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 10:14:50 by aholster       #+#    #+#                */
/*   Updated: 2019/11/13 15:41:06 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "../libft/libft.h"

static const char g_init_tbl[8][4] = {
	[0] = "---",
	[1] = "--x",
	[2] = "-w-",
	[3] = "-wx",
	[4] = "r--",
	[5] = "r-x",
	[6] = "rw-",
	[7] = "rwx",
};

static void	generate_permissions_line(char *const restrict abuf,\
				const mode_t perm_modes)
{
	ft_memcpy(abuf + 6, g_init_tbl[(perm_modes & S_IRWXO)], 3);
	if ((S_ISVTX & perm_modes) > 0)
	{
		if ((S_IXOTH & perm_modes) > 0)
			abuf[8] = 't';
		else
			abuf[8] = 'T';
	}
	ft_memcpy(abuf + 3, g_init_tbl[(perm_modes & S_IRWXG) >> 3], 3);
	if ((S_ISGID & perm_modes) > 0)
	{
		if ((S_IXGRP & perm_modes) > 0)
			abuf[5] = 's';
		else
			abuf[5] = 'S';
	}
	ft_memcpy(abuf, g_init_tbl[(perm_modes & S_IRWXU) >> 6], 3);
	if ((S_ISUID & perm_modes) > 0)
	{
		if ((S_IXUSR & perm_modes) > 0)
			abuf[2] = 's';
		else
			abuf[2] = 'S';
	}
}

void		init_permissions_table(char permissions_table[4096][10])
{
	mode_t aiter;

	aiter = 0;
	while (aiter <= ALLPERMS)
	{
		generate_permissions_line(permissions_table[aiter], aiter);
		aiter++;
	}
}
