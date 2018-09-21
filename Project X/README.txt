"Tile?"

This game is very similar in setup and rules to the popular mobile game "2048"

Objective:
	The objective of the game "Tile?" is to slide tiles with numbers (and characters) on them.
They combine to eventually create a tile with the ASCII number of 63, or the tile with the character '?'.
The game's function is to merge two identical numbers, not by their mathematical value, but by their ASCII number.
The game begins with characters '1' and '2' (ASCII numbers 49 and 50, respectively).

Rules:
 - Tile? is played on a square grid (specifically, a 4 x 4 grid). Begin with one tile labeled '1'.
 - To merge tiles, press the arrow keys to move all the tiles in the specified direction.
    - Does not work diagonally (pressing more than two keys at once)
 - Random tiles of '1' or '2' will randomly appear in spaces that are not occupied after EACH press of a direction,
   regardless if the board is already 'all the way' pushed.
 - If there are no more available spaces, then the game ends.
 - When two tiles with the same ASCII number collide, they merge into one tile and the new tile will now
   have the next ASCII number
    - For example, if tiles '5' and '5' touch, they become one tile with ASCII 54, or the character '6'
    - For reference, this is the ASCII legend and points chart
       - '1' = 49 = 1 pointb
       - '2' = 50 = 2 points
       - '3' = 51 = 3 points
       - '4' = 52 = 4 points
       - '5' = 53 = 5 points
       - '6' = 54 = 6 points
       - '7' = 55 = 7 points
       - '8' = 56 = 8 points
       - '9' = 57 = 9 points
       - ':' = 58 = 10 points
       - ';' = 59 = 11 points
       - '<' = 60 = 12 points
       - '=' = 61 = 13 points
       - '>' = 62 = 14 points
       - '?' = 63 = 15 points
 - Scoring:
    - Keep track number of each tile earned
    - Multiply number of tiles by the number of points worth (see legend above for worth)
       - For example, 7 tiles of the '4' tile is 4 x 7 = 28 points earned
    - Total score is the sum of points
