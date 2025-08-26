Mandatory part
Program name so_long
Turn in files Makefile, *.h, *.c, maps, textures
Makefile NAME, all, clean, fclean, re
Arguments A map in format *.ber
External functs.
• open, close, read, write,
malloc, free, perror,
strerror, exit
• All functions of the math
library (-lm compiler option,
man man 3 math)
• All functions of the MiniLibX
• gettimeofday()
• ft_printf and any equivalent
YOU coded
Libft authorized Yes
Description You must create a basic 2D game in which a dolphin
escapes Earth after eating some fish. Instead of
a dolphin, fish, and the Earth, you can use any
character, any collectible and any place you want.
Your project must comply with the following rules:
• You must use MiniLibX, using either the version on the school machines or by
installing it using its sources.
• You have to turn in a Makefile which will compile your source files. It must not
relink.
• Your program must take a map description file with the extension .ber as a pa8
So Long And thanks for all the fish!
rameter.


Game
• The player’s goal is to collect all collectibles on the map and then escape by choosing
the shortest possible route.
• The W, A, S, and D keys must be used to move the main character.
• The player should be able to move in these four directions: up, down, left, and
right.
• The player should not be able to move into walls.
• At every move, the current number of movements must be displayed in the shell.
• You have to use a 2D view (top-down or profile).
• The game does not have to be in real time.
• Although the given examples show a dolphin theme, you can create the world you
want.
If you prefer, you can use ZQSD or the arrow keys on your keyboard to
move your main character.

Graphic management
• Your program has to display the image in a window.
• Window management must remain smooth (switching to another window, minimizing, etc.).
• Pressing ESC must close the window and quit the program in a clean way.
• Clicking on the cross on the window’s frame must close the window and quit the
program in a clean way.
• The use of the images of the MiniLibX is mandatory

 Map
• The map has to be constructed with 3 components: walls, collectibles, and free
space.
• The map can be composed of only these 5 characters:
0 for an empty space,
1 for a wall,
C for a collectible,
E for a map exit,
P for the player’s starting position.
Here is a simple valid map:
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
• To be valid, a map must contain 1 exit, 1 starting position and at least 1
collectible.
If the map contains duplicate characters (exit/start), an error
message should be displayed.
• The map must be rectangular.
• The map must be enclosed/surrounded by walls. If it is not, the program must
return an error.
• You must verify if there is a valid path in the map.
• You must be able to parse any kind of map, as long as it respects the above rules.
• Another example of a minimal .ber map:
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
• If any misconfiguration is encountered in the file, the program must exit cleanly,
and return "Error\n" followed by an explicit error message of your choice.

Bonus:
You are allowed to use other functions to complete the bonus part, provided their use
is justified during your evaluation. Be smart!
You will receive extra points if you:
• Make the player lose when they touch an enemy patrol.
• Add some sprite animation.
• Display the movement count directly on screen instead of writing it in the shell


1. Map Handling  ✅

Read map file
Validate map format
Check walls, characters, collectibles, etc.

2. Basic Game Structure   ✅

Create game state struct to store:
Map data
Player position
Collectibles count
Move counter
Initialize MLX42
Create window
Basic error handling

3. Asset Management

Load textures for:
	Walls 
	Player ✅
	Collectibles ✅
	Exit 
	Empty space 
Create texture loading/handling functions

<!-- The workflow is:

Load PNG files → Textures (using texture_manager.c)
Convert Textures → Images (using image_handler.c)
Display Images on screen (which we'll do next) -->

4. Rendering System

Draw map function:
	- Loop through the map array
	- Place correct images based on characters ('1' for walls, '0' for empty, etc.)
Draw player function:
	- Find player position ('P' in map)
	- Place player image at correct coordinates
Draw collectibles:
	- Find collectible positions ('C' in map)
	- Place collectible images
Basic refresh mechanism:
	- Setup MLX loop hooks for rendering
	- Update display when changes occur

5. Player Movement

Handle keyboard input (W, A, S, D) ✅
Collision detection with walls ✅
Move counter -------> UPDATED FROM PRINTF
Display moves in shell


6. Game Logic

Collectible pickup system
Exit condition checking
Win condition (all collectibles + reach exit)


7. Window Management

Handle window closing (X button)
Handle ESC key
Clean exit functionality


8. Memory Management

Free all allocated memory
Handle cleanup on exit
Check for memory leaks


9. Testing & Bug Fixing

Test with different maps
Edge cases
Memory leaks
Error handling


10. Bonus Features (Optional)

Enemy patrols
Sprite animations
On-screen move counter


assets (here will be .png)
ft_printf (it has it's own makefile and header)
get_next_line (it has it's own header)
include (header so_long)
libft (it has it's own makefile and header)
maps (.ber files)
MLX42
src
MAKEFILE



main function:
Initialize game struct & validate map (already correct)
Initialize MLX and window (already correct)
Load textures and images (already correct)
Initialize player position (already correct)
Set up hooks ✅
Initial render ✅


sprite sheet contains 18 frames (6 columns × 3 rows) of the duck character.


if (game->map[new_y][new_x] == 'C')
{
    game->collectibles--;
    game->map[new_y][new_x] = '0';  // Changes the map character to empty space
}
