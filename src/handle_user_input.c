/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_user_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 21:51:48 by kpawlows          #+#    #+#             */
/*   Updated: 2023/09/01 22:40:51 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Handles mouse inputs from main window
int	handle_mouse(int button, int x, int y, t_data *data)
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
int	handle_mouse_gui(int button, int x, int y, t_data *data)
{
	t_pos	mouse_pos;

	if (y < 0)
		return (0);
	mouse_pos.x = x;
	mouse_pos.y = y;
	gui(data, data->gui, mouse_pos, button);
	return (0);
}

// Handles key inputs from main window
int	handle_keypress(int key, t_data *data)
{
	move_camera_w_arrows(key, data);
	if (key == KEY_LEFT)
		rotate_camera_y(data->camera, 5.0);
	else if (key == KEY_RIGHT)
		rotate_camera_y(data->camera, -5.0);
	else if (key == KEY_UP)
		rotate_camera_x(data->camera, 5.0);
	else if (key == KEY_DOWN)
		rotate_camera_x(data->camera, -5.0);
	if (key == KEY_ESC)
		quit(data);
	conditional_retrace(data, 0);
	return (0);
}

// Moves camera with arrow keys
void	move_camera_w_arrows(int key, t_data *data)
{
	if (key == KEY_A)
		data->camera->pos->x += 0.2;
	else if (key == KEY_D)
		data->camera->pos->x -= 0.2;
	else if (key == KEY_E)
		data->camera->pos->y -= 0.2;
	else if (key == KEY_Q)
		data->camera->pos->y += 0.2;
	else if (key == KEY_W)
		data->camera->pos->z -= 0.1;
	else if (key == KEY_S)
		data->camera->pos->z += 0.1;
	else if (key == KEY_ENTER && data->auto_retrace == 0)
		data->auto_retrace = 1;
	else if (key == KEY_ENTER && data->auto_retrace == 1)
		data->auto_retrace = 0;
}
