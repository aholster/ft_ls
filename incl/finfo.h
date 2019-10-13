/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finfo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/12 15:12:46 by aholster       #+#    #+#                */
/*   Updated: 2019/10/13 13:22:31 by aholster      ########   odam.nl         */
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

t_finfo				*finfo_lstnew(const char *const restrict s_name,\
						const struct stat *const restrict astat_info);

void				finfo_lstadd(t_finfo *restrict *const restrict alst,\
						t_finfo *const new);
void				finfo_lstiter(t_finfo *restrict lst,\
						void (*const f)(t_finfo *restrict elem));

void				finfo_lstdel(t_finfo *restrict *const restrict alst);
void				finfo_lstdelone(t_finfo *restrict *const restrict alst);

#endif
