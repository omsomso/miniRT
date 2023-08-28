/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:52:43 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/29 01:05:51 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	calculate_selected_bckg(t_data *data, t_pos mouse_pos)
{
	int		obj_count;
	float	obj_selected;

	obj_selected = 0;
	obj_count = count_objects(data->objects) + 2;
	obj_selected = (mouse_pos.x / GUI_EL_WIDTH);
		obj_selected = obj_selected + ((mouse_pos.y / GUI_EL_HEIGHT) \
		* (GUI_MAX_WIDTH / GUI_EL_WIDTH));
	if (obj_selected > obj_count)
		return (-1);
	return (obj_selected + 1);
}

// Finds object in obj linked list by id from 0, advances the list
t_object *find_object(t_object *obj, int id)
{
	int			count;

	count = 0;
	while (obj)
	{
		count++;
		if (count == id)
			return (obj);
		obj = obj->next;
	}
	return (NULL);
}

int	cut_values_int(int *a, int max_a, int min_a)
{
	if (*a > max_a)
		*a = max_a;
	if (*a < min_a)
		*a = min_a;
	return (*a);
}

float	cut_values(float *a, float max_a, float min_a)
{
	if (*a > max_a)
		*a = max_a;
	if (*a < min_a)
		*a = min_a;
	return (*a);
}

int	modify_sphere(t_sphere *sphere, int button, int sel_param)
{
	if (sel_param == 1 && button == 4)
		sphere->center->x -= MOD_POS;
	else if (sel_param == 1 && button == 5)
		sphere->center->x += MOD_POS;
	else if (sel_param == 2 && button == 4)
		sphere->center->y -= MOD_POS;
	else if (sel_param == 2 && button == 5)
		sphere->center->y += MOD_POS;
	else if (sel_param == 3 && button == 4)
		sphere->center->z -= MOD_POS;
	else if (sel_param == 3 && button == 5)
		sphere->center->z += MOD_POS;
	else if (sel_param == 4 && button == 4)
		sphere->radius -= MOD_RADIUS;
	else if (sel_param == 4 && button == 5)
		sphere->radius += MOD_RADIUS;
	else if (sel_param)
		return (1);
	cut_values(&sphere->radius, 100000, 0.1);
	return (0);
}

int	modify_plane_b(t_plane *plane, int button, int sel_param)
{
	if (sel_param == 5 && button == 4)
		plane->normal_vec->x -= MOD_NORMAL;
	else if (sel_param == 5 && button == 5)
		plane->normal_vec->x += MOD_NORMAL;
	else if (sel_param == 6 && button == 4)
		plane->normal_vec->y -= MOD_NORMAL;
	else if (sel_param == 6 && button == 5)
		plane->normal_vec->y += MOD_NORMAL;
	else if (sel_param == 7 && button == 4)
		plane->normal_vec->z -= MOD_NORMAL;
	else if (sel_param == 7 && button == 5)
		plane->normal_vec->z += MOD_NORMAL;
	else if (sel_param)
		return (1);
	cut_values(&plane->normal_vec->x, 1, -1);
	cut_values(&plane->normal_vec->y, 1, -1);
	cut_values(&plane->normal_vec->z, 1, -1);
	return (0);
}

int	modify_plane(t_plane *plane, int button, int sel_param)
{
	int	mod;

	mod = 0;
	if (sel_param == 1 && button == 4)
		mod = plane->point->x -= MOD_POS;
	else if (sel_param == 1 && button == 5)
		mod = plane->point->x += MOD_POS;
	else if (sel_param == 2 && button == 4)
		mod = plane->point->y -= MOD_POS;
	else if (sel_param == 2 && button == 5)
		mod = plane->point->y += MOD_POS;
	else if (sel_param == 3 && button == 4)
		mod = plane->point->z -= MOD_POS;
	else if (sel_param == 3 && button == 5)
		mod = plane->point->z += MOD_POS;
	return (mod += (modify_plane_b(plane, button, sel_param)));
}

