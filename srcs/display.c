/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 11:55:11 by lguiller          #+#    #+#             */
/*   Updated: 2018/11/08 16:13:04 by lguiller         ###   ########.fr       */
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

void		ft_print_all(t_all *all)
{
	pthread_t	test[FPX / THREAD];
	t_all		*tmp[FPX / THREAD];
	int			i;
	int			x;

	all->a = all->p.a + ft_rad(FOV / 2.0);
	all->lens = ft_rad(FOV / 2.0) * all->keys_tab[KEY_H];
	all->i = -THREAD;
	x = 0;
	while ((all->i += THREAD) < FPX)
	{
		tmp[x] = (t_all*)malloc(sizeof(t_all));
		ft_cpy_struct(tmp[x], all);
		pthread_create(&test[x], NULL, ft_wall_dist, tmp[x]);
		all->lens -= (double)THREAD * ft_rad(RAY_ANGLE) * all->keys_tab[KEY_H];
		all->a -= (double)THREAD * ft_rad(RAY_ANGLE);
		++x;
	}
	i = -1;
	while (++i < FPX / THREAD)
	{
		pthread_join(test[i], NULL);
		free(tmp[i]);
	}
	ft_print_map(&all->info, all->rc.map);
}

int			ft_quit(void)
{
	exit(0);
}

void		ft_draw(t_all all, char *name)
{
	char	*title;

	all.prevx = -8000;
	all.prevy = -8000;
	all.start_wall = WINY / 2;
	title = ft_strjoin("wolf3d - ", name);
	ft_init_mlx(&all, title);
	free(title);
	mlx_hook(all.ptr.win, 2, (1L << 0), ft_key_press, &all);
	mlx_hook(all.ptr.win, 3, (1L << 1), ft_key_release, &all);
	mlx_hook(all.ptr.win, 4, (1L << 2), ft_button_press, &all);
	mlx_hook(all.ptr.win, 6, (1L << 6), ft_mouse_motion, &all);
	mlx_hook(all.ptr.win, 17, 0, ft_quit, 0);
	mlx_loop_hook(all.ptr.mlx, ft_movements, &all);
	ft_print_all(&all);
	mlx_loop(all.ptr.mlx);
}
