/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmascaro <nmascaro@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:55:48 by nmascaro          #+#    #+#             */
/*   Updated: 2025/07/23 10:47:33 by nmascaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Parses the map file and validates its contents.
 * If loading or validation fails, exits with an error.
 */

static void	parse_and_validate_map(const char *filename, t_game *game)
{
	t_map	*map;

	map = read_map(filename);
	if (!map)
		free_all_and_exit(game, NULL);
	if (!validate_map(map))
	{
		game->map = map;
		free_all_and_exit(game, NULL);
	}
	game->map = map;
	game->collectibles_left = count_collectibles(map);
	game->move_count = 0;
	init_player_position(game);
}

/**
 * Initializes the game environment and runs the game loop.
 * If initialization or texture loading fails, exits with an error.
 */

static void	setup_and_run_game(t_game *game)
{
	if (initialize_game(game, game->map) != 0)
		free_all_and_exit(game, "Error: failed to initialize the game");
	if (load_textures(game) != 0)
		free_all_and_exit(game, "Error: failed to load textures");
	render_map(game);
	mlx_key_hook(game->mlx, key_handler, game);
	mlx_loop(game->mlx);
	cleanup_textures(game);
	mlx_terminate(game->mlx);
	free_map(game->map);
}

/**
 * Checks for the correct number of command-line arguments;
 * initializes the game structure to zero,
 * parses and validates the map file,
 * then sets up and runs the game.
 * Returns 0 on success, 1 on error.
 */

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
	{
		ft_putendl_fd("Error: missing map file argument", 2);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	parse_and_validate_map(argv[1], &game);
	setup_and_run_game(&game);
	return (0);
}
