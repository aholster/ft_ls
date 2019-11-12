/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_file_format.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 12:34:59 by aholster       #+#    #+#                */
/*   Updated: 2019/11/12 05:50:30 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_FORMAT_H
# define FT_FILE_FORMAT_H

# include "finfo.h"

# define MAX_INODE_LEN 21

# define PERMLST_LEN 12

# define MAX_HLINK_LEN 7

# define MAX_UIDGID_LEN 128

# define DATELEN 13
# define MAX_DATELEN 21

# define EPOCH_SIXMONTH 15778476

typedef struct s_list	t_list;

typedef	struct	s_longests{
	int			fname_len;
	int			inode_len;
	int			hlink_len;
	int			fsize_len;
	int			gname_len;
	int			uname_len;
	int			date_len;
}				t_longests;

typedef enum	e_components{
	f_inode = 0,
	f_permlst = 1,
	f_hardlinks = 2,
	f_uid = 3,
	f_gid = 4,
	f_size = 5,
	f_date = 6,
	f_name = 7,
}				t_components;

# define T_COMPCOUNT 8
# define VECTOR_START 1028

typedef struct	s_fvec{
	size_t			indices[T_COMPCOUNT];
	size_t			tail;
	size_t			size;
	char			*vector;
	struct s_fvec	*next;
}				t_fvec;

typedef struct	s_fvec_queue{
	t_longests	caps;
	t_fvec		*fvec_lst;
	t_fvec		*tail_lst;
}				t_fvec_queue;

int				ft_create_intermediate(\
					t_finfo *restrict *const restrict afinfo_stack,\
					t_fvec_queue *const restrict aintermediate,\
					const t_flags *const restrict aflags);

void			ft_find_longest_fields(const t_finfo *restrict finfo_stack,\
					t_longests *const restrict amin_fields,\
					int *const restrict amax_len,\
					const t_flags *const restrict aflags);

int				ft_long_format_file(const t_finfo *const restrict cur_file,\
					t_list **const restrict aout_stack,\
					const t_longests *const restrict amin_fields,\
					const t_flags *const restrict aflags);

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
