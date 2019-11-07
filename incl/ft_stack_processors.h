/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stack_processors.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:27:27 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 13:37:42 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_PROCESSORS_H
# define FT_STACK_PROCESSORS_H

# include "./../ft_ls.h"

# define MAX_INODE_LEN 21

typedef	struct	s_longests{
	int			inode_len;
	int			fname_len;
	int			hlink_len;
	int			fsize_len;
	int			gname_len;
	int			uname_len;
}				t_longests;

void			ft_process_ndir_stack(t_fstack *const restrict afstack,\
					const t_flags *const restrict aflags);

void			ft_process_dir_stack(t_fstack *const restrict afstack,\
					const t_flags *const restrict aflags);

int				ft_process_files_to_txt(\
					t_finfo *restrict *const restrict afinfo_stack,\
					t_list **const restrict aout_stack,\
					int *const restrict amax_reclen,\
					const t_flags *const restrict aflags);

void			ft_find_longest_fields(t_finfo *restrict finfo_stack,\
					t_longests *const restrict amin_fields,\
					int *const restrict amax_reclen,\
					const t_flags *const restrict aflags);

int				ft_long_format_file(const t_finfo *const restrict cur_file,\
					t_list **const restrict aout_stack,\
					const t_longests *const restrict amin_fields,\
					const t_flags *const restrict aflags);

#endif
