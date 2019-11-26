/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stack_processors.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/16 16:27:27 by aholster       #+#    #+#                */
/*   Updated: 2019/11/26 10:12:07 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_PROCESSORS_H
# define FT_STACK_PROCESSORS_H

# include "../ft_ls.h"

typedef struct	s_print_widths{
	int			byt_width;
	int			vis_width;
}				t_print_widths;

void			ft_process_ndir_stack(t_fstack *const restrict afstack,\
					const t_flags aflags);

void			ft_process_dir_stack(t_fstack *const restrict afstack,\
					const t_flags aflags);

int				ft_process_files_to_txt(\
					t_finfo *restrict *const restrict afinfo_stack,\
					t_list **const restrict aout_stack,\
					t_print_widths *const restrict awidths,\
					const t_flags aflags);

int				ft_printer(const t_list *const restrict out_list,\
					const t_print_widths *const restrict awidths,\
					const t_flags aflags);

int				ft_multi_column_print(const t_list *restrict iterator,\
					const int byt_width,\
					const int vis_width,\
					const uint32_t term_width);

#endif
