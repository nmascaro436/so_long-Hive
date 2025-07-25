/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 08:40:43 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/25 09:57:59 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <fcntl.h> 
# include <stdlib.h>
# include "libft/libft.h"
# include "MLX42/MLX42.h"

# define TILE_SIZE 64

/**
* Linked list to hold map lines before converting to array.
*/
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;
/**
* Represents the map structure.
*/
typedef struct s_map
{
	char	**tiles;
	int		width;
	int		height;
}	t_map;
/**
* Holds textures and images used for rendering.
*/
typedef struct s_textures
{
	mlx_texture_t	*player_texture;
	mlx_texture_t	*wall_texture;
	mlx_texture_t	*floor_texture;
	mlx_texture_t	*collectible_texture;
	mlx_texture_t	*exit_texture;
	mlx_image_t		*player_image;
	mlx_image_t		*wall_image;
	mlx_image_t		*floor_image;
	mlx_image_t		*collectible_image;
	mlx_image_t		*exit_image;
}	t_textures;
/**
 * Represents a movement from one position to another.
 */
typedef struct s_move
{
	int	old_x;
	int	old_y;
	int	target_x;
	int	target_y;
	char	target_tile;
}	t_move;
/**
* Master structure that holds all game state.
*/
typedef struct s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_textures	textures;
	int			player_x;
	int			player_y;
	int			collectibles_left;
	int			move_count;
}	t_game;

// Used for reading the map file line by line
t_list	*new_node(char *line);
void	add_to_end(t_list **head, t_list *new_node);
int		list_size(t_list *head);
void	free_list_nodes(t_list *head);
void	read_lines_cleanup(char *line, t_list *head, int fd);
void	free_partial_map_allocations(t_map *map, int alloc_rows);

// Map handling and validation
t_map	*read_map(const char *filename);
int		validate_map(t_map *map);
void	free_map(t_map *map);
int		path_validation(t_map *map);

// Cleanup and exit 
void	free_all_and_exit(t_game *game, const char *error_message);

// Game initialization and texture management
int		initialize_game(t_game *game, t_map *map);
int		load_textures(t_game *game);
void	cleanup_textures(t_game *game);

// Player setup and movement
int		find_player(t_map *map, int *x, int *y);
void	init_player_position(t_game *game);
void	move_player(t_game *game, int horizontal_move, int vertical_move);
int		count_collectibles(t_map *map);

// Rendering
void	render_map(t_game *game);
void	render_single_tile(t_game *game, int col, int row, char tile);
void	clear_old_position(t_game *game, int col, int row);
void	update_new_position(t_game *game, int col, int row, int collected_item);
void	helper_render(t_game *game, char tile, int row, int col);

// Input handling
void	key_handler(mlx_key_data_t keydata, void *param);

#endif
