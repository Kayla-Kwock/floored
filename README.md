# Floored

Floored is a wave-based survival game inspired by the various flash games from the early 2000's. The game plays like a tower defense but with a twist: the enemies can spawn on any one of 5 available floors. Along with upgradable stationary turrets and traps to defend each floor, the player can traverse between them and support any floor using their own weapons. There are 15 waves in total, each wave being harder than the last. Can you survive?

## How to Play
After forking the repo, a pre-compiled version of the game is available at 'Exec/Release/EE205Final.exe'. Once initialized, it may take a while to load. 

You play as the elevator (grey square on the left hand side of the field). Your goal is to ensure that enemies do not deplete your health bar (top of the screen) fully. 

The game is split into 2 phases: prep and combat. In the prep phase, you can build, repair and upgrade your defenses. In the combat phase, you take control of the elevator and begin defending. After all enemies in the wave are defeated, you will return to the prep phase, and move on to the next wave. This continues until you lose or complete all 15 waves. Upon starting the game, you begin in the prep phase.

On the prep phase screen, there are 3 areas of interest: red boxes (turrets), green boxes (equipment/consumable) and the Player Upgrade. Each defense will cost a certain amount of money, which you can get by defeating enemies.

### Turrets/Equipment
These are stationary defenses capable of defending the floor they occupy. By clicking a red or green box, you can either place a defense if there is none present in that box or upgrade it. Certain equipment are destroyable or are one-time use. If this occurs, they change to red and become unusable. You can repair them during any prep phase.

### Player Upgrades
You initially start with only the pistol, but can carry up to 2 different weapons. These weapons are purchased, equipped, and upgraded at the Player Upgrade screen. **After purchasing the weapon of choice, you must equip it by clicking on the weapon again and pressing 'Equip'.** 

## Controls (During Combat Phase Only)
W - Move Elevator Up

S - Move Elevator Down

Mouse 1 (Hold) - Fire Weapon

Mouse 2 - Swap Active Weapon

## Stats
Weapons and defenses have unique stats to determine how they work and interact with the world.
- Level: What level the defense is. Higher levels mean better stats.
- Damage: How much damage the defense will do per shot.
- ROF: Rate of fire. How often the defense will shoot.
- Punch: How many enemies the each shot will damage. Ex: a weapon with punch of 2 will damage 2 enemies.


