/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stack_processors.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:27:27 by aholster       #+#    #+#                */
/*   Updated: 2019/12/03 10:20:21 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_PROCESSORS_H
# define FT_STACK_PROCESSORS_H

# include <sys/types.h>
# include <sys/dir.h>

# include "../ft_ls.h"

int				ft_process_ndir_stack(t_finfo **const restrict afinfo_lst,\
					const t_flags aflags);

int				ft_process_files_to_txt(\
					t_finfo *restrict *const restrict afinfo_stack,\
					t_list **const restrict aout_stack,\
					int *const restrict amax_len,\
					const t_flags aflags);

int				ft_process_dir_stack(t_finfo_queue *const restrict dir_queue,\
					const int is_singledir,\
					const t_flags aflags);

int				ft_dirp_to_finfo(DIR *const restrict dirp,\
					const char *const restrict path,\
					t_finfo_queue *const restrict aqueue,\
					const t_flags aflags);

int				ft_printer(const t_list *const restrict out_list,\
					const int max_len,\
					const t_flags aflags);

int				ft_multi_column_print(const t_list *restrict iterator,\
					const int max_len,\
					const uint32_t term_width);

#endif
