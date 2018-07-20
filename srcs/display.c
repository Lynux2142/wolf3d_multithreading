/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:55:11 by lguiller          #+#    #+#             */
/*   Updated: 2018/07/20 15:15:48 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_fill_pixel(t_img *ptr, int x, int y, int col)
{
	if ((y >= 0 && y < WINY) && (x >= 0 && x < WINX))
	{
		if (ptr->endian == 0 && ptr->bpp == (8 * 4))
		{
			((char *)(ptr->data))[((x * 4) + (y * ptr->sl))] =
				(char)col;
			((char *)(ptr->data))[((x * 4) + (y * ptr->sl)) + 1] =
				(char)(col >> 8);
			((char *)(ptr->data))[((x * 4) + (y * ptr->sl)) + 2] =
				(char)(col >> 16);
			((char *)(ptr->data))[((x * 4) + (y * ptr->sl)) + 3] =
				(char)(col >> 24);
		}
	}
}

static void	ft_test(t_all *tmp, t_all *all)
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
	tmp->lens = all->lens;
}

void		ft_print_all(t_all *all)
{
	pthread_t	test[FPX];
	t_all		*tmp[FPX];
	int			i;

	all->a = all->p.a + ft_rad(FOV / 2.0);
	all->lens = ft_rad(FOV / 2.0) * all->keys_tab[KEY_H];
	all->i = -1;
	while (++all->i < FPX)
	{
		tmp[all->i] = (t_all*)malloc(sizeof(t_all));
		ft_test(tmp[all->i], all);
		pthread_create(&test[all->i], NULL, ft_wall_dist, tmp[all->i]);
		all->lens -= ft_rad(RAY_ANGLE) * all->keys_tab[KEY_H];
		all->a -= ft_rad(RAY_ANGLE);
	}
	i = -1;
	while (++i < FPX)
		pthread_join(test[i], NULL);
	ft_print_map(&all->info, all->rc.map);
}

static int	ft_quit(void)
{
	exit(0);
}

void		ft_draw(t_all all, char *name)
{
	char	*title;

	title = ft_strjoin("wolf3d - ", name);
	ft_init_mlx(&all, title);
	free(title);
	mlx_hook(all.ptr.win, 2, (1L << 0), ft_key_press, &all);
	mlx_hook(all.ptr.win, 3, (1L << 1), ft_key_release, &all);
	mlx_hook(all.ptr.win, 4, (1L << 2), ft_button_press, &all);
	mlx_hook(all.ptr.win, 17, 0, ft_quit, 0);
	mlx_loop_hook(all.ptr.mlx, ft_movements, &all);
	ft_print_all(&all);
	mlx_loop(all.ptr.mlx);
}
