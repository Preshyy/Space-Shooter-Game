**PROJECT TITLE: SPACE SHOOTER GAME [C++]**
**DESCRIPTION:** This is a personal project for a space shooter game written in C++. To run it, you only need the code in the .cpp file and the player_records.txt file. The code in the .cpp file can be copied into a blank project and the text file should be in the same file directory
as the .cpp file. This will ensure that the program is able to access the pre-made player records file and display a list of already tested player records. Alternatively, you can simply use the code in the .cpp file as the program is written to be able to create new text files to store 
player records if none can be found. So really all you need to run this program is the .cpp file and an updated Visual Studio version.

The purpose of this game is for the player to survive as long as possible while they evade constantly spawning obstacles that can also be destroyed for points. The more obstacles are destroyed, the more points the player has. These obstacles, when they collide with the player ship will 
cause the game to end as the player will be eliminated. Their score is recorded and stored at each attempt made. 

- Libraries used in this project include the iostream library, which handles the standard input/output functions. The chrono library, which handles some little time management functions, the thread library, for handling the creation and management of threads in the program, the ctime library,
  also for handling time management functions and for time capture functions, the time.h header file for more time management functions, the fstream library to handle input/output from text files, the dos.h header file to handle process interruptions and the window.h header file for console
  dimensions and overall game window construction.

- Dimensions and Cursor management: Window dimension variables are initialised with properties like screen width, screen height gap size and menu width. These and the other defined variables help set the stage on which the game is constructed upon. An array is then used to create a basic visual
  of the player ship; more variables like the ship positions are defined with arrays as well. A struct is used to define a player class, which is made public by default, and assigned the necessary properties for the player. gotoxy functions are also defined as well, to take two input parameters
  for x-y coordinate values. Next, a function is defined to make the cursor invisible as the game begins. Following this, a function to define the game's borders is made and initiated. FOR loops are used to create visuals on what the game's borders will look like with all necessary dimensions present.

- Game Characters: Starting from line 88, functions are made to define and create some of the game characters. The drawEnemy function is to create the obstacles that will spawn throughout the game, and the next function generates these obstacles at random intervals throughout the gameplay process.
  The eraseEnemy function creates the instance for deletion when an obstacle is shot by the player. This ensures that the obstacles are erased when they come in contact with bullets from the player. A reset function is also defined to make sure that the obstacles are erased and respawned if they are
  not destroyed by the player but they manage to reach the opposite end of the game's borders.  
 
- Bullet Generation/Mechanics: The next pair of functions are for the player bullets and their mechanics. The genBullet function generates the bullets for the player ship and the moveBullet function manages the bullet path after it is shot from the player ship. The drawBullet function is to create
  what the bullet will look like visually when shot from the player. The eraseBullet function erases the bullets when they hit an obstacle and the resetBullets function erases the bullets if they do not hit an obstacle and make it to the opposite end of the game's borders. 

- Player spawn/Collision mechanics: The next few functions are for the player spawn mechanics. The drawShip function constructs the player ship at the start of the game and the eraseShip function deletes the player ship when called. These functions are also manipulated to account for the player movement
  when the corresponding key bindings are pressed so that when it moves left or right, it appears on the left or right and is erased from its previous position. The playerCollision function checks for collisions from the player's ship and the obstacles. This makes sure that when the player ship collides with
  an obstacle, the player ship is eliminated and the game ends at the necessary function calls in the main function. The collisionDetector function ensures that the obstacles are destroyed when hit by bullets from the player ship. 

- Score Management Mechanics/Instructions: The next few functions are to manage the score calculations and display the menu instructions. The updateScore function displays a score tab on the right of the game screen and this score is updated as the player eliminates obstacles. The instructions function
  displays a small pocket menu at the right side of the game window. This menu shows the basic game control instructions for the player to reference at any point of the game. 

- Time Management: The next few functions are to calculate the time spent by each play sequence. When a player starts the game, the startTimer function initiates a countdown measured in milliseconds and the stopTimer function ends this time when the game ends. The calculateTimeElapsed function calculates
  the time elapsed and converts this recorded time from milliseconds to seconds to be stored with the player data in the records text file. 

- Game Over Mechanics: The next function is to initiate a display when the game is over. This function shows a small user friendly display signalling the end of the game as well as showing the player data. The time elapsed previously calculated is shown as well as the player's score. A prompt is also
  displayed to collect input from the user to return the game back to the main menu. 

- Player Record Management: The next functions are to manage the player records. The savePlayerRecord function is there to collect all of the player data and save it to a text file. If there is no existing text file, this function makes sure to create one and add every collected data to this file. The data
  collected are the player's name, the player's high score and the time elapsed. This function also ensures that only the highest score of every player is recorded, so if a player plays more than once, only their highest score is recorded and saved. The displayHighScore function is to display all the high score
  data collected by the game. A display format is constructed to have the scores displayed in an orderly fashion and every data recorded by the game is displayed. 

- Loading Screen Mechanics: The next function is for the loading screen at the start of the game. This function is where this loading screen is constructed and its animation is made. Friendly prompts are displayed as the animation runs, and a prompt to have the user interact by pressing any key to continue is
  displayed on the screen at the end of the loading animation. 

- Gameplay Mechanics: The next function is where it all comes together. All the other functions are called here as the gameplay itself is constructed. The menu on the right side of the game screen showing the controls are also defined here as well as the key bindings for the player ship movement. All of the
  mechanics are set up and put together in this function, with all the other necessary functions called and initiated as necessary. The main function is then defined after this showing the very first menu as this program is executed. Three main options are given: 1. Start Game 2. Instructions 3. High Scores 4. Quit,
  and each option is defined to have their corresponding parameters with the necessary functions called when selected.

This program was written entirely with C++ and the IDE used was Visual Studio (not Visual Studio Code). My learning objectives fulfilled with this project include learning how to set up and  manipulate game mechanics and to gain an understanding of the complexities behind programming a video game with C++.  

**CREDITS:** YouTube, Google.
**CONTACT:** Email: precioussunday@my.smcccd.edu
**KNOWN ISSUES:** None were discovered at the completion of this project. Ensure that you are using the latest version of Microsoft Visual Studio and it should run seamlessly. Please refer to my email should you have any questions, encounter any issues or would like to offer suggestions. 
**TIMESTAMP:** 02/03/2024 || 12:59 AM (PST)


