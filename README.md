# ENGG1340 Group Project - Jetpack Joyride
## Members
1. Lam Cheuk Yin Bryan
- UID: 3035690696
- Username: Bryan-lam
2. Haris Rashid
- UID: 3035834565
- Username: harisrab

## Gameplay
https://user-images.githubusercontent.com/62747193/167154055-b9fbfadf-18bb-4373-96c3-9474e4164e8b.mp4



## Instructions
Simply Clone the Repo and Execute these lines in CS Server shell.

```shell
make
make main && ./main
```

## Proposal
For the project, we are taking inspiration from one of the most downloaded mobile games **Jetpack Joyride**, to create an endless runner game.

<img src="https://user-images.githubusercontent.com/89774942/159976575-b32d8cad-b627-4b7a-906a-a74efbbed4cb.png" width="200" height="200">


### Game Description
#### Background story
You are an exploited factory worker deprived of decent salary and dignity, working 24/7 under a technological corporate, which expertise in building jetpacks for military use. Under tremendous stress, you have decided to break out of the hierarchal and highly pressurizing environment both mentally and physically, in a revolutionary manner: stealing one of its jetpacks and going for a joyride. There you must traverse through deadly obstacles within the factory's operation, collect upgrades for the jetpack along the way, and see how far you can make it before getting caught!

### Game rules
The player must survive as long as possible, before running into deadly obstacles which result in an instant "game over".

The protagonist is continuously moving forwards. Only his vertical movement can be controlled, by holding the "space" key to blast a jet of plasma downwards, which propels the player upwards. The longer the key is held, the longer the airborne duration, and that the character would fall quickly to the ground once the button is released.

Vertical pipes and machinery are spawned along the way to block the player's direction of travel, which upon collision would cause the player to faint and lose the game. 

Floating powerups are spawned occasionally, and once collected would grant the player additional upgrades depending the following types, for a limited duration of time.

* Berserker: a layer of protective armour providing toughness to breakthrough obstacles upon collision for a given period.
* Flash: a turbo upgrade for the engine which grants immunity and dashes the player forwards for a given period.
* Heart: giving the player an extra life by allowing 1 respawn opportunity after collision 

At the start of each game, players are required to enter their name. At the end of each run, the player score will be displayed in comparison to the highscore of previous players. Scores are attained according to the 1) distance travelled by the player before gameover, and 2) the number of power ups collected.

### Code Requirements
| Requirements | Description |
| --------------- | ------------- |
| 1. Generation of random game sets or events | Obstacles and powerups are randomly spanwed on screen, although the frequency and size of the obstacles will be dynamically assessed for the player's possibility to avoid, with regard to a feasible difficulty |
| 2. Data structures for storing game status | To avoid duplicate games or data recorded for each gameplay, a game class is defined and only 1 game class object would be instantiated to interact with program files. Highscores of all historical players would be stored in a separate text file for reference. |
| 3. Dynamic memory management | To avoid stack overflow, obstacles and powerup objects will be dynamically deleted after a given period of offscreen time. |
| 4. File input/output | Graphical assets of our game are handled by ASCII art, for which the aesthetic design would be stored in a text file. Leaderboard scores would also be stored in a separate file |
| 5. Program codes in multiple files | Various files are responsible for handling different modes in the game. For instance 1 file would be responsible for handling gameplay, another for managing leaderboard scores, and another one for menu displays |

### Development
![image](https://user-images.githubusercontent.com/62747193/161444136-f8faf2c3-d105-479c-ad12-53e2ef4e8199.png)
