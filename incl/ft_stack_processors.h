/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stack_processors.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:27:27 by aholster       #+#    #+#                */
/*   Updated: 2019/10/26 19:45:29 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_PROCESSORS_H
# define FT_STACK_PROCESSORS_H

# include "./../ft_ls.h"

void			ft_process_ndir_stack(t_fstack *const restrict afstack,\
					const t_flags *const restrict aflags);

void			ft_process_dir_stack(t_fstack *const restrict afstack,\
					const t_flags *const restrict aflags);

int				ft_process_files_to_txt(\
					t_finfo *restrict *const restrict afinfo_stack,\
					t_list **const restrict aout_stack,\
					int *const restrict abiggest_len,\
					const t_flags *const restrict aflags);

typedef	struct	s_longests{
	int			fname;
	int			inode;
	int			groupname;
	int			username;
}				t_longests;

#endif