int	calculate_selected_param(t_pos mouse_pos)
{
	float	sel_param;
	float	sel_row;

	sel_row = 0;
	while (sel_row * GUI_EL_HEIGHT < mouse_pos.y)
		sel_row++;
	sel_row--;
	sel_param = (mouse_pos.y - (sel_row * GUI_EL_HEIGHT)) / 10;
	sel_param -= 1;
	return (sel_param);
}

int	modify_cylinder_b(t_cylinder *cy, int button, int sel)
{
	if (sel == 8 && button == 4)
		cy->height -= MOD_POS;
	else if (sel == 8 && button == 5)
		cy->height += MOD_POS;
	cut_values(&cy->diameter, 100000, 0.1);
	cut_values(&cy->height, 100000, 0.1);
	return (0);
}

int	modify_cylinder(t_cylinder *cy, int button, int sel)
{
	if (sel == 1 && button == 4)
		cy->center->x -= MOD_POS;
	else if (sel == 1 && button == 5)
		cy->center->x += MOD_POS;
	else if (sel == 2 && button == 4)
		cy->center->y -= MOD_POS;
	else if (sel == 2 && button == 5)
		cy->center->y += MOD_POS;
	else if (sel == 3 && button == 4)
		cy->center->z -= MOD_POS;
	else if (sel == 3 && button == 5)
		cy->center->z += MOD_POS;
	else if (sel == 4 && button == 4)
		cy->radius -= MOD_RADIUS;
	else if (sel == 4 && button == 5)
		cy->radius += MOD_RADIUS;
	modify_cylinder_b(cy, button, sel);
	return (0);
}

int	modify_light(t_data *data, int button, int sel)
{
	if (sel == 1 && button == 4)
		data->light->pos->x -= MOD_POS;
	else if (sel == 1 && button == 5)
		data->light->pos->x += MOD_POS;
	else if (sel == 2 && button == 4)
		data->light->pos->y -= MOD_POS;
	else if (sel == 2 && button == 5)
		data->light->pos->y += MOD_POS;
	else if (sel == 3 && button == 4)
		data->light->pos->z -= MOD_POS;
	else if (sel == 3 && button == 5)
		data->light->pos->z += MOD_POS;
	return (0);
}

int	modify_camera_b(t_data *data, t_gui *gui, int button, int sel)
{
	if (sel == 5 && button == 4)
	{
		rotate_camera_x(data->camera, -1);
		gui->cam_ang_change.x += 1;
	}
	else if (sel == 5 && button == 5)
	{
		rotate_camera_x(data->camera, 1);
		gui->cam_ang_change.x -= 1;
	}
	else if (sel == 6 && button == 4)
	{
		rotate_camera_y(data->camera, -1);
		gui->cam_ang_change.y += 1;
	}
	else if (sel == 6 && button == 5)
	{
		rotate_camera_y(data->camera, 1);
		gui->cam_ang_change.y -= 1;
	}
	return (0);
}

int	modify_camera(t_data *data, t_gui *gui, int button, int sel)
{
	if (sel == 1 && button == 4)
		data->camera->pos->x -= MOD_POS;
	else if (sel == 1 && button == 5)
		data->camera->pos->x += MOD_POS;
	else if (sel == 2 && button == 4)
		data->camera->pos->y -= MOD_POS;
	else if (sel == 2 && button == 5)
		data->camera->pos->y += MOD_POS;
	else if (sel == 3 && button == 4)
		data->camera->pos->z -= MOD_POS;
	else if (sel == 3 && button == 5)
		data->camera->pos->z += MOD_POS;
	else if (sel == 4 && button == 4)
		data->camera->fov -= MOD_FOV;
	else if (sel == 4 && button == 5)
		data->camera->fov += MOD_FOV;
	cut_values_int(&data->camera->fov, 180, 0);
	modify_camera_b(data, gui, button, sel);
	return (0);
}

