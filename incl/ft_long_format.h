/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_long_format.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 12:34:59 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 16:08:33 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LONG_FORMAT_H
# define FT_LONG_FORMAT_H

# include "finfo.h"

# include "ft_stack_processors.h"

# define PERMLST_LEN 12

# define MAX_HLINK_LEN 7

# define MAX_UIDGID_LEN 128

# define TIMELEN 13
# define MAX_TIMELEN 21

# define EPOCH_SIXMONTH 15778476

int				ft_generate_time(char *const restrict abufp,\
					size_t *const restrict aoffset,\
					const struct stat *const restrict astat,\
					const t_flags *const restrict aflags);

void			ft_generate_permissions(char *const restrict aholder,\
					size_t *const restrict aoffset,\
					const t_finfo *const restrict cur_file);
void			init_permissions_table(char permissions_table[4096][10]);

int				ft_generate_gid_uid(char *const restrict aholder,\
					size_t *const restrict aoffset,\
					const struct stat *const restrict stat,\
					const t_longests *const restrict amin_fields);

#endif
