### Opengl Plant vs Zombine clone using GFX-framework

This game is a simplified rendition inspired by the popular 2D game Plants vs. Zombies. The game consists of a 3x3 grid where players strategically place turrets (representing plants) of four different colors to defend against randomly spawning hexagonal enemies (representing zombies).
The player strategically position diamond-shaped turrets in one of the three cells on each row. These turrets launch projectiles that move to the right along the row, but only when they face an enemy of the same color. When a hexagon is hit three times, it disappears, however, if a hexagon successfully reaches the end of the screen (the red gate), the player loses one life. Losing three lives results in a game over.

### General Game Rules
##### Placing Diamonds in the Game Scene
The game operates on a color-based system, featuring four types of triplets: diamond-projectile-enemy, with each triplet sharing a base color (e.g., orange, blue, yellow, and purple). In the GUI's top-left corner, players find four slots, each representing a type of diamond. Through a drag & drop process, players select a specific diamond type and place it in a valid game cell with no other diamonds.

Players can only select a diamond type if they have enough resources:

1. Orange diamond: 1 star
2. Blue diamond: 2 stars
3. Yellow diamond: 2 stars
4. Purple diamond: 3 stars
Stars appear randomly on the screen in groups of three. Players select stars by placing the cursor inside and clicking the left mouse button, adding them to their total count.

##### Diamond and Enemy Behavior
At unpredictable intervals, enemies move from the right side of the screen along a randomly chosen row. Each enemy belongs to one of four possible types. If a diamond of the same type is present in one of the three cells on the row, it initiates the launch of projectiles. If no matching diamond is present, the hexagon remains unaffected.

##### GUI
The game features a user-friendly GUI with essential information to assist players:
1. Remaining lives
2. Collected stars
3. Star requirements for each diamond type

##### Framework Used
This game is built on the [gfx-framework](https://github.com/UPB-Graphics/gfx-framework). If you want to explore the graphics framework, check out the repository for more details.