int	modify_objects(t_data *data, t_gui *gui, int button)
{
	t_object	*obj;
	int			mod;

	mod = 1;
	if (gui->sel_par && (button == 4 || button == 5))
	{
		obj = find_object(data->objects, gui->sel_bckg);
		if (gui->sel_bckg == gui->obj_count - 1)
			modify_light(data, button, gui->sel_par);
		else if (gui->sel_bckg == gui->obj_count)
			modify_camera(data, data->gui, button, gui->sel_par);
		if (!obj)
			return (mod);
		else if (obj->type == SPHERE)
			mod = modify_sphere(obj->object, button, gui->sel_par);
		else if (obj->type == PLANE)
			mod = modify_plane(obj->object, button, gui->sel_par);
		else if (obj->type == CYLINDER)
			mod = modify_cylinder(obj->object, button, gui->sel_par);
	}
	// if (!mod)
		// printf("modified param %d of object %d\n", sel_par, sel_obj_id);
	return (mod);
}

void	conditional_retrace(t_data *data, int button)
{
	if (data->auto_retrace)
		generate_rays(data);
	else if (button == 2 || button == -1)
		generate_rays(data);
}

t_gui	*update_gui_struct(t_data *data, t_gui *gui, t_pos mouse_pos)
{
	gui->mouse_pos = mouse_pos;
	gui->sel_bckg = calculate_selected_bckg(data, mouse_pos);
	if (gui->sel_bckg < 0)
		gui->sel_bckg = -1;
	gui->sel_par = calculate_selected_param(mouse_pos);
	if (gui->sel_par < 0)
		gui->sel_par = -1;
	gui->draw_pos.x = 0;
	gui->draw_pos.y = 0;
	return (gui);
}

t_gui	*init_gui_struct(t_data *data)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	gui->cam_ang_change.x = 0;
	gui->cam_ang_change.y = 0;
	gui->pics = data->pics;
	gui->sel_bckg = 0;
	if (gui->sel_bckg < 0)
		gui->sel_bckg = -1;
	gui->objects = data->objects;
	gui->mlx = data->mlx;
	gui->draw_pos.x = 0;
	gui->draw_pos.y = 0;
	gui->obj_count = count_objects(gui->objects);
	data->gui = gui;
	gui->data = data;
	return (gui);
}

int	gui(t_data *data, t_gui *gui, t_pos mouse_pos, int button)
{
	int		mod;

	mod = 1;
	update_gui_struct(data, gui, mouse_pos);
	mod = modify_objects(data, data->gui, button);
	(void)mod;
	draw_gui(data, data->gui);
	conditional_retrace(data, button);
	return (0);
}

int handle_mouse(int button, int x, int y, t_data *data)
{
	t_pos	mouse_pos;

	mouse_pos.x = x;
	mouse_pos.y = y;
	// printf("Mouse button %d pressed at %d, %d\n", button, x, y);
	gui(data, data->gui, mouse_pos, button);
	return (0);
}

int	draw_object_name(t_gui *gui, char *name, int id)
{
	t_mlx	*m;
	t_pos	p;
	char	*id_str;
	char	*s;

	m = gui->mlx;
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	id_str = ft_itoa(id);
	s = ft_strjoin_ff(id_str, name);
	if (!s)
		return (1);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 16, COL_WHITE, s);
	free(s);
	return (0);
}

int	draw_sel_param_bckg(t_gui *gui, int id)
{
	t_mlx	*m;
	t_pos	p;

	(void)m;
	if (id == gui->sel_bckg && gui->sel_par >=1 && gui->sel_par <= 8)
	{
		m = gui->mlx;
		p.x = gui->draw_pos.x;
		p.y = gui->draw_pos.y + 10 + (gui->sel_par * 10);
		mlx_put_image_to_window(m->ptr, m->win_gui, gui->pics->sel_p, p.x, p.y);
	}
	return (0);
}

