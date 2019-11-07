/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stack_processors.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:27:27 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 06:31:47 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_PROCESSORS_H
# define FT_STACK_PROCESSORS_H

# include "./../ft_ls.h"

# define PERMLST_LEN 12

# define MAX_INODE_LEN 21

# define TIMELEN 13

# define MAX_TIMELEN 21

# define EPOCH_SIXMONTH 15778476

typedef	struct	s_longests{
	int			fname;
	int			inode;
	int			timelen;
	int			sizelen;
	int			groupname;
	int			username;
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
					const t_flags *const restrict aflags);

int				ft_long_format_file(const t_finfo *const restrict cur_file,\
					t_list **const restrict aout_stack,\
					const t_longests *const restrict amin_fields,\
					const t_flags *const restrict aflags);

int				ft_generate_time(char *const restrict abufp,\
					size_t *const restrict aoffset,\
					const struct stat *const restrict astat,\
					const t_flags *const restrict aflags);

int				ft_generate_permissions(char *const restrict aholder,\
					size_t *const restrict aoffset,\
					const t_finfo *const restrict cur_file);

#endif
