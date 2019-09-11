// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <memory>
#include <tchar.h>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <map>
#include <vector>
#include <time.h>

// TODO: reference additional headers your program requires here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "Sounds.h"
#include "Info.h"
#include "Object.h"
#include "Dynamic.h"
#include "Projectile.h"
#include "Enemy.h"
#include "Firearm.h"
#include "Player.h"
#include "Placeable.h"
#include "Turret.h"
#include "Consumable.h"

#include "Shaft.h"
#include "Floor.h"
#include "GameManager.h"

#include "Collision.h"
#include "Draw.h"
#include "EnemySpawn.h"

#include "Clickable.h"
#include "Menu.h"
#include "Upgrade.h"
#include "Global.h"