/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 17:05:59 by lguiller          #+#    #+#             */
/*   Updated: 2018/07/25 11:38:20 by lguiller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <limits.h>
# include <pthread.h>

# define MAPX			32
# define MAPY			MAPX
# define INFOX			256
# define INFOY			WINY
# define FPX			960
# define FPY			600
# define TEXT_NORTH		"./textures/wood1.xpm"
# define TEXT_SOUTH		"./textures/stone1.xpm"
# define TEXT_EAST		"./textures/metal1.xpm"
# define TEXT_WEST		"./textures/ice1.xpm"
# define SPR_KNIFE		"./sprites/weapon1.xpm"
# define SPR_WOLF		"./sprites/wolf1.xpm"
# define SPR_PAPYRUS	"./sprites/papyrus1.xpm"
# define WINX			FPX + INFOX
# define WINY			FPY
# define BLOCK_SIZE		64.0
# define CAM_HEIGHT		BLOCK_SIZE / 2.0
# define FOV			60.0
# define RAY_ANGLE		FOV / (double)FPX
# define START			's'
# define FLOOR			' '
# define WALL			'1'
# define SECRET			'2'
# define TP_S			'3'
# define TP_E			'4'
# define TO_MAP(x)		(int)x / 64
# define ALPHA			0xFF000000
# define BLACK			0
# define WHITE			0xFFFFFF
# define RED			0xFF0000
# define GREEN			0xFF00
# define BLUE			0xFF
# define LIGHT_GREEN	0xAAFFAA
# define GREY			0x888888
# define YELLOW			0xFFFF00
# define TOP			0x87CEFA
# define BOTTOM			0xFFDA8C
# define N_W			0x940602
# define S_W			0x50468C
# define E_W			0x769600
# define W_W			0xD45E3A
# define NORTH			M_PI / 2.0
# define SOUTH			3.0 * M_PI / 2.0
# define WEST			M_PI
# define EAST			0.0
# define EAST2			2.0 * M_PI
# define HIT_BOX		5.0
# define VIEW_DIST		20.0
# define ZOOM			(double)(((double)MAPX * BLOCK_SIZE) / (double)INFOX)
# define P_SIZE			2.5
# define LITTLE			0.00000000000012
# define TRUE			1
# define FALSE			0
# define THREAD			80

# ifdef __linux__
#  define MOVE_SPEED	2.0
#  define RUN_SPEED		3.0
#  define ROT_SPEED		1.5
#  define ESC			65307
#  define KEY_A			97
#  define KEY_D			100
#  define KEY_W			119
#  define KEY_S			115
#  define KEY_H			104
#  define KEY_Q			113
#  define KEY_E			101
#  define KEY_T			116
#  define KEY_SHIFT		65505
#  define KEYS_TAB_SIZE	65600
# else
#  define MOVE_SPEED	2.0
#  define RUN_SPEED		5.0
#  define ROT_SPEED		2.5
#  define ESC			53
#  define KEY_A			0
#  define KEY_D			2
#  define KEY_W			13
#  define KEY_S			1
#  define KEY_H			4
#  define KEY_Q			12
#  define KEY_E			14
#  define KEY_T			17
#  define KEY_SHIFT		257
#  define KEYS_TAB_SIZE	280
# endif

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_fcoord
{
	double		x;
	double		y;
}				t_fcoord;

typedef struct	s_player
{
	int			ray_infos;
	double		x;
	double		y;
	double		a;
}				t_player;

typedef struct	s_parse
{
	char		*buff;
	char		fd;
	short		i;
}				t_parse;

typedef struct	s_ray
{
	char		*txtrs;
	double		dist;
	int			hit;
	double		fx;
	double		fy;
	double		xa;
	double		ya;
	double		dx;
	double		dy;
	double		x;
	double		y;
}				t_ray;

typedef struct	s_raycast
{
	char		map[MAPY][MAPX];
	t_ray		ray_h;
	t_ray		ray_v;
	t_ray		ray;
}				t_raycast;

typedef struct	s_img
{
	int			endian;
	char		*data;
	void		*img;
	int			bpp;
	int			sl;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	t_img		info;
	t_img		fp;
}				t_mlx;

typedef struct	s_algo_brez
{
	int			cumul;
	int			cpta;
	int			cptb;
	int			da;
	int			db;
	int			i;
	int			a;
	int			b;
}				t_algo_brez;

typedef struct	s_textures
{
	int			height;
	int			width;
	t_img		img_w;
	t_img		img_e;
	t_img		img_n;
	t_img		img_s;
}				t_textures;

typedef struct	s_sprites
{
	void		*papyrus;
	void		*knife;
	int			height;
	void		*wolf;
	int			width;
}				t_sprites;

typedef struct	s_all
{
	int			keys_tab[KEYS_TAB_SIZE];
	t_textures	textures;
	t_sprites	sprites;
	t_img		info;
	t_mlx		ptr;
	t_img		fp;
	t_raycast	rc;
	t_player	p;
	double		a;
	int			i;
	double		lens;
	int			x;
}				t_all;

void			*ft_wall_dist(void *ptr);
void			ft_print_ray_infos(t_all *all);
void			ft_algo(t_img *ptr, t_ray ray, t_player *p, int col);
int				ft_button_press(int key, int x, int y, t_all *all);
void			ft_init_player(char map[MAPY][MAPX], t_player *p);
void			ft_read_file(char *name, char (*map)[MAPY][MAPX]);
void			ft_init_keys_tab(int (*keys_tab)[KEYS_TAB_SIZE]);
void			ft_fill_pixel(t_img *ptr, int x, int y, int col);
void			ft_print_on_screen(t_all *all, int x, double a);
void			ft_print_map(t_img *ptr, char map[MAPY][MAPX]);
void			ft_check_map(char *buff, char (*start)[2]);
void			ft_perso(t_img *img, double x, double y);
void			ft_init_mlx(t_all *all, char *title);
int				ft_key_release(int key, t_all *all);
void			ft_free_map(char map[MAPY][MAPX]);
int				ft_key_press(int key, t_all *all);
void			ft_draw(t_all all, char *name);
void			ft_print_all(t_all *all);
int				ft_movements(t_all *all);
int				ft_quit(void);
void			ft_cpy_struct(t_all *tmp, t_all *all);

#endif
