#ifndef _STDAFX_H_
#define _STDAFX_H_

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_image.h"
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_primitives.h>
#include "allegro5\\allegro_native_dialog.h"

#include "glm.hpp"

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <random>

#define weak std::weak_ptr
#define shared std::shared_ptr
#define degToRad (ALLEGRO_PI/180)

#define Vec2 glm::vec2
enum AXIS { X_AXIS, Y_AXIS, Z_AXIS };

enum COLOUR { RED, GREEN, BLUE, WHITE, BLACK };
enum OBJECTS { PLAYER, ASTEROID, BULLET, UFO, POWERUP };

#endif