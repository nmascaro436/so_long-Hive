/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:46:04 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/10 11:38:12 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
 * Reads the map file line by line and stores each line in a linked list.
 * Opens the file, reads with get_next_line, creates nodes, and appends them.
 * Returns the head of the linked list containing all map lines,
 * or NULL if an error occurs.
 */
static t_list	*read_lines_into_list(const char *filename)
{
	int		fd;
	char	*line;
	t_list	*head;
	t_list	*node;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	head = NULL;
	line = get_next_line(fd);
	while (line)
	{
		node = new_node(line);
		if (!node)
		{
			free_list_nodes(head);
			return (NULL);
		}
		add_to_end(&head, node);
		line = get_next_line(fd);
	}
	close (fd);
	return (head);
}
/**
 * Converts the linked list of map lines into a t_map structure.
 * Allocates memory for the map struct and its tiles array.
 * Copies lines from the linked list to the array.
 * Sets map height and width (based on first line length).
 * Returns a pointer to the allocated t_map, or NULL on failure.
 */

static t_map	*convert_list_to_map(t_list *list)
{
	t_map	*map;
	int		height;
	int		i;

	height = list_size(list);
	if (height == 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->tiles = malloc(sizeof(char *) * (height + 1));
	if (!map->tiles)
	{
		free(map);
		return (NULL);
	}
	map->height = height;
	i = 0;
	while (list)
	{
		map->tiles[i++] = list->content;
		list = list->next;
	}
	map->width = ft_strlen(map->tiles[0]);
	return (map);
}
/**
 * Reads the map from the given filename and returns a t_map struct.
 * Internally reads lines into a linked list, converts it to array,
 * frees linked list nodes, and returns the map.
 * Returns NULL if reading or allocation fails.
 */

t_map	*read_map(const char *filename)
{
	t_list	*list;
	t_map	*map;

	list = read_lines_into_list(filename);
	if (!list)
	{
		ft_putendl_fd("Error: couldn't read map file or file is empty", 2);
		return (NULL);
	}
	map = convert_list_to_map(list);
	if (!map)
	{
		ft_putendl_fd("Error: couldn't allocate map", 2);
		free_list_nodes(list);
		return (NULL);
	}
	free_list_nodes(list);
	return (map);
}
