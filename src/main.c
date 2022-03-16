/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: xchen <xchen@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/01/25 19:23:24 by xchen         #+#    #+#                 */
/*   Updated: 2021/03/16 11:13:44 by xchen         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	int			fd;
	t_minirt	minirt;

	fd = open(argv[1], O_RDONLY);
	if (check_argument(fd, argc, argv, &minirt.save_bmp) == -1)
		return (0);
	if (parse_file(fd, &minirt.scene) == -1)
		return (exit_parse_error(&minirt.scene));
	show_on(argv[1], &minirt);
	return (0);
}