int	draw_background(t_gui *gui, t_mlx *m, int obj_id)
{
	t_pics	*pics;
	int		x;
	int		y;

	pics = gui->pics;
	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	if (obj_id == gui->sel_bckg)
		mlx_put_image_to_window(m->ptr, m->win_gui, pics->sel, x, y);
	else
		mlx_put_image_to_window(m->ptr, m->win_gui, pics->bckg, x, y);
	draw_sel_param_bckg(gui, obj_id);
	return (0);
}

t_v3	get_pos_sphere(t_sphere *sphere)
{
	t_v3	pos;

	pos.x = sphere->center->x;
	pos.y = sphere->center->y;
	pos.z = sphere->center->z;
	return (pos);
}

t_v3	get_pos_plane(t_plane *plane)
{
	t_v3	pos;

	pos.x = plane->point->x;
	pos.y = plane->point->y;
	pos.z = plane->point->z;
	return (pos);
}

t_v3	get_pos_cylinder(t_cylinder *cylinder)
{
	t_v3	pos;

	pos.x = cylinder->center->x;
	pos.y = cylinder->center->y;
	pos.z = cylinder->center->z;
	return (pos);
}

t_v3	get_rot_plane(t_plane *plane)
{
	t_v3	rot;

	rot.x = plane->normal_vec->x;
	rot.y = plane->normal_vec->y;
	rot.z = plane->normal_vec->z;
	return (rot);
}

t_v3	get_rot_cylinder(t_cylinder *cylinder)
{
	t_v3	rot;

	rot.x = cylinder->normal_vec->x;
	rot.y = cylinder->normal_vec->y;
	rot.z = cylinder->normal_vec->z;
	return (rot);
}

char	*ft_ftoa(float f)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*out;

	tmp1 = ft_itoa((int)f);
	tmp2 = ft_strjoin_ff(tmp1, ".");
	tmp3 = ft_itoa((int)((f - (int)f) * 100));
	out = ft_strjoin_fb(tmp2, tmp3);
	return (out);
}

int	draw_pos_values(t_gui *gui, t_mlx *m, t_v3 pos)
{
	t_v3	p;
	int		x;
	int		y;
	char	*s[3];

	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	p.x = gui->draw_pos.x + pos.x;
	p.y = gui->draw_pos.x + pos.y;
	p.z = gui->draw_pos.x + pos.z;
	s[0] = ft_ftoa(p.x);
	s[1] = ft_ftoa(p.y);
	s[2] = ft_ftoa(p.z);
	mlx_string_put(m->ptr, m->win_gui, x + 50, y + 30, COL_GREY_D, s[0]);
	mlx_string_put(m->ptr, m->win_gui, x + 50, y + 40, COL_GREY_D, s[1]);
	mlx_string_put(m->ptr, m->win_gui, x + 50, y + 50, COL_GREY_D, s[2]);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	return (0);
}

int	draw_pos_names(t_gui *gui)
{
	t_mlx	*m;
	int		x;
	int		y;

	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	m = gui->mlx;
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 30, COL_GREY_L, "POS X");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 40, COL_GREY_L, "POS Y");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 50, COL_GREY_L, "POS Z");
	return (0);
}

int	draw_rot_names(t_gui *gui)
{
	t_mlx	*m;
	int		x;
	int		y;

	m = gui->mlx;
	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 70, COL_GREY_L, "ROT X");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 80, COL_GREY_L, "ROT Y");
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 90, COL_GREY_L, "ROT Z");
	return (0);
}

int	draw_radius(t_gui *gui, t_mlx *m, float radius)
{
	char	*value;
	int		x;
	int		y;

	value = ft_ftoa(radius);
	x = gui->draw_pos.x;
	y = gui->draw_pos.y + 50;
	mlx_string_put(m->ptr, m->win_gui, x + 10, y + 10, COL_GREY_L, "RAD");
	mlx_string_put(m->ptr, m->win_gui, x + 50, y + 10, COL_GREY_D, value);
	free(value);
	return (0);
}

