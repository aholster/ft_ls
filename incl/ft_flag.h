/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_flag.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: aholster <aholster@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/11 02:14:33 by aholster       #+#    #+#                */
/*   Updated: 2019/10/14 15:36:23 by aholster      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAG_H
# define FT_FLAG_H

typedef	enum	e_flags
{
	flg_R = 1LU << 0,
	flg_a = 1LU << 1,
	flg_d = 1LU << 2,//done?
	flg_f = 1LU << 3,//probably done
	flg_i = 1LU << 4,
	flg_l = 1LU << 5,
	flg_r = 1LU << 6,//done?
	flg_t = 1LU << 7,//done
	flg_u = 1LU << 8,
}				t_flags;

void		ft_flag_parser(int *const restrict aargc,\
				char **restrict *const restrict aargv,\
				t_flags *const restrict aflags);

#endif

/*
** typedef	enum	e_flags
** {
** 	// A = 1LU << 1, include hidden files exept '.' and '..'
** 	// B = 1LU << 2, forceprint non-printable characters as \xxx (octal int) (conflict with -q)
** 	// C = 1LU << 3, force multi-collumn output (def terminal)
** 	// F = 1LU << 4, postfix filetypes based on type\
**		(/ for dir, *for executable, @ symlink, = socket, % whiteout, | fifo)
** 	// G = 1LU << 5, Colourized output!
** 	// H = 1LU << 6, symbolic links on command line are followed?\
**			(intresting, possibly easy) (assumes -F, -d, -l are all off)
** 	// L = 1LU << 7, follow all symlinks to final target (cancels -P)
** 	// O = 1LU << 8, include file flags in (-l) ouput (what??)
** 	// P = 1LU << 9, if argu is symlink, list link rather than object (supresses -H and -L)
 	R = 1LU << 10, Recursive traversal of subdirs
** 	// S = 1LU << 11, sort files by SIZEEE
** 	// T = 1LU << 12, when used with -l, display FULL dates for file
** 	// U = 1LU << 13, use time of file creation for sorting (-t) or (-l)
** 	// W = 1LU << 14, display whiteouts when scanning dir (-S flag)
** 	// at_sign = 1LU << 15, display extended attribute keys and sizes in -l
 	a = 1LU << 16, include dirname starting with '.' (hidden files)
** 	// b = 1LU << 17, same as -B but with c escape codes
** 	// c = 1LU << 18, sort by file status last changed if -t or -l
 	d = 1LU << 19, directories are listed as plain files
** 	// e = 1LU << 20, print access control list if present(-l)
 	f = 1LU << 21, output is not sorted (turns on -a)
** 	// g = 1LU << 22, display groupname in -l, supressing owner
** 	// h = 1LU << 23, in -l, uses unit prefixes to reduce size to 3 digits
	i = 1LU << 24, print inode! (easy!)
** 	// k = 1LU << 25, if -s is on, prints file alloc in kilobytes, not blocks
 	l = 1LU << 26, AWW YEAHH LONG FORMATTTTT
** 	// m = 1LU << 27, stream output format, list across page seperated by ','
** 	// n = 1LU << 28, lists user and group ID numerically (seems doable)(turns on -l)
** 	// o = 1LU << 29, list in (-l) output but omit groupid
** 	// p = 1LU << 30, postfix all dirnames with '/' (mini -F)
** 	// q = 1LU << 31, forceprint non writeables as '?' (defualt to terminal) (conflict with -B)
 	r = 1LU << 32, reverse order of sorting,\
**		lexographical order or oldest entires first (largest last if also size)
** 	// s = 1LU << 33, display number of file system blocks in use by file and total count before (round size to 512 byte blocks)(env varialbe BLOCKSIZE overrides 512)
	t = 1LU << 34, sort by time modified (most recent first), before sort lexic
	u = 1LU << 35, use time of last access instead of last modif for sort
** 	// w = 1LU << 36, force raw-print non-printables (defualt for non-terminal)
** 	// x = 1LU << 37, same as -C except multicollumn sort is sorted across, rather than down the colloumns
** 	// one = 1LU << 38, force output one entry per line (def non-terminal)
** }				t_flags;
**
**	check man for additional flag overrides and dual-activations
*/
