/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_file_format.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 12:34:59 by aholster       #+#    #+#                */
/*   Updated: 2019/11/20 08:07:33 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FILE_FORMAT_H
# define FT_FILE_FORMAT_H

# include "finfo.h"

# define PERM_LEN 12

# define DATELEN 13
# define MDATELEN 21

# define EPOCH_SIXMONTH 15778476

typedef struct s_list	t_list;

typedef	struct	s_compcaps{
	int			inode_len;
	int			hlink_len;
	int			uname_len;
	int			gname_len;
	int			fsize_len;
	int			fname_len;
}				t_compcaps;

typedef enum	e_component_names{
	f_inode = 0,
	f_perm = 1,
	f_nlnk = 2,
	f_uid = 3,
	f_gid = 4,
	f_size = 5,
	f_date = 6,
	f_name = 7,
}				t_component_names;

# define T_COMPCOUNT 8
# define VECTOR_START 1024

typedef struct	s_fvec{
	size_t		indices[T_COMPCOUNT];
	size_t		tail;
	size_t		size;
	char		*svec;
}				t_fvec;

typedef	int		(*t_comp_gen)(const t_finfo *const restrict,\
					t_compcaps *const restrict,\
					const t_flags);

typedef	t_list	*(*t_unifier)(const t_fvec *const restrict,\
					const t_compcaps *const restrict);

t_unifier		ft_unifier_method(const t_flags aflags);

int				ft_create_components(t_finfo *restrict afinfo_stack,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);

int				ft_fvec_enter_comp(const t_finfo *const restrict afile,\
					const t_component_names component_num,\
					const char *const restrict component_str,\
					const size_t component_size);

int				ft_generate_inode(const t_finfo *const restrict afile,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);

int				ft_generate_hardlinks(const t_finfo *const restrict afile,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);

int				ft_generate_size(const t_finfo *const restrict afile,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);

int				ft_generate_date(const t_finfo *const restrict afile,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);

int				ft_generate_permissions(const t_finfo *const restrict afile,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);
void			init_permissions_table(char permissions_table[4096][10]);

int				ft_generate_uid(const t_finfo *const restrict afile,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);

int				ft_generate_gid(const t_finfo *const restrict afile,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);

int				ft_generate_name(const t_finfo *const restrict afile,\
					t_compcaps *const restrict acaps,\
					const t_flags aflags);

#endif
