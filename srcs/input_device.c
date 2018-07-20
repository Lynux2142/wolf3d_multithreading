/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_device.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:24:19 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/20 14:54:08 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_key_press(int key, t_all *all)
{
	if (key == KEY_H || key == KEY_T)
		all->keys_tab[key] = (all->keys_tab[key] == FALSE) ? TRUE : FALSE;
	else
		all->keys_tab[key] = 1;
	if (key == ESC)
		exit(0);
	return (1);
}

int		ft_key_release(int key, t_all *all)
{
	if (key != KEY_H && key != KEY_T)
		all->keys_tab[key] = 0;
	return (1);
}

int		ft_button_press(int key, int x, int y, t_all *all)
{
	double a;

	(void)y;
	a = all->p.a - ft_rad(((x - INFOX - 1) - (FPX / 2) - 1) * RAY_ANGLE);
	if (key == 1)
	{
		all->p.ray_infos = 1;
		ft_wall_dist(all);
		all->p.ray_infos = 0;
	}
	return (0);
}
