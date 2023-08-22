/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpawlows <kpawlows@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:31:12 by fcullen           #+#    #+#             */
/*   Updated: 2023/08/22 20:50:48 by kpawlows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Function gets colors from char array and frees array
int	get_color(t_color *color, char **s)
{
	int	i;

	i = 0;
	if (!s[0] || !s[1] || !s[2])
		return (1);
	color->r = ft_atoi(s[0]);
	color->g = ft_atoi(s[1]);
	color->b = ft_atoi(s[2]);
	ft_ptrfree(s);
	return (0);
}

// Function Returns Pointer to 3D Vector from char Array + Frees Array
t_v3	*get_vec(char **s)
{
	t_v3	*vector;

	if (!s[0] || !s[1] || !s[2])
		return (NULL);
	vector = malloc(sizeof(t_v3));
	if (!vector)
		return (NULL);
	vector->x = ft_atof(s[0]);
	vector->y = ft_atof(s[1]);
	vector->z = ft_atof(s[2]);
	ft_ptrfree(s);
	return (vector);
}

int	check_a(char **s)
{
	float		ratio;
	static int	count = 0;

	count++;
	if (ft_ptrcount(s) != 3 || count > 1)
	{
		write(2, "Error: Ambient light parameters invalid\n", 40);
		return (1);
	}
	if (!s[1] || !s[2])
	{
		write(2, "Error: Ambient light parameters missing\n", 40);
		return (1);
	}
	ratio = ft_atof(s[1]);
	if (ratio < 0 || ratio > 1)
	{
		write(2, "Error: Ambient light ratio must be between 0 and 1\n", 51);
		return (1);
	}
	if (check_color(s[2]))
		return (1);
	return (0);
}

int	check_pl(char **s)
{
	if (!s[1] || !s[2] || !s[3])
	{
		write(2, "Error: Plane parameters missing\n", 33);
		return (1);
	}
	if (ft_ptrcount(s) != 4 || check_pos(s[1]))
	{
		write(2, "Error: Plane parameters invalid\n", 33);
		return (1);
	}
	if (check_color(s[3]))
		return (1);
	if (check_normal(s[2]))
		return (1);
	return (0);
}

int	check_normal(char *s)
{
	t_v3	*norm;
	int		err;

	err = 0;
	norm = get_vec(ft_split(s, ','));
	if (norm->x < -1 || norm->x > 1)
		err = 1;
	if (norm->y < -1 || norm->y > 1)
		err = 1;
	if (norm->z < -1 || norm->z > 1)
		err = 1;
	free(norm);
	if (err == 1)
	{
		write(2, "Error: Camera normal vector must be between -1 & 1\n", 51);
		return (1);
	}
	return (0);
}

int	check_l(char **s)
{
	static int	count = 0;

	count++;
	if (!s[1] || !s[2] || ft_ptrcount(s) > 4 || count > 1)
	{
		write(2, "Error: Light parameters invalid\n", 33);
		return (1);
	}
	if (ft_atof(s[2]) < 0 || ft_atof(s[2]) > 1)
	{
		write(2, "Error: Light brightness must be between 0 and 1\n", 48);
		return (1);
	}
	if (check_pos(s[1]))
		return (1);
	if (s[3])
	{
		if (check_color(s[3]))
			return (1);
	}
	return (0);
}

int	check_c(char **s)
{
	int			fov;
	static int	count = 0;

	count++;
	if (count > 1 || ft_ptrcount(s) != 4 || s[1] && check_pos(s[1]))
	{
		write(2, "Error: Camera parameters invalid\n", 33);
		return (1);
	}
	if (!s[1] || !s[2] || !s[3])
	{
		write(2, "Error: Camera parameters missing\n", 33);
		return (1);
	}
	fov = ft_atoi(s[3]);
	if (fov < 0 || fov > 180)
	{
		write(2, "Error: Camera FOV must be between 0 and 180\n", 45);
		return (1);
	}
	if (check_normal(s[2]))
		return (1);
	return (0);
}

// Ambient Light Parser
int	parse_a(char **s, t_data **data)
{
	t_amb	*ambient_light;
	char	**colors;

	if (check_a(s))
		return (1);
	ambient_light = malloc(sizeof(t_amb));
	if (!ambient_light)
		return (1);
	ambient_light->ratio = ft_atof(s[1]);
	colors = ft_split(s[2], ',');
	get_color(&(ambient_light->color), colors);
	(*data)->ambient_light = ambient_light;
	ft_ptrfree(s);
	return (0);
}

// Camera Parser
int	parse_c(char **s, t_data **data)
{
	t_camera	*camera;
	char		**split;

	if (check_c(s))
		return (1);
	camera = malloc(sizeof(t_camera));
	if (!camera || !s[1] || !s[2] || !s[3])
		return (1);
	split = ft_split(s[1], ',');
	camera->pos = get_vec(split);
	split = ft_split(s[2], ',');
	camera->normal_vec = get_vec(split);
	camera->fov = ft_atoi(s[3]);
	(*data)->camera = camera;
	ft_ptrfree(s);
	return (0);
}

// Light Parser
int	parse_l(char **s, t_data **data)
{
	t_light	*light;
	char	**split;

	if (check_l(s))
		return (1);
	light = malloc(sizeof(t_light));
	if (!light || !s[1] || !s[2])
		return (1);
	split = ft_split(s[1], ',');
	light->pos = get_vec(split);
	if (!light->pos)
		return (1);
	light->brightness = ft_atof(s[2]);
	split = ft_split(s[3], ',');
	get_color(&(light->color), split);
	(*data)->light = light;
	ft_ptrfree(s);
	return (0);
}

// Free Sphere Object
void	free_sp(void *object)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)object;
	free(sphere->center);
	free(sphere);
}

// Free Plane Object
void	free_pl(void *object)
{
	t_plane	*plane;

	plane = (t_plane *)object;
	free(plane->normal_vec);
	free(plane->point);
	free(plane);
}

// Free Cylinder Object
void	free_cy(void *object)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)object;
	free(cylinder->normal_vec);
	free(cylinder->center);
	free(cylinder);
}

// Object Deletion
void	free_objects(t_object *objects_head)
{
	t_object	*current;

	current = objects_head;
	while (current)
	{
		current = objects_head->next;
		if (objects_head->type == SPHERE)
			free_sp(objects_head);
		if (objects_head->type == PLANE)
			free_pl(objects_head);
		if (objects_head->type == CYLINDER)
			free_cy(objects_head);
	}
	free(current);
}

// Free A, C and L
void	free_acl(t_amb *ambient_light, t_camera *camera, t_light *light)
{
	free(ambient_light);
	free(camera);
	free(light);
}

void	free_data(t_data *data)
{
	free_objects(data->objects);
	free_acl(data->ambient_light, data->camera, data->light);
}

// Object Creation
void	add_object(t_object **objects_head, void *object, t_type type, char **s)
{
	t_object	*current;
	t_object	*new_object;

	new_object = malloc(sizeof(t_object));
	if (!new_object)
		return ;
	new_object->object = object;
	new_object->type = type;
	new_object->ambient_coefficient = 0.2;
	new_object->diffuse_coefficient = 0.9;
	new_object->next = NULL;
	new_object->distance = INFINITY;
	new_object->mirror = false;

	if (!s[4])
	{
		new_object->check = false;
		new_object->mirror = false;
	}
	else if (s[4] && ft_atoi(s[4]) == 1)
	{
		new_object->check = true;
		if (s[5] && ft_atoi(s[5]) == 1)
				new_object->mirror = true;
	}

	if (*objects_head == NULL)
			*objects_head = new_object;
	else
	{
		current = *objects_head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_object;
	}
}

// Returns 1 if string has invalid number (for color & pos)
int	ch_nb(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]) && !ft_isspace(s[i]))
		{
			if (!(s[i] == '.' || s[i] == '-' || s[i] == '+'))
				return (1);
		}
		i++;
	}
	return (0);
}

// Returns 1 if color is invalid
int	check_color(char *color)
{
	int		err;
	char	**col;

	col = ft_split(color, ',');
	err = 0;
	if (!col || !col[0] || !col[1] || !col[2] || ft_ptrcount(col) != 3)
	{
		write(2, "Error: Color parameters invalid\n", 32);
		return (1);
	}
	else if (ch_nb(col[0]) || ft_atoi(col[0]) < 0 || ft_atoi(col[0]) > 255)
		err = 1;
	else if (ch_nb(col[1]) || ft_atoi(col[1]) < 0 || ft_atoi(col[1]) > 255)
		err = 1;
	else if (ch_nb(col[2]) || ft_atoi(col[2]) < 0 || ft_atoi(col[2]) > 255)
		err = 1;
	if (err == 1)
	{
		write(2, "Error: Color parameters must be\
		numbers between 0 & 255\n", 57);
		free(col);
		return (1);
	}
	free(col);
	return (0);
}

// Returns 1 if position is missing or invalid
int	check_pos(char *position)
{
	char **pos;

	pos = ft_split(position, ',');
	if (!pos || !pos[0] || !pos[1] || !pos[2] || ft_ptrcount(pos) != 3)
	{
		write(2, "Error: Object position coordinates invalid\n", 43);
		ft_ptrfree(pos);
		return (1);
	}
	else if (ch_nb(pos[0]) || ch_nb(pos[1]) || ch_nb(pos[2]))
	{
		write(2, "Error: Object position coordinates must be numbers\n", 51);
		ft_ptrfree(pos);
		return (1);
	}
	ft_ptrfree(pos);
	return (0);
}

// Returns 1 if sp data is missing or invalid
int	check_sp(char **s)
{
	if (!s[1] || !s[2] || !s[3])
	{
		write(2, "Error: Sphere parameters invalid\n", 33);
		return (1);
	}
	if (ch_nb(s[2]) || ft_atof(s[2]) <= 0)
	{
		write(2, "Error: Sphere diameter must be a positive number\n", 49);
		return (1);
	}
	if (check_pos(s[1]))
		return (1);
	if (check_color(s[3]))
		return (1);
	return (0);
}

// Returns 1 if cy data is missing or invalid
int	check_cy(char **s)
{
	if (!s[1] || !s[2] || !s[3] || s[4] || ft_ptrcount(s) != 5)
	{
		write(2, "Error: Cylinder parameters invalid\n", 35);
		return (1);
	}
	if (ch_nb(s[2]) || ft_atof(s[2]) <= 0)
	{
		write(2, "Error: Cylinder diameter must be a positive number\n", 51);
		return (1);
	}
	if (ch_nb(s[3]) || ft_atof(s[3]) <= 0)
	{
		write(2, "Error: Cylinder height must be a positive number\n", 49);
		return (1);
	}
	if (check_pos(s[1]))
		return (1);
	if (check_color(s[4]))
		return (1);
	return (0);
}

// Sphere Parser
int	parse_sp(char **s, t_object **objects)
{
	t_sphere	*sphere;
	t_v3		*center;
	char		**split;

	if (check_sp(s))
		return (1);
	sphere = malloc(sizeof(t_sphere));
	center = malloc(sizeof(t_v3));
	if (!sphere || !center)
		return (1);
	sphere->center = center;
	split = ft_split(s[1], ',');
	sphere->center = get_vec(split);
	if (!sphere->center)
		return (1);
	sphere->diameter = ft_atof(s[2]);
	sphere->radius = sphere->diameter / 2;
	split = ft_split(s[3], ',');
	get_color(&(sphere->color), split);
	add_object(objects, sphere, SPHERE, s);
	return (0);
}

// Plane Parser
int	parse_pl(char **s, t_object **objects)
{
	t_plane		*plane;
	t_v3		*point;
	t_v3		*normal_vec;
	char		**split;

	plane = malloc(sizeof(t_plane));
	point = malloc(sizeof(t_v3));
	normal_vec = malloc(sizeof(t_v3));
	if (!plane || !point || !normal_vec)
		return (1);
	split = ft_split(s[1], ',');
	plane->point = get_vec(split);
	split = ft_split(s[2], ',');
	plane->normal_vec = get_vec(split);
	if (!plane->point || !plane->normal_vec)
		return (1);
	split = ft_split(s[3], ',');
	get_color(&(plane->color), split);
	add_object(objects, plane, PLANE, s);
	return (0);
}

// Cylinder Parser
int	parse_cy(char **s, t_object **objects)
{
	t_cylinder	*cylinder;
	t_v3		*center;
	t_v3		*normal_vec;
	char		**split;

	if (check_cy(s))
		return (1);
	cylinder = malloc(sizeof(t_cylinder));
	center = malloc(sizeof(t_v3));
	normal_vec = malloc(sizeof(t_v3));
	if (!cylinder || !center || !normal_vec)
		return (1);
	split = ft_split(s[1], ',');
	cylinder->center = get_vec(split);
	split = ft_split(s[2], ',');
	cylinder->normal_vec = get_vec(split);
	if (!cylinder->center || !cylinder->normal_vec)
		return (1);
	cylinder->diameter = ft_atoi(s[3]);
	cylinder->radius = cylinder->diameter / 2;
	cylinder->height = ft_atoi(s[4]);
	split = ft_split(s[5], ',');
	get_color(&(cylinder->color), split);
	add_object(objects, cylinder, CYLINDER, s);
	return (0);
}

// returns 1 if line is only spaces, tabs etc
int	line_isspace(char *line)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	while (line[i])
	{
		if (ft_isspace(line[i]))
			space++;
		i++;
	}
	if (space == i)
		return (1);
	return (0);
}

// Replaces all tabs, multiple spaces etc with single space
char	*line_fixspace(char *line)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	j = 0;
	newline = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!newline)
		return (NULL);
	while (line[i])
	{
		if (ft_isspace(line[i]))
			newline[j] = ' ';
		else
			newline[j] = line[i];
		i++;
		j++;
	}
	newline[j] = '\0';
	free(line);
	return (newline);
}

// Returns 0 if name starts with a valid identifier or line is empty
int	check_line(char *line, char *name)
{
	if (line_isspace(line))
		return (0);
	if (!ft_strncmp("A", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("C", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("L", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("sp", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("pl", name, ft_strlen(name)))
		return (0);
	else if (!ft_strncmp("cy", name, ft_strlen(name)))
		return (0);
	return (1);
}

// Parse Ambient, Camera and Light
int	parse_acl(char **s, t_data **data)
{
	if (!s[0])
		return (1);
	if (!ft_strncmp("A", s[0], ft_strlen(s[0])))
	{
		if (parse_a(s, data))
			return (1);
	}
	else if (!ft_strncmp("C", s[0], ft_strlen(s[0])))
	{
		if (parse_c(s, data))
			return (1);
	}
	else if (!ft_strncmp("L", s[0], ft_strlen(s[0])))
	{
		if (parse_l(s, data))
			return (1);
	}
	return (0);
}

// Parse Sphere, Plane and Cylinder
int	parse_spplcy(char **s, t_object **objects)
{
	if (!ft_strncmp("sp", s[0], ft_strlen(s[0])))
	{
		if (parse_sp(s, objects))
			return (1);
	}
	else if (!ft_strncmp("pl", s[0], ft_strlen(s[0])))
	{
		if (parse_pl(s, objects))
			return (1);
	}
	else if (!ft_strncmp("cy", s[0], ft_strlen(s[0])))
	{
		if (parse_cy(s, objects))
			return (1);
	}
	return (0);
}

// Line Parser Function
int	parse_line(char *line, t_object **objects, t_data *data)
{
	char	**split;
	int		obj_count;

	split = ft_split(line, ' ');
	obj_count = 0;
	if (!split[0])
		return (ft_ptrfree(split), -1);
	if (check_line(line, split[0]))
	{
		write(2, "Error: Invalid identifier : ", 28);
		ft_putendl_fd(split[0], 2);
		return (1);
	}
	// if (parse_acl(split, &data) || parse_spplcy(split, objects))
	// 	return (ft_ptrfree(split), 1);
	if (!ft_strncmp("A", split[0], ft_strlen(split[0])))
	{
		if (parse_a(split, &data))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("C", split[0], ft_strlen(split[0])))
	{
		if (parse_c(split, &data))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("L", split[0], ft_strlen(split[0])))
	{
		if (parse_l(split, &data))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("sp", split[0], ft_strlen(split[0])))
	{
		if (parse_sp(split, objects))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("pl", split[0], ft_strlen(split[0])))
	{
		if (parse_pl(split, objects))
			return (ft_ptrfree(split), 1);
	}
	else if (!ft_strncmp("cy", split[0], ft_strlen(split[0])))
	{
		if (parse_cy(split, objects))
			return (ft_ptrfree(split), 1);
	}
	return (0);
}

// Merge sort objects by distance
t_object* sorted_merge(t_object* a, t_object* b)
{
	t_object* result = NULL;

	if (!a)
		return b;
	else if (!b)
		return a;

	// Pick the smaller distance and recur
	if (a->distance <= b->distance)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return result;
}

void front_back_split(t_object* source, t_object** front_ref, t_object** back_ref)
{
	t_object* fast;
	t_object* slow;

	if (source == NULL || source->next == NULL)
	{
		*front_ref = source;
		*back_ref = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;

		while (fast != NULL)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front_ref = source;
		*back_ref = slow->next;
		slow->next = NULL;
	}
}

t_object* merge_sort(t_object* head)
{
    if (!head || !head->next) return head;

    t_object* a;
    t_object* b;
    front_back_split(head, &a, &b);

    a = merge_sort(a);
    b = merge_sort(b);

    return sorted_merge(a, b);
}

double compute_distance(t_v3 origin, t_object *obj)
{
	t_v3 *object_point;

	switch (obj->type)
	{
	case SPHERE:
		object_point = ((t_sphere *)obj->object)->center;
		break;
	case PLANE:
		object_point = ((t_plane *)obj->object)->point;
		break;
	case CYLINDER:
		object_point = ((t_cylinder *)obj->object)->center;
		break;
	default:
		return INFINITY;
	}

	return distance_to_point(origin, *object_point);
}

void sort_objects_by_distance(t_v3 origin, t_object **head)
{
	t_object *temp = *head;

	// Compute the distances for each object in the list
	while (temp)
	{
		temp->distance = compute_distance(origin, temp);
		temp = temp->next;
	}
	// Use merge sort to sort the list based on the computed distances
	*head = merge_sort(*head);
}

int	check_scene(t_data *data)
{
	if (!data->ambient_light)
	{
		write(2, "Error: No ambient light\n", 25);
		return (1);
	}
	if (!data->camera)
	{
		write(2, "Error: No camera\n", 17);
		return (1);
	}
	if (!data->light)
	{
		write(2, "Error: No light\n", 16);
		return (1);
	}
	return (0);
}

int	init_scene(t_data *data)
{
	data->ambient_light = NULL;
	data->camera = NULL;
	data->light = NULL;
	// data->objects = NULL;
	return (0);
}

// Main Parser Function
// needs check for A, C, L duplicates
int	parser(char *filename, t_object **objects, t_data *data)
{
	int		fd;
	char	*line;

	init_scene(data);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (fd);
	line = get_next_line(fd);
	*objects = NULL;
	if (!line)
	{
		write(1, "Scene file empty\n", 17);
		return (-1);
	}
	line = line_fixspace(line);
	while (line)
	{
		printf("%s\n", line);
		if (parse_line(line, objects, data))
		{
			write(1, "Parsing error\n", 14);
			free(line);
			return (-1);
		}
		free(line);
		line = get_next_line(fd);
	}

	if (check_scene(data))
		return (-1);
	sort_objects_by_distance(*data->camera->pos, &(*objects));
	printf("Parsing Done!\n");
	printf("The camera center's coordinates are: %f, %f, %f\n", data->camera->pos->x, data->camera->pos->y, data->camera->pos->z);
	printf("The camera orientation is: %f, %f, %f\n", data->camera->normal_vec->x, data->camera->normal_vec->y, data->camera->normal_vec->z);
	t_object *obj = data->objects;
	
	while (obj != NULL)
	{
		if (obj->type == SPHERE)
		{
			t_sphere *sphere = (t_sphere*)obj->object;
			printf("The sphere center's coordinates are: %f, %f, %f\n", sphere->center->x, sphere->center->y, sphere->center->z);
			// printf("Diameter = %f\n", sphere->diameter);
			// printf("Sphere color.r = %f\n", sphere->color.r);
		}
		else if (obj->type == PLANE)
		{
			t_sphere *plane = (t_sphere*)obj->object;
			printf("The plane's coordinates are: %f, %f, %f\n", plane->center->x, plane->center->y, plane->center->z);
			// printf("Diameter = %f\n", sphere->diameter);
			// printf("Sphere color.r = %f\n", sphere->color.r);
		}
		obj = obj->next;
	}
	return (0);
}
