/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt_bonus.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/15 13:23:21 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/18 17:58:12 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H
# include "minirt.h"
# include "pthread.h"
# define THREAD_COUNT 10

typedef struct s_thread{
	int			index;
	t_obj		camera;
	t_screen	screen;
	t_img		*img;
	t_scene		scene;
}				t_thread;

#endif
