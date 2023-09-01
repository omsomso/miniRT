/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 22:52:43 by kpawlows          #+#    #+#             */
/*   Updated: 2023/08/30 23:56:49 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Returns selected ui element id based on mouse pos
int	find_selected_ui_element(t_data *data, t_pos mouse_pos)
{
	int	obj_selected;
	int	max_horizontal_el;

	obj_selected = 0;
	max_horizontal_el = 0;
	obj_selected = (mouse_pos.x / GUI_EL_WIDTH);
	while (max_horizontal_el < GUI_MAX_WIDTH)
		max_horizontal_el += GUI_EL_WIDTH;
	max_horizontal_el = max_horizontal_el / GUI_EL_WIDTH;
	obj_selected += ((mouse_pos.y / GUI_EL_HEIGHT) * max_horizontal_el);
	if (obj_selected > data->gui->obj_count)
		return (-1);
	return (obj_selected + 1);
}

// Finds object in obj linked list by id, advances the list
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

int	modify_plane_b(t_gui *gui, t_plane *plane, int button, int sel)
{
	if (sel == 5 && button == 5)
	{
		rotate_plane_x(plane, -MOD_ANG);
		plane->pl_ang_offset.x += MOD_ANG;
	}
	else if (sel == 5 && button == 4)
	{
		rotate_plane_x(plane, MOD_ANG);
		plane->pl_ang_offset.x -= MOD_ANG;
	}
	else if (sel == 6 && button == 5)
	{
		rotate_plane_y(plane, -MOD_ANG);
		plane->pl_ang_offset.y += MOD_ANG;
	}
	else if (sel == 6 && button == 4)
	{
		rotate_plane_y(plane, MOD_ANG);
		plane->pl_ang_offset.y -= MOD_ANG;
	}
	else if (sel == 7 && button == 5)
	{
		rotate_plane_z(plane, -MOD_ANG);
		plane->pl_ang_offset.z += MOD_ANG;
	}
	else if (sel == 7 && button == 4)
	{
		rotate_plane_z(plane, MOD_ANG);
		plane->pl_ang_offset.z -= MOD_ANG;
	}
	*plane->normal_vec = normalize(*plane->normal_vec);
	// if (sel_param)
		// return (1);
	return (0);
}

int	modify_plane(t_gui *gui, t_plane *plane, int button, int sel)
{
	int	mod;

	mod = 0;
	if (sel == 1 && button == 4)
		mod = plane->point->x -= MOD_POS;
	else if (sel == 1 && button == 5)
		mod = plane->point->x += MOD_POS;
	else if (sel == 2 && button == 4)
		mod = plane->point->y -= MOD_POS;
	else if (sel == 2 && button == 5)
		mod = plane->point->y += MOD_POS;
	else if (sel == 3 && button == 4)
		mod = plane->point->z -= MOD_POS;
	else if (sel == 3 && button == 5)
		mod = plane->point->z += MOD_POS;
	return (mod += (modify_plane_b(gui, plane, button, sel)));
}

// Returns selected row of an ui element based on mouse_pos.y
int	find_selected_param(t_pos mouse_pos)
{
	float	sel_par;
	float	sel_row;

	sel_row = 0;
	while (sel_row * GUI_EL_HEIGHT < mouse_pos.y)
		sel_row++;
	sel_row--;
	sel_par = (mouse_pos.y - (sel_row * GUI_EL_HEIGHT)) / GUI_EL_PAR_HEIGHT;
	sel_par -= GUI_EL_PAR_OFFSET;
	return (sel_par);
}

int	modify_cylinder_b(t_cylinder *cy, int button, int sel)
{
	if (sel == 5 && button == 5)
	{
		rotate_cylinder_x(cy, -MOD_ANG);
		cy->cy_ang_offset.x += MOD_ANG;
	}
	else if (sel == 5 && button == 4)
	{
		rotate_cylinder_x(cy, MOD_ANG);
		cy->cy_ang_offset.x -= MOD_ANG;
	}
	else if (sel == 6 && button == 5)
	{
		rotate_cylinder_y(cy, -MOD_ANG);
		cy->cy_ang_offset.y += MOD_ANG;
	}
	else if (sel == 6 && button == 4)
	{
		rotate_cylinder_y(cy, MOD_ANG);
		cy->cy_ang_offset.y -= MOD_ANG;
	}
	else if (sel == 7 && button == 5)
	{
		rotate_cylinder_z(cy, -MOD_ANG);
		cy->cy_ang_offset.z += MOD_ANG;
	}
	else if (sel == 7 && button == 4)
	{
		rotate_cylinder_z(cy, MOD_ANG);
		cy->cy_ang_offset.z -= MOD_ANG;
	}
	if (sel == 8 && button == 4)
		cy->height -= MOD_POS;
	else if (sel == 8 && button == 5)
		cy->height += MOD_POS;
	cut_values(&cy->diameter, 100000, 0.01);
	cut_values(&cy->height, 100000, 0.01);
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
	if (sel == 5 && button == 5)
	{
		rotate_camera_x(data->camera, -1);
		gui->cam_ang_offset.x -= 1;
	}
	else if (sel == 5 && button == 4)
	{
		rotate_camera_x(data->camera, 1);
		gui->cam_ang_offset.x += 1;
	}
	else if (sel == 6 && button == 5)
	{
		rotate_camera_y(data->camera, -1);
		gui->cam_ang_offset.y += 1;
	}
	else if (sel == 6 && button == 4)
	{
		rotate_camera_y(data->camera, 1);
		gui->cam_ang_offset.y -= 1;
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

// Modifies object parameters based on user input
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
			mod = modify_plane(gui, obj->object, button, gui->sel_par);
		else if (obj->type == CYLINDER)
			mod = modify_cylinder(obj->object, button, gui->sel_par);
	}
	// if (!mod)
		// printf("modified param %d of object %d\n", sel_par, sel_obj_id);
	return (mod);
}

// Calls generate rays if auto_retrace is on or if right click
void	conditional_retrace(t_data *data, int button)
{
	if (data->auto_retrace)
		generate_rays(data);
	else if (button == 2 || button == -1)
		generate_rays(data);
}

// Updates the gui struct for each ui redraw
t_gui	*update_gui_struct(t_data *data, t_gui *gui, t_pos mouse_pos)
{
	gui->mouse_pos = mouse_pos;
	gui->sel_bckg = find_selected_ui_element(data, mouse_pos);
	if (gui->sel_bckg < 0)
		gui->sel_bckg = -1;
	gui->sel_par = find_selected_param(mouse_pos);
	if (gui->sel_par < 0)
		gui->sel_par = -1;
	gui->draw_pos.x = 0;
	gui->draw_pos.y = 0;
	return (gui);
}

// Inits gui struct
t_gui	*init_gui_struct(t_data *data)
{
	t_gui	*gui;

	gui = malloc(sizeof(t_gui));
	if (!gui)
		return (NULL);
	gui->cam_ang_offset.x = 0;
	gui->cam_ang_offset.y = 0;
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

// Calls relevant ui functions and retraces based on user mouse input
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

// Handles mouse inputs from main window
int handle_mouse(int button, int x, int y, t_data *data)
{
	t_pos	mouse_pos;

	if (y < 0)
		return (0);
	mouse_pos.x = x;
	mouse_pos.y = y;
	if (button == 2)
		gui(data, data->gui, mouse_pos, button);
	return (0);
}

// Handles mouse inputs from gui window
int handle_mouse_gui(int button, int x, int y, t_data *data)
{
	t_pos	mouse_pos;

	if (y < 0)
		return (0);
	mouse_pos.x = x;
	mouse_pos.y = y;
	// printf("Mouse button %d pressed at %d, %d\n", button, x, y);
	gui(data, data->gui, mouse_pos, button);
	return (0);
}

// Draws name on the ui
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
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 16, COL_WHITE, s);
	free(s);
	return (0);
}

// Draws selection highlight on the ui
int	draw_sel_param_bckg(t_gui *gui, t_mlx *m, int id)
{
	t_pos	p;

	if (id == gui->sel_bckg && gui->sel_par >=1 && gui->sel_par <= 8)
	{
		p.x = gui->draw_pos.x;
		p.y = gui->draw_pos.y + 10 + (gui->sel_par * 10);
		mlx_put_image_to_window(m->ptr, m->win_gui, \
		gui->pics->sel_p, p.x, p.y);
	}
	return (0);
}

// Draws background for each object on the ui
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
	draw_sel_param_bckg(gui, gui->mlx, obj_id);
	return (0);
}

// Draws object position names and values
int	draw_rot_data_cam(t_gui * gui, t_mlx *m, t_pos obj_ang_offset)
{
	char	*ang_x;
	char	*ang_y;
	char	*ang_z;
	t_pos	p;

	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	ang_x = ft_itoa(obj_ang_offset.x);
	ang_y = ft_itoa(obj_ang_offset.y);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 70, COL_GREY_L, "ANG X");
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 80, COL_GREY_L, "ANG Y");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 70, COL_GREY_D, ang_x);
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 80, COL_GREY_D, ang_y);
	free(ang_x);
	free(ang_y);
	return (0);
}

// Draws object rotation names and values
int	draw_rot_data(t_gui * gui, t_mlx *m, t_pos obj_ang_offset)
{
	char	*ang_x;
	char	*ang_y;
	char	*ang_z;
	t_pos	p;

	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	ang_x = ft_itoa(obj_ang_offset.x);
	ang_y = ft_itoa(obj_ang_offset.y);
	ang_z = ft_itoa(obj_ang_offset.z);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 70, COL_GREY_L, "ANG X");
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 80, COL_GREY_L, "ANG Y");
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 90, COL_GREY_L, "ANG Z");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 70, COL_GREY_D, ang_x);
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 80, COL_GREY_D, ang_y);
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 90, COL_GREY_D, ang_z);
	free(ang_x);
	free(ang_y);
	free(ang_z);
	return (0);
}

// Draws object position names and values
int	draw_pos_data(t_gui *gui, t_mlx *m, t_v3 pos)
{
	int		x;
	int		y;
	char	*s[3];

	x = gui->draw_pos.x;
	y = gui->draw_pos.y;
	s[0] = ft_ftoa(pos.x);
	s[1] = ft_ftoa(pos.y);
	s[2] = ft_ftoa(pos.z);
	mlx_string_put(m->ptr, m->win_gui, x, y + 30, COL_GREY_L, "POS X");
	mlx_string_put(m->ptr, m->win_gui, x, y + 40, COL_GREY_L, "POS Y");
	mlx_string_put(m->ptr, m->win_gui, x, y + 50, COL_GREY_L, "POS Z");
	mlx_string_put(m->ptr, m->win_gui, x + DM, y + 30, COL_GREY_D, s[0]);
	mlx_string_put(m->ptr, m->win_gui, x + DM, y + 40, COL_GREY_D, s[1]);
	mlx_string_put(m->ptr, m->win_gui, x + DM, y + 50, COL_GREY_D, s[2]);
	free(s[0]);
	free(s[1]);
	free(s[2]);
	return (0);
}

// Gets and draws name and value of sphere radius
int	draw_sp_radius(t_gui *gui, t_mlx *m, float radius)
{
	char	*value;
	t_pos	p;

	value = ft_ftoa(radius);
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y + 50;
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 10, COL_GREY_L, "RAD");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 10, COL_GREY_D, value);
	free(value);
	return (0);
}

// Gets and draws cylinder parameters on ui window
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
	draw_object_name(gui, " CYLINDER ", id);
	draw_pos_data(gui, gui->mlx, pos_cylinder);
	draw_rot_data(gui, gui->mlx, cylinder->cy_ang_offset);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 60, COL_GREY_L, "WIDTH");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 60, COL_GREY_D, s[0]);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 100, COL_GREY_L, "HGHT");
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 100, COL_GREY_D, s[1]);
	free(s[0]);
	free(s[1]);
	return (0);
}

// Gets and draws plane parameters on ui window
int	draw_pl_ctrls(t_gui *gui, t_plane *plane, int id)
{
	draw_object_name(gui, " PLANE ", id);
	draw_pos_data(gui, gui->mlx,  get_pos_plane(plane));
	draw_rot_data(gui, gui->mlx, plane->pl_ang_offset);
	// draw_rot_names(gui, gui->mlx);
	// draw_rot_values(gui, gui->mlx, get_rot_plane(plane));
	return (0);
}

// Gets and draws sphere parameters on gui window
int	draw_sp_ctrls(t_gui *gui, t_sphere *sphere, int id)
{
	draw_object_name(gui, " SPHERE ", id);
	draw_pos_data(gui, gui->mlx, get_pos_sphere(sphere));
	draw_sp_radius(gui, gui->mlx, sphere->radius);
	return (0);
}

// Counts objects for ui (adds 2 for C and L)
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

// Returns ui window height based on modifiable parameters
int	compute_gui_height(int obj_count)
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

// Returns final ui window width based on GUI_MAX_WIDTH
int	compute_gui_width(int obj_count)
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

// Offsets draw_pos to higher y values if x exceeds GUI_MAX_WIDTH
void	wrap_gui(t_gui *gui)
{
	gui->draw_pos.x += GUI_EL_WIDTH;
	if (gui->draw_pos.x >= GUI_MAX_WIDTH)
	{
		gui->draw_pos.x = 0;
		gui->draw_pos.y += GUI_EL_HEIGHT;
	}
}

// Fills background of empty ui space
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
		mlx_put_image_to_window(m->ptr, m->win_gui, gui->pics->empty, p.x, p.y);
		p.x += GUI_EL_WIDTH;
	}
}

// Draws ui elements for each object in data->objects
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
		gui->draw_pos.x += GUI_EL_MARGIN;
		if (current->type == SPHERE)
			draw_sp_ctrls(gui, current->object, obj_id);
		else if (current->type == PLANE)
			draw_pl_ctrls(gui, current->object, obj_id);
		else if (current->type == CYLINDER)
			draw_cy_ctrls(gui, current->object, obj_id);
		current = current->next;
		gui->draw_pos.x -= GUI_EL_MARGIN;
		wrap_gui(gui);
	}
	return (0);
}

// Gets and draws light parameters
int	draw_light_ctrls(t_light *light, t_gui *gui, t_mlx *m)
{
	t_v3	light_pos;
	t_pos	p;


	draw_background(gui, m, gui->obj_count - 1);
	gui->draw_pos.x += GUI_EL_MARGIN;
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	light_pos = get_light_pos(light);
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 16, COL_WHITE, "LIGHT");
	draw_pos_data(gui, gui->mlx, light_pos);
	gui->draw_pos.x -= GUI_EL_MARGIN;
	wrap_gui(gui);
	return (0);
}

// Gets and draws camera parameters
int	draw_camera_ctrls(t_camera *camera, t_gui *gui, t_mlx *m)
{
	t_v3	camera_pos;
	t_pos	p;
	char	*fov_s;

	draw_background(gui, m, gui->obj_count);
	gui->draw_pos.x += GUI_EL_MARGIN;
	p.x = gui->draw_pos.x;
	p.y = gui->draw_pos.y;
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 60, COL_GREY_L, "FOV");
	mlx_string_put(m->ptr, m->win_gui, p.x, p.y + 16, COL_WHITE, "CAMERA");
	fov_s = ft_itoa(camera->fov);
	mlx_string_put(m->ptr, m->win_gui, p.x + DM, p.y + 60, COL_GREY_D, fov_s);
	free(fov_s);
	camera_pos = get_camera_pos(camera);
	draw_pos_data(gui, gui->mlx, camera_pos);
	draw_rot_data_cam(gui, gui->mlx, gui->cam_ang_offset);
	gui->draw_pos.x -= GUI_EL_MARGIN;
	wrap_gui(gui);
	return (0);
}

// Draws ui window
int	draw_gui(t_data *data, t_gui *gui)
{
	mlx_clear_window(data->mlx->ptr, data->mlx->win_gui);
	draw_gui_loop(gui);
	draw_light_ctrls(data->light, gui, data->mlx);
	draw_camera_ctrls(data->camera, gui, data->mlx);
	fill_background(gui, gui->mlx);
	return (0);
}
