/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:12:46 by aholster       #+#    #+#                */
/*   Updated: 2019/11/07 07:53:59 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FINFO_H
# define FT_FINFO_H

# include <stdlib.h>
# include <sys/stat.h>
# include "./ft_flag.h"

typedef struct		s_finfo
{
	char *restrict	s_name;
	struct stat		stat;
	struct s_finfo	*next;
}					t_finfo;

typedef enum		e_sortcode
{
	cor_order,
	bad_order,
}					t_sortcode;

typedef t_sortcode	(*t_decider)(const t_finfo *const restrict,\
						const t_finfo *const restrict,\
						const t_flags *const restrict);

t_finfo				*finfo_lstnew(const char *const restrict s_name,\
						const struct stat *const restrict astat_info);

void				finfo_lstadd(t_finfo *restrict *const restrict alst,\
						t_finfo *const new);

void				finfo_lstiter(t_finfo *restrict lst,\
						void (*const f)(t_finfo *restrict elem));

void				finfo_lstdel(t_finfo *restrict *const restrict alst);
void				finfo_lstdelone(t_finfo *restrict *const restrict alst);

t_finfo				*finfo_stack_pop(\
						t_finfo *restrict *const restrict afinfo_stack);

#endif