int	draw_cy_ctrls(t_gui *gui, t_cylinder *cylinder, int id)
{
	t_v3		pos_cylinder;
	t_mlx		*m;
	t_pos		p;
	char		*s[2];

	m = gui->mlx;
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	pos_cylinder = get_pos_cylinder(cylinder);
	s[0] = ft_ftoa (cylinder->radius);
	s[1] = ft_ftoa (cylinder->height);
	draw_object_name(gui, " - CYLINDER ", id);
	draw_pos_names(gui);
	draw_pos_values(gui, gui->mlx, pos_cylinder);
	// draw_rot_names(gui);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 60, COL_GREY_L, "WIDTH");
	mlx_string_put(m->ptr, m->win_gui, p.x + 50, p.y + 60, COL_GREY_D, s[0]);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 100, COL_GREY_L, "HGHT");
	mlx_string_put(m->ptr, m->win_gui, p.x + 50, p.y + 100, COL_GREY_D, s[1]);
	free(s[0]);
	free(s[1]);
	return (0);
}

int	draw_rot_values(t_gui *gui, t_mlx *m, t_v3 rot)
{
	t_v3	p;
	int		x;
	int		y;
	char	*s[3];

	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	p.x = gui->draw_pos.x + rot.x;
	p.y = gui->draw_pos.x + rot.y;
	p.z = gui->draw_pos.x + rot.z;
	s[0] = ft_ftoa(rot.x);
	s[1] = ft_ftoa(rot.y);
	s[2] = ft_ftoa(rot.z);
	mlx_string_put(m->ptr, m->win_gui, x + 50, y + 70, COL_GREY_D, s[0]);
	mlx_string_put(m->ptr, m->win_gui, x + 50, y + 80, COL_GREY_D, s[1]);
	mlx_string_put(m->ptr, m->win_gui, x + 50, y + 90, COL_GREY_D, s[2]);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	return (0);
}

int	draw_pl_ctrls(t_gui *gui, t_plane *plane, int id)
{
	t_v3	pos_plane;

	pos_plane = get_pos_plane(plane);
	draw_object_name(gui, " - PLANE ", id);
	draw_pos_names(gui);
	draw_pos_values(gui, gui->mlx, pos_plane);
	draw_rot_names(gui);
	draw_rot_values(gui, gui->mlx, get_rot_plane(plane));
	return (0);
}

int	draw_sp_ctrls(t_gui *gui, t_sphere *sphere, int id)
{
	t_v3		pos_sphere;

	pos_sphere = get_pos_sphere(sphere);
	draw_object_name(gui, " - SPHERE ", id);
	draw_pos_names(gui);
	draw_pos_values(gui, gui->mlx, pos_sphere);
	draw_radius(gui, gui->mlx, sphere->radius);
	return (0);
}

int	count_objects(t_object *objects)
{
	int			count;
	t_object	*obj;

	count = 2;
	obj = objects;
	while (obj)
	{
		count++;
		obj = obj->next;
	}
	return (count);
}

int	calculate_gui_height(int obj_count)
{
	int	height;

	height = 0;
	while (obj_count > 0)
	{
		obj_count -= (GUI_MAX_WIDTH / GUI_EL_WIDTH);
		height += GUI_EL_HEIGHT;
	}
	return (height);
}

int	calculate_gui_width(int obj_count)
{
	int	width;

	width = 0;
	while (obj_count > 0 && width < GUI_MAX_WIDTH)
	{
		obj_count -= 1;
		width += GUI_EL_WIDTH;
	}
	return (width);
}

void	wrap_gui(t_gui *gui)
{
	gui->draw_pos.x += GUI_EL_WIDTH;
	if (gui->draw_pos.x >= GUI_MAX_WIDTH)
	{
		gui->draw_pos.x = 0;
		gui->draw_pos.y += GUI_EL_HEIGHT;
	}
}

