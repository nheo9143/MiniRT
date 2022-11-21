/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nheo <nheo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:06:48 by nheo              #+#    #+#             */
/*   Updated: 2022/11/21 17:20:45 by nheo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../mlx/mlx.h"

static void	parse(char *av, t_info *info)
{
	char	*content;

	content = ft_strdup("");
	if (!content)
		ft_error("malloc failed");
	check_file_extension(av);
	read_file(av, &content);
	parse_to_info(content, info);
}

static void	exceve(t_info *info)
{
	mlx_info_init(info);
	draw(info);
	mlx_key_hook(info->win, key_press, info);
	mlx_mouse_hook(info->win, mouse_click, info);
	mlx_loop(info->mlx);
}

int	main(int ac, char **av)
{
	t_info	info;

	ft_memset(&info, 0, sizeof(t_info));
	if (ac != 2)
		ft_error("wrong number of arguments");
	parse(av[1], &info);
	exceve(&info);
	exit(0);
}
