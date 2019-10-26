/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_process_files_to_txt.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/18 19:31:37 by aholster       #+#    #+#                */
/*   Updated: 2019/10/26 21:22:52 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./../incl/ft_stack_processors.h"

static int	inode_len(uint64_t inode)
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

static void	find_largest_fields(t_finfo *restrict lst_iterator,\
				t_longests *const restrict amin_fields,\
				const t_flags *const restrict aflags)
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
		if (lst_iterator->inf.st_ino > inode)
		{
			inode = lst_iterator->inf.st_ino;
		}
		lst_iterator = lst_iterator->next;
	}
	(void)aflags;
	amin_fields->inode = inode_len(inode);
}

int			ft_process_files_to_txt(\
				t_finfo *restrict *const restrict afinfo_stack,\
				t_list **const restrict aout_stack,\
				int *const restrict abiggest_len,\
				const t_flags *const restrict aflags)
{
	t_finfo *restrict		cur_file;
	char					holder[1028];
	int						rec_len;
	t_longests				min_fields;

	ft_bzero(&min_fields, sizeof(t_longests));
	find_largest_fields(*afinfo_stack, &min_fields, aflags);
	*abiggest_len = min_fields.fname;//change this to be full entry len
	cur_file = finfo_stack_pop(afinfo_stack);
	while (cur_file != NULL)
	{
		if (((*aflags) & flg_i) > 0)
			rec_len = snprintf(holder, sizeof(holder),"%*llu %s", min_fields.inode, cur_file->inf.st_ino, cur_file->s_name);
		else
			rec_len = snprintf(holder, sizeof(holder),"%s", cur_file->s_name);
		if (rec_len == -1)
		{
			return (-1);
		}
		if (ft_lst_stack_push(aout_stack, holder, rec_len + 1) == -1)
		{
			return (-1);
		}
		finfo_lstdelone(&cur_file);
		cur_file = finfo_stack_pop(afinfo_stack);
	}
	return (1);
}
