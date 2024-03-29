/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 02:14:33 by aholster       #+#    #+#                */
/*   Updated: 2019/12/11 07:44:31 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAG_H
# define FT_FLAG_H

typedef	enum	e_flags
{
	basic = 0,
	flg_B = 1LU << 0,
	flg_C = 1LU << 1,
	flg_F = 1LU << 2,
	flg_H = 1LU << 3,
	flg_L = 1LU << 4,
	flg_P = 1LU << 5,
	flg_R = 1LU << 6,
	flg_T = 1LU << 7,
	flg_U = 1LU << 8,
	flg_a = 1LU << 9,
	flg_b = 1LU << 10,
	flg_c = 1LU << 11,
	flg_d = 1LU << 12,
	flg_f = 1LU << 13,
	flg_g = 1LU << 14,
	flg_i = 1LU << 15,
	flg_l = 1LU << 16,
	flg_m = 1LU << 17,
	flg_n = 1LU << 18,
	flg_o = 1LU << 19,
	flg_p = 1LU << 20,
	flg_q = 1LU << 21,
	flg_r = 1LU << 22,
	flg_t = 1LU << 23,
	flg_u = 1LU << 24,
	flg_w = 1LU << 25,
	flg_x = 1LU << 26,
	flg_1 = 1LU << 27,
}				t_flags;

typedef	struct	s_flg_tbl
{
	t_flags		enable;
	t_flags		disable;
}				t_flg_tbl;

void			ft_flag_parser(int *const restrict aargc,\
					char **restrict *const restrict aargv,\
					t_flags *const restrict aflags);

#endif

/*
** typedef	enum	e_flags
** {
** 		// A = 1LU << 1, include hidden files exept '.' and '..'
**	B = 1LU << 2, forceprint non-printable characters as \xxx (octal int)
**	C = 1LU << 3, force multi-collumn output (def terminal)
**	F = 1LU << 4, postfix filetypes based on type\
**		(/ for dir, *for executable, @ symlink, = socket, % whiteout, | fifo)
**	G = 1LU << 5, Colourized output!
** 		// H = 1LU << 6, symbolic links on command line are followed?\
**			(intresting, possibly easy) (assumes -F, -d, -l are all off)
**	L = 1LU << 7, follow all symlinks to final target (cancels -P)
** 		// O = 1LU << 8, include file flags in (-l) ouput (what??)
** 		// P = 1LU << 9, if arg symlink, link over target (supresses -H and -L)
** 	R = 1LU << 10, Recursive traversal of subdirs
** 		// S = 1LU << 11, sort files by SIZEEE
**	T = 1LU << 12, when used with -l, display FULL dates for file
**	U = 1LU << 13, use time of file creation for sorting (-t) or (-l)
** 		// W = 1LU << 14, display whiteouts when scanning dir (-S flag)
** 		// at_sign = 1LU << 15, display extended attribute keys and sizes in -l
** 	a = 1LU << 16, include dirname starting with '.' (hidden files)
**	b = 1LU << 17, same as -B but with c escape codes
**	c = 1LU << 18, use status change time
** 	d = 1LU << 19, directories are listed as plain files
** 		// e = 1LU << 20, print access control list if present(-l)
** 	f = 1LU << 21, output is not sorted (turns on -a)
** 	g = 1LU << 22, display groupname in -l, supressing owner
** 		// h = 1LU << 23, in -l, uses unit prefixes to reduce size to 3 digits
**	i = 1LU << 24, print inode! (easy!)
** 		// k = 1LU << 25, if -s is on, prints size in kilobytes, not blocks
** 	l = 1LU << 26, AWW YEAHH LONG FORMATTTTT
**	m = 1LU << 27, stream output format, list across page seperated by ','
**	n = 1LU << 28, lists user and group ID numerically (turns on -l)
**	o = 1LU << 29, list in (-l) output but omit groupid
**	p = 1LU << 30, postfix all dirnames with '/' (mini -F)
**	q = 1LU << 31, forceprint non writeables as '?' (defualt to terminal)
**	r = 1LU << 32, reverse order of sorting,\
**		lexographical order or oldest entires first (largest last if also size)
** 		// s = 1LU << 33, display number of file system blocks in use by file
** (round size to 512 byte blocks)(env varialbe BLOCKSIZE overrides 512)
**	t = 1LU << 34, sort by time modified (most recent first), before sort lexic
**	u = 1LU << 35, use time of last access
**	w = 1LU << 37, force raw-print non-printables (defualt for non-terminal)
**	x = 1LU << 38, same as -C except multicollumn sort is sorted across
**	one = 1LU << 38, force output one entry per line (def non-terminal)
** }				t_flags;
**
**	check man for additional flag overrides and dual-activations
*/
