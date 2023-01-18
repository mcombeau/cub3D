#include "cub3d.h"

// Ex : EA         ./path_to_the_east_texture   test
/**
 *  Get the path of texture
 * 			Steps:
 * 			1) If there are any spaces or tabs, ignore them 
 * 			2) Count in advance the total length of the path for the malloc
 * 			3) Copy the path into the newly malloced var until you encounter a space/tab
 * 			4) Check if there are any alphanum chars (even dots or slashes) after => should it be the case, return NULL
 * 			5) return the path
 * 
 */

static char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' '  && line[len] != '\t'))
		len++;
	path = malloc(len - j + 1);
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

// Ex: "  C        225,30,0"
static int	*get_rgb_colors(char *line) // normalement on a envoyé line + j + 1
{
	char	**rgb_to_convert;
	int		*rgb;
	int		i;

	rgb_to_convert = ft_split(line, ','); 
	// nb : on s'en fout s'il y a des espaces dans les elts splittés vu que le atoi les ignore
	// TODO CHECKER AVEC ESPACES APRES LE NB
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
		return (0);
	i = 0;
	while (rgb_to_convert[i])
	{
		if (i > 2) // cas du test : "C        225,30,0,5,20"
			return (0);
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		i++;
	}
	return (rgb);
}

static int	set_direction_textures(t_textures *texture, char *line, int j)
{
	if (line[j + 2] && ft_isprint(line[j + 2])) // cas où la ligne est : SOU ./path_to_the_south_texture
		return (WRONG_INPUT);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(texture->dir_NO))
		texture->dir_NO = get_texture_path(line, j + 2); // j + 2 pour passer les deux lettres de la dir
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(texture->dir_SO))
		texture->dir_SO = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(texture->dir_WE))
		texture->dir_WE = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(texture->dir_EA))
		texture->dir_EA = get_texture_path(line, j + 2);
	else
		return (WRONG_INPUT);
	return (SUCCESS);
}

static int set_floor_and_ceiling_colors(t_textures *texture, char *line, int j)
{
	if (line[j + 1] && ft_isprint(line[j + 1])) // cas où la ligne est : FLOOR 220,100,0 au lieu de F 220,100,0
		return (WRONG_INPUT);
	if (!texture->ceiling && line[j] == 'C')
		texture->ceiling = get_rgb_colors(line + j + 1);
	else if (!texture->floor && line[j] == 'F')
		texture->floor = get_rgb_colors(line + j + 1);
	else
		return (WRONG_INPUT);
	return (SUCCESS);
}

int	parse_data(t_data *data, t_textures *textures, char **map_infos)
{
	int	i;
	int	j;

	(void) data;
	i = 0;
	while (map_infos[i])
	{
		j = 0;
		// printf("%s\n", map_infos[i]);
		while (map_infos[i][j])
		{
			while (map_infos[i][j] == ' ' || map_infos[i][j] == '\t' || map_infos[i][j] == '\r' // ETAPE 1 : IGNORER LES WHITESPACES
			|| map_infos[i][j] == '\n' || map_infos[i][j] == '\v' || map_infos[i][j] == '\f')
				j++;
			// printf("laligne ap les whitespaces: %s\n", map_infos[i] + j);
			if (ft_isalpha(map_infos[i][j])) // ETAPE 2 : on check s'il y a des chars dans cette ligne, et si oui, s'il y en a 1 ou 2
			{
				// printf("voici le char traité : %c\n", map_infos[i][j]);
				if (map_infos[i][j + 1] && ft_isalpha(map_infos[i][j + 1]))
				{
					if (set_direction_textures(textures, map_infos[i], j) == WRONG_INPUT)
						return (FAILURE);
					break ; // Des que la ligne est traitée, il faut passer à la ligne suivante (i++)
				}	
				else
				{
					if (set_floor_and_ceiling_colors(textures, map_infos[i], j) == WRONG_INPUT)
						return (FAILURE);
					break ;
				}	
			}
			else if (ft_isdigit(map_infos[i][j]))
			{
				if (parse_map_description(data, map_infos, i) == FAILURE) //c'est la qu'on envoie l'adresse du j
					return (FAILURE);
				else
					return (SUCCESS);
			}
			j++;
		}
		i++;
	}
	printf("VOICI LES DONNEES RECUP :\nDirections: NO : %s | SO : %s | WE : %s | EA : %s\n", textures->dir_NO, textures->dir_SO, textures->dir_WE, textures->dir_EA);
	if (textures->floor)
	{
		for (int k = 0; k < 3; k++)
			printf("floor: %d => |%d|\n", k, textures->floor[k]);
	}
	if (textures->ceiling)
	{
		for (int l = 0; l < 3; l++) // PB avec le 0, qui est la "fin" du int * et ne s'imprime pas
			printf("ceiling: %d => |%d|\n", l, textures->ceiling[l]);
	}
	printf("tout est bon!\n");
	return (SUCCESS);
}



// ITERE DANS CHAR **MAP
/*
	STR[I]
	{
		on ignore les whitespaces
		IF On checke les premiers caract :
		si y a deux chars : WE NO SO EA /!\ et que la var correspondante n'a pas deja ete remplie
			Et ca doit etre suivi d'un path (une string sans espaces)
			
			par ex split sur les espaces et on veut un tab de taille 2
		si y a qu'un char : F C


		IF {
			isdigit ? OUI => on the map_infos = true
			{
				on envoie l'adresse de j
				parse_map_description : 
			}
			ligne vide  => break ERROR
		}
		if (!dir || !dir || !floor | !ceiling)
		ERROR
	}
*/