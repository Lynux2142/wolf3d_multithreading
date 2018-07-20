/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 14:06:10 by lguiller          #+#    #+#             */
/*   Updated: 2018/07/20 15:03:15 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_dist(char map[MAPY][MAPX], t_ray *ray, t_player *p)
{
	int		i;

	ray->x = ray->fx;
	ray->y = ray->fy;
	i = 0;
	while (ray->x >= 0.0 && ray->x < (MAPX * BLOCK_SIZE)
		&& ray->y >= 0.0 && ray->y < (MAPY * BLOCK_SIZE)
		&& map[TO_MAP(ray->y)][TO_MAP(ray->x)] != WALL
		&& map[TO_MAP(ray->y)][TO_MAP(ray->x)] != SECRET)
	{
		ray->x += ray->xa;
		ray->y += ray->ya;
		++i;
	}
	ray->dx = fabs(p->x - ray->x);
	ray->dy = fabs(p->y - ray->y);
	ray->dist = sqrt(pow(ray->dx, 2) + pow(ray->dy, 2));
}

static void	ft_fp_hori(t_ray *ray, t_player *p, char map[MAPY][MAPX], double a)
{
	if (a == WEST || a == EAST || a == EAST2)
		ray->fy = p->y;
	else if (sin(a) >= 0)
		ray->fy = ft_roundminf(p->y, (int)BLOCK_SIZE) - LITTLE;
	else
		ray->fy = ft_roundmsup(p->y, (int)BLOCK_SIZE);
	ray->fx = p->x + (p->y - ray->fy) / tan(a);
	ray->ya = (sin(a) >= 0) ? -BLOCK_SIZE : BLOCK_SIZE;
	ray->xa = -ray->ya / tan(a);
	ft_dist(map, ray, p);
	ray->hit = (sin(a) > 0) ? S_W : N_W;
}

static void	ft_fp_vert(t_ray *ray, t_player *p, char map[MAPY][MAPX], double a)
{
	if (a == NORTH || a == SOUTH)
		ray->fx = p->x;
	else if (cos(a) < 0)
		ray->fx = ft_roundminf(p->x, (int)BLOCK_SIZE) - LITTLE;
	else
		ray->fx = ft_roundmsup(p->x, (int)BLOCK_SIZE);
	ray->fy = p->y + (p->x - ray->fx) * tan(a);
	ray->xa = (cos(a) < 0) ? -BLOCK_SIZE : BLOCK_SIZE;
	ray->ya = -ray->xa * tan(a);
	ft_dist(map, ray, p);
	ray->hit = (cos(a) > 0) ? W_W : E_W;
}

void		*ft_wall_dist(void *ptr)
{
	t_all	*all;

	all = (t_all*)ptr;
	ft_fp_hori(&all->rc.ray_h, &all->p, all->rc.map, all->a);
	ft_fp_vert(&all->rc.ray_v, &all->p, all->rc.map, all->a);
	if (all->rc.ray_h.dist != all->rc.ray_h.dist || all->rc.ray_v.dist != all->rc.ray_v.dist)
		all->rc.ray = (all->rc.ray_h.dist != all->rc.ray_h.dist) ? all->rc.ray_v : all->rc.ray_h;
	else
		all->rc.ray = (all->rc.ray_h.dist <= all->rc.ray_v.dist) ? all->rc.ray_h : all->rc.ray_v;
	if (all->p.ray_infos == 1)
	{
		ft_putstr("ray dist: ");
		ft_putnbr(all->rc.ray.dist);
		ft_putchar('\n');
	}
	ft_algo(&all->info, all->rc.ray, &all->p, YELLOW);
	ft_perso(&all->info, all->p.x, all->p.y);
	ft_print_on_screen(all, all->i, all->lens);
	pthread_exit(NULL);
}
