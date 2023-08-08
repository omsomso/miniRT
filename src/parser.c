/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcullen <fcullen@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 12:31:12 by fcullen           #+#    #+#             */
/*   Updated: 2023/08/07 14:00:59 by fcullen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

// Function To Get Colors
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

// Ambient Light Parser
int	parse_a(char **s, t_data **data)
{
	t_amb	*ambient_light;
	char	**colors;

	ambient_light = malloc(sizeof(t_amb));
	if (!ambient_light || !s[1] || !s[2])
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

	light = malloc(sizeof(t_light));
	if (!light || !s[1] || !s[2] || !s[3])
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
void	add_object(t_object **objects_head, void *object, t_type type)
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

// Sphere Parser
int	parse_sp(char **s, t_object **objects)
{
	t_sphere	*sphere;
	t_v3		*center;
	char		**split;

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
	add_object(objects, sphere, SPHERE);
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
	add_object(objects, plane, PLANE);
	return (0);
}

// Cylinder Parser
int	parse_cy(char **s, t_object **objects)
{
	t_cylinder	*cylinder;
	t_v3		*center;
	t_v3		*normal_vec;
	char		**split;

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
	add_object(objects, cylinder, CYLINDER);
	return (0);
}


// Line Parser Function
int	parse_line(char *line, t_object **objects, t_data *data)
{
	char	**split;
	int		obj_count;

	split = ft_split(line, ' ');
	obj_count = 0;
	// (void)objects;
	if (!split[0])
		return (ft_ptrfree(split), -1);
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

t_object* merge_sort(t_object* head) {
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

// Main Parser Function
// needs check for A, C, L duplicates
int	parser(char *filename, t_object **objects, t_data *data)
{
	int		fd;
	char	*line;

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
	while (line)
	{
		printf("%s\n", line);
		parse_line(line, objects, data);
		line = get_next_line(fd);
	}

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
		obj = obj->next;
	}
	return (0);
}
