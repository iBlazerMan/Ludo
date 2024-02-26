# Ludo

<h2>Build Instruction</h2>
The project is developed with Microsoft Visual Studio and Qt 6.6.2 for msvc. To build, load ``` Ludo.sln ``` into Visual Studio, right click on ``` Ludo ``` in the solution explorer and choose "build".
> Qt modules ``` Qt Core ```, ``` Qt GUI ```, ``` Qt Widgets ```, and ``` Qt Multimedia ``` version 6.6.2 (or any other compatible version) are required.

<h2>Overview</h2>  
    Ludo is a board game of 1-4 players, and the player's objective is to move all of their pieces from the start to the final tile before anyone else. This variation includes unique features including jumps, flights, knockbacks, fortresses and more, introducing strategies to the game.  

<h2>Controls</h2>  
    Click on the dice in the center of the board to roll it, and drag a piece that is allowed to move to the available tile to move it.

<h2>Rules and Features</h2>  
    All players start with the same number of pieces(planes) in their hangar. Every round, each player gets to roll a six-sided die once, and they must choose from two options: move a piece from the hanger to the runway, which can only be done if a 6 is rolled, or move a piece that is already airborne(on the board) clockwise the number of spaces indicated by the die. If no pieces are available to move and a 6 is not rolled, the player passes their round without any action.  
    
<h3>Final Approach</h3>  
    When a player's piece has gone around the board and reached the center arrow corresponding to their color, the piece will turn into the arrow and enter the final approach stage. Here, they must throw the exact number needed for the piece to get to the final tile in order to complete the run for that piece. If the number thrown is too low, the piece will approach the final tile as normal. If the number is too high, the piece will bounce back from the final tile for as many surplus moves as there are (e.g. if the piece is 1 tile away from the final tile and a 5 is thrown, the piece will reach the final tile first, and go back 5-1=4 tiles due to the surplus and is now 4 tiles away from the final tile). If the exact number is thrown, the piece's run is completed and is no longer movable. No piece is allowed to enter the center arrow of a different color.  

<h3>Jump</h3>  
    If a player's piece lands on a tile with the same color as the piece, it will jump to the next tile of that color. There are no jumps in the final approach stage. 

<h3>Flight</h3>
    If a player's piece lands on their color's flight tile (the tile with arrows pointing across the board), their piece will take a shortcut and fly to the other side of the flight path.

<h3>Knockback</h3>  
    If a player's piece lands on the same tile as another player's piece (whether by moving, jumping or flying) and the other player only has 1 piece on that tile, their piece is sent back to the hanger and must take off again by rolling a 6 and redo the entire course.

<h3>Fortress</h3>  
    If a player has 2 or more pieces landed on the same tile, that tile becomes a fortress, and no other piece may go over it (either by moving or jumping, flying is still allowed). However, if another player's piece lands on the same tile as the fortress, all pieces including the pieces in the fortress and the piece that landed on it will be sent back to the hanger. 
    <i>Will be implemented in the future.</i>  <br><br>
    
*The game is currently incomplete and still being worked on, and only a multiplayer demo is available. More features and a single-player mode with various levels of difficulty will be implemented in the future.*
    
<h2>artwork credits:</h2>  
    <a href="https://www.flaticon.com/free-icons/dice">Dice icons created by Nsit - Flaticon</a> <br>
    <a href="https://freesound.org/people/simone_ds/sounds/366065/">Move sound effect by simone_ds</a> <br>
    <a href="https://freesound.org/people/Jagadamba/sounds/387669/">Jump sound effect by Jagadamba</a> <br>
    <a href="https://freesound.org/people/XfiXy8/sounds/467282/">Knockback sound effect by XfiXy8</a> <br>
    <a href="https://freesound.org/people/Matt_G/sounds/30351/">Flight sound effect by Matt_G</a>
        
