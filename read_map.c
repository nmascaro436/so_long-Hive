/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 09:46:04 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/19 11:26:08 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Removes newline character from a string if present.
 */
static void	remove_newline(char *str)
{
	size_t	len;

	if (!str)
		return ;
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
}
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
		remove_newline(line);
		node = new_node(line);
		if (!node)
		{
			read_lines_cleanup(line, head, fd);
			return (NULL);
		}
		add_to_end(&head, node);
		line = get_next_line(fd);
	}
	close (fd);
	return (head);
}
/**
 * Allocates memory for a t_map structure and its tiles array.
 * Sets height based on the size of the input list, and
 * width based on the length of the first line.
 * Returns NULL on allocation failure or if list is empty,
 * pointer to the allocated t_map on success.
 */
static t_map	*allocate_map(t_list *list)
{
	int	height;
	t_map	*map;

	height = list_size(list);
	if (height == 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->tiles = malloc(sizeof(char *) * height);
	if (!map->tiles)
	{
		free(map);
		return (NULL);
	}
	map->height = height;
	map->width = ft_strlen(list->content);
	return (map);
}
/**
 * Converts the linked list of map lines into a t_map structure.
 * Duplicates each line in the list into the map's tiles array.
 * On allocation failure, frees any allocated memory and
 * returns NULL.
 * Returns a pointer to the allocated t_map, or NULL on failure.
 */
static t_map	*convert_list_to_map(t_list *list)
{
	t_map	*map;
	int		i;

	map = allocate_map(list);
	if (!map)
		return (NULL);
	i = 0;
	while (list && i < map->height)
	{
		map->tiles[i] = ft_strdup(list->content);
		if (!map->tiles[i])
		{
			free_partial_map_allocations(map, i);
			return (NULL);
		}
		list = list->next;
		i++;
	}
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