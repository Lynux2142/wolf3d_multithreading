/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bede-fre <bede-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 13:28:36 by bede-fre          #+#    #+#             */
/*   Updated: 2018/06/01 15:05:36 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	ft_fill_line(t_algo_brez algo, t_img *ptr, int col, t_player *p)
{
	algo.cumul = algo.da / 2;
	while (algo.i <= algo.da)
	{
		algo.a += algo.cpta;
		algo.cumul += algo.db;
		if (algo.cumul >= algo.da)
		{
			algo.cumul -= algo.da;
			algo.b += algo.cptb;
		}
		if (VIEW_DIST < sqrtf(powf((double)algo.a - (p->x / ZOOM), 2.0) +
		powf((p->y / ZOOM) - (double)algo.b, 2.0)))
			break ;
		ft_fill_pixel(ptr, algo.a, algo.b, col);
		algo.i++;
	}
}

static void	ft_fill_column(t_algo_brez algo, t_img *ptr, int col, t_player *p)
{
	algo.cumul = algo.db / 2;
	while (algo.i <= algo.db)
	{
		algo.b += algo.cptb;
		algo.cumul += algo.da;
		if (algo.cumul >= algo.db)
		{
			algo.cumul -= algo.db;
			algo.a += algo.cpta;
		}
		if (VIEW_DIST < sqrtf(powf((double)algo.a - (p->x / ZOOM), 2.0) +
		powf((p->y / ZOOM) - (double)algo.b, 2.0)))
			break ;
		ft_fill_pixel(ptr, algo.a, algo.b, col);
		algo.i++;
	}
}

void		ft_algo(t_img *ptr, t_ray ray, t_player *p, int col)
{
	t_algo_brez	algo;

	algo.a = (int)(p->x / ZOOM);
	algo.b = (int)(p->y / ZOOM);
	algo.da = (int)((ray.x - p->x) / ZOOM);
	algo.db = (int)((ray.y - p->y) / ZOOM);
	algo.cpta = (algo.da > 0) ? 1 : -1;
	algo.cptb = (algo.db > 0) ? 1 : -1;
	algo.da = ft_abs(algo.da);
	algo.db = ft_abs(algo.db);
	ft_fill_pixel(ptr, algo.a, algo.b, col);
	algo.i = 1;
	if (algo.da > algo.db)
		ft_fill_line(algo, ptr, col, p);
	else
		ft_fill_column(algo, ptr, col, p);
}
