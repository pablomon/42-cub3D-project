score: 102

Useful info for the project:
- cub3d_destroyer to test the parser: https://github.com/Dustin42Codam/cub3d_destroyer
- Setting up a project with minilibx and renderling your first pixels: https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html
- Official minilibx info: https://qst0.github.io/ft_libgfx/man_mlx.html
- Raycasting technique: https://lodev.org/cgtutor/raycasting.html
- Bitmap file header: https://www.youtube.com/watch?v=AoTklZbLKd4
- Checking leaks with valgrind (linux): https://www.valgrind.org/docs/manual/quick-start.html

Some small things to Keep in mind:
Minilibx, ironically, doesn't free it's mallocs. Valgrind will always show some still reachable bytes. The amount depends also on the textures you use.

