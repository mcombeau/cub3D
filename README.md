# cub3D

<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/cub3de.png" alt="Cub3D 42 project badge"/>
</p>

## Status

Work in progress.

## Usage

Clone the repository including the minilibx submodule:

```shell
git clone --recursive https://github.com/mcombeau/cub3D.git
```

Or:

```shell
git clone https://github.com/mcombeau/cub3D.git
git submodule update --init --recursive
```

To compile:

```shell
cd cub3D && make
```

To run the program:

```shell
./cub3d <map.cub>
```

The program takes a map file as an argument. Maps are available in the `maps` directory. There are good maps which the program should run smoothly with, and bad maps which the program should reject.
For example:

- `./cub3d maps/good/simple_map.cub` should run.

- `./cub3d maps/bad/wrong_filetype.buc` should print an error and abort.


---
Made by aquesada and mcombeau
