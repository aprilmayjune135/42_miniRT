/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 14:41:40 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/16 11:13:01 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	return_error(int result, char *message)
{
	ft_putstr("Error\n");
	ft_putstr(message);
	return (result);
}

void	free_objs(t_obj **list)
{
	t_obj	*temp;

	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}

void	free_scene(t_scene **scene)
{
	free_objs(&((*scene)->cameras));
	free_objs(&((*scene)->lights));
	free_objs(&((*scene)->objs));
	free((*scene)->bump);
	free(*scene);
}

int	exit_parse_error(t_scene **scene)
{
	free_scene(scene);
	return (0);
}

int	exit_program(t_minirt *minirt)
{
	free_scene(&minirt->scene);
	ft_putstr("Program exited successfully!\n");
	ft_putstr("Thank you, have a nice day! :)\n");
	exit(0);
}
