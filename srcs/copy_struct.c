/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 11:36:09 by lguiller          #+#    #+#             */
/*   Updated: 2018/11/08 16:19:57 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_cpy_struct_3(t_all *tmp, t_all *all)
{
	tmp->lens = all->lens;
	tmp->prevx = all->prevx;
	tmp->prevy = all->prevy;
	tmp->start_wall = all->start_wall;
	tmp->wall_gap1 = all->wall_gap1;
	tmp->wall_gap2 = all->wall_gap2;
}

static void	ft_cpy_struct_2(t_all *tmp, t_all *all)
{
	tmp->rc.ray_v.dist = all->rc.ray_v.dist;
	tmp->rc.ray_v.hit = all->rc.ray_v.hit;
	tmp->rc.ray_v.fx = all->rc.ray_v.fx;
	tmp->rc.ray_v.fy = all->rc.ray_v.fy;
	tmp->rc.ray_v.xa = all->rc.ray_v.xa;
	tmp->rc.ray_v.ya = all->rc.ray_v.ya;
	tmp->rc.ray_v.dx = all->rc.ray_v.dx;
	tmp->rc.ray_v.dy = all->rc.ray_v.dy;
	tmp->rc.ray_v.x = all->rc.ray_v.x;
	tmp->rc.ray_v.y = all->rc.ray_v.y;
	tmp->rc.ray.txtrs = all->rc.ray.txtrs;
	tmp->rc.ray.dist = all->rc.ray.dist;
	tmp->rc.ray.hit = all->rc.ray.hit;
	tmp->rc.ray.fx = all->rc.ray.fx;
	tmp->rc.ray.fy = all->rc.ray.fy;
	tmp->rc.ray.xa = all->rc.ray.xa;
	tmp->rc.ray.ya = all->rc.ray.ya;
	tmp->rc.ray.dx = all->rc.ray.dx;
	tmp->rc.ray.dy = all->rc.ray.dy;
	tmp->rc.ray.x = all->rc.ray.x;
	tmp->rc.ray.y = all->rc.ray.y;
	tmp->p = all->p;
	tmp->a = all->a;
	tmp->i = all->i;
	ft_cpy_struct_3(tmp, all);
}

void		ft_cpy_struct(t_all *tmp, t_all *all)
{
	int	i;

	i = -1;
	while (++i < KEYS_TAB_SIZE)
		tmp->keys_tab[i] = all->keys_tab[i];
	tmp->textures = all->textures;
	tmp->sprites = all->sprites;
	tmp->info = all->info;
	tmp->ptr = all->ptr;
	tmp->fp = all->fp;
	tmp->rc = all->rc;
	tmp->rc.ray.txtrs = all->rc.ray.txtrs;
	tmp->rc.ray_h.txtrs = all->rc.ray_h.txtrs;
	tmp->rc.ray_h.dist = all->rc.ray_h.dist;
	tmp->rc.ray_h.hit = all->rc.ray_h.hit;
	tmp->rc.ray_h.fx = all->rc.ray_h.fx;
	tmp->rc.ray_h.fy = all->rc.ray_h.fy;
	tmp->rc.ray_h.xa = all->rc.ray_h.xa;
	tmp->rc.ray_h.ya = all->rc.ray_h.ya;
	tmp->rc.ray_h.dx = all->rc.ray_h.dx;
	tmp->rc.ray_h.dy = all->rc.ray_h.dy;
	tmp->rc.ray_h.x = all->rc.ray_h.x;
	tmp->rc.ray_h.y = all->rc.ray_h.y;
	tmp->rc.ray_v.txtrs = all->rc.ray_v.txtrs;
	ft_cpy_struct_2(tmp, all);
}
