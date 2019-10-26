/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:12:46 by aholster       #+#    #+#                */
/*   Updated: 2019/10/26 19:22:03 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FINFO_H
# define FT_FINFO_H

# include <stdlib.h>
# include <sys/stat.h>

typedef struct		s_finfo
{
	char *restrict	s_name;
	struct stat		inf;
	struct s_finfo	*next;
}					t_finfo;

typedef enum		e_sortcode
{
	cor_order,
	bad_order,
}					t_sortcode;

typedef t_sortcode	(*t_decider)(const t_finfo *const restrict,\
						const t_finfo *const restrict);

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
