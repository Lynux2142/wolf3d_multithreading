/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 12:59:44 by bede-fre          #+#    #+#             */
/*   Updated: 2018/07/20 15:16:12 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static int		ft_wall_height_on_screen(double dist)
{
	return ((int)(((double)FPX / 2.0) / tan(ft_rad(FOV / 2.0))
		* (CAM_HEIGHT) / dist));
}

static int		ft_color_textures(t_img *ptr, double cpt, int col)
{
	return (ft_rgba(
		ptr->data[col * 4 + ((int)(CAM_HEIGHT + cpt) * ptr->sl) + 2],
		ptr->data[col * 4 + ((int)(CAM_HEIGHT + cpt) * ptr->sl) + 1],
		ptr->data[col * 4 + ((int)(CAM_HEIGHT + cpt) * ptr->sl)],
		ptr->data[col * 4 + ((int)(CAM_HEIGHT + cpt) * ptr->sl) + 3]));
}

static int		ft_find_color(t_all *all, double cpt, int col)
{
	if (all->rc.ray.hit == N_W)
		return (ft_color_textures(&all->textures.img_n, cpt, col));
	else if (all->rc.ray.hit == S_W)
		return (ft_color_textures(&all->textures.img_s, cpt, col));
	else if (all->rc.ray.hit == E_W)
		return (ft_color_textures(&all->textures.img_e, cpt, col));
	else
		return (ft_color_textures(&all->textures.img_w, cpt, col));
}

static void		ft_print_textures(t_all *all, int x, int i, double h)
{
	int		col;
	double	cpt;

	cpt = (double)i * (BLOCK_SIZE / (h * 2.0));
	if (all->rc.ray.hit == N_W || all->rc.ray.hit == S_W)
		col = (int)(all->rc.ray.x - ft_roundminf(all->rc.ray.x, BLOCK_SIZE));
	else
		col = (int)(all->rc.ray.y - ft_roundminf(all->rc.ray.y, BLOCK_SIZE));
	ft_fill_pixel(&all->fp, x, (WINY / 2) + i, ft_find_color(all, cpt, col));
	ft_fill_pixel(&all->fp, x, (WINY / 2) - i, ft_find_color(all, -cpt, col));
}

void			ft_print_on_screen(t_all *all, int x, double lens)
{
	int		i;
	double	h;

	i = -1;
	h = ft_wall_height_on_screen(all->rc.ray.dist * cos(lens));
	while ((++i + (WINY / 2)) <= WINY)
	{
		if ((double)i >= h)
		{
			ft_fill_pixel(&all->fp, x, (WINY / 2) - i, TOP);
			ft_fill_pixel(&all->fp, x, (WINY / 2) + i, BOTTOM);
		}
		else
		{
			if (all->keys_tab[KEY_T] == TRUE)
				ft_print_textures(all, x, i, h);
			else if (all->keys_tab[KEY_T] == FALSE)
			{
				ft_fill_pixel(&all->fp, x, (WINY / 2) + i, all->rc.ray.hit);
				ft_fill_pixel(&all->fp, x, (WINY / 2) - i, all->rc.ray.hit);
			}
		}
	}
}
