/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_find_longest_fields.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 21:50:00 by aholster       #+#    #+#                */
/*   Updated: 2019/10/31 00:10:34 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"

static int	ull_len(uint64_t inode)
{
	int	len;

	len = 0;
	if (inode == 0)
	{
		return (1);
	}
	while (inode != 0)
	{
		len++;
		inode /= 10;
	}
	return (len);
}

// void		find_long_format_fields(t_finfo *restrict lst_iterator,\
// 				t_longests *const restrict amin_fields)
// {
// 	int						namelen;
// 	uint64_t				inode;

// 	inode = 0;
// 	while (lst_iterator != NULL)
// 	{
// 		namelen = (int)ft_strlen(lst_iterator->s_name);
// 		if (namelen + 1 > amin_fields->fname)
// 		{
// 			amin_fields->fname = namelen + 1;
// 		}
// 		if (lst_iterator->stat.st_ino > inode)
// 		{
// 			inode = lst_iterator->stat.st_ino;
// 		}
// 		lst_iterator = lst_iterator->next;
// 	}
// 	amin_fields->inode = ull_len(inode);
// }

void		find_inode_fields(t_finfo *restrict lst_iterator,\
				t_longests *const restrict amin_fields)
{
	int						namelen;
	uint64_t				inode;

	inode = 0;
	while (lst_iterator != NULL)
	{
		namelen = (int)ft_strlen(lst_iterator->s_name);
		if (namelen + 1 > amin_fields->fname)
		{
			amin_fields->fname = namelen + 1;
		}
		if (lst_iterator->stat.st_ino > inode)
		{
			inode = lst_iterator->stat.st_ino;
		}
		lst_iterator = lst_iterator->next;
	}
	amin_fields->inode = ull_len(inode);
}

void		find_basic_fields(t_finfo *restrict lst_iterator,\
				t_longests *const restrict amin_fields)
{
	int						namelen;

	while (lst_iterator != NULL)
	{
		namelen = (int)ft_strlen(lst_iterator->s_name);
		if (namelen + 1 > amin_fields->fname)
		{
			amin_fields->fname = namelen + 1;
		}
		lst_iterator = lst_iterator->next;
	}
}

void		ft_find_longest_fields(t_finfo *restrict finfo_stack,\
				t_longests *const restrict amin_fields,\
				const t_flags *const restrict aflags)
{
	ft_bzero(amin_fields, sizeof(t_longests));
	// if (((*aflags) & flg_l) > 0)
	// {
	// 	find_long_format_fields(finfo_stack, amin_fields);
	// }
	if (((*aflags) & flg_i) > 0)
	{
		find_inode_fields(finfo_stack, amin_fields);
	}
	else
	{
		find_basic_fields(finfo_stack, amin_fields);
	}
}