void	fill_background(t_gui *gui, t_mlx *m)
{
	int	w;
	int	h;
	int	el_per_row;
	t_pos	p;

	p.y = gui->draw_pos.y;
	p.x = gui->draw_pos.x;
	while (p.x < GUI_MAX_WIDTH)
	{
		mlx_put_image_to_window(m->ptr, m->win_gui, gui->pics->bckg, p.x, p.y);
		p.x += GUI_EL_WIDTH;
	}
}

int	draw_gui_loop(t_gui *gui)
{
	t_object	*current;
	int			obj_id;

	obj_id = 0;
	current = gui->objects;
	while (current)
	{
		obj_id++;
		draw_background(gui, gui->mlx, obj_id);
		if (current->type == SPHERE)
			draw_sp_ctrls(gui, current->object, obj_id);
		else if (current->type == PLANE)
			draw_pl_ctrls(gui, current->object, obj_id);
		else if (current->type == CYLINDER)
			draw_cy_ctrls(gui, current->object, obj_id);
		current = current->next;
		wrap_gui(gui);
	}
	return (0);
}

t_v3	get_light_pos(t_light *light)
{
	t_v3	pos;

	pos.x = light->pos->x;
	pos.y = light->pos->y;
	pos.z = light->pos->z;
	return (pos);
}

t_v3	get_camera_pos(t_camera *camera)
{
	t_v3	pos;

	pos.x = camera->pos->x;
	pos.y = camera->pos->y;
	pos.z = camera->pos->z;
	return (pos);
}

int	draw_light_ctrls(t_light *light, t_gui *gui, t_mlx *m)
{
	t_v3	light_pos;
	t_pos	p;

	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	draw_background(gui, m, gui->obj_count - 1);
	light_pos = get_light_pos(light);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 16, COL_WHITE, "LIGHT");
	draw_pos_names(gui);
	draw_pos_values(gui, gui->mlx, light_pos);
	// gui->draw_pos.x += GUI_EL_WIDTH;
	wrap_gui(gui);
	return (0);
}

int	draw_camera_rotation_values(t_gui * gui)
{
	char	*ang_x;
	char	*ang_y;
	t_mlx	*m;
	t_pos	p;

	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	m = gui->mlx;
	ang_x = ft_itoa(gui->cam_ang_change.x);
	ang_y = ft_itoa(gui->cam_ang_change.y);
	mlx_string_put(m->ptr, m->win_gui, p.x + 50, p.y + 70, COL_GREY_D, ang_x);
	mlx_string_put(m->ptr, m->win_gui, p.x + 50, p.y + 80, COL_GREY_D, ang_y);
	free(ang_x);
	free(ang_y);
	return (0);
}

int	draw_camera_ctrls(t_camera *camera, t_gui *gui, t_mlx *m)
{
	t_v3	camera_pos;
	t_pos	p;
	char	*fov_str;

	draw_background(gui, m, gui->obj_count);
	camera_pos = get_camera_pos(camera);
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 16, COL_WHITE, "CAMERA");
	draw_pos_names(gui);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 60, COL_GREY_L, "FOV");
	fov_str = ft_itoa(camera->fov);
	mlx_string_put(m->ptr, m->win_gui, p.x + 50, p.y + 60, COL_GREY_D, fov_str);
	draw_pos_values(gui, gui->mlx, camera_pos);
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 70, COL_GREY_L, "ANG X");
	mlx_string_put(m->ptr, m->win_gui, p.x + 10, p.y + 80, COL_GREY_L, "ANG Y");
	free(fov_str);
	draw_camera_rotation_values(gui);
	wrap_gui(gui);
	return (0);
}

int	draw_gui(t_data *data, t_gui *gui)
{
	mlx_clear_window(data->mlx->ptr, data->mlx->win_gui);
	draw_gui_loop(gui);
	draw_light_ctrls(data->light, gui, data->mlx);
	draw_camera_ctrls(data->camera, gui, data->mlx);
	fill_background(gui, gui->mlx);
	return (0);
}
