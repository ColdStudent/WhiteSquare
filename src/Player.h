#pragma once


#include "MenuManager.h"
#include "AudioManager.h"
#include "RenderSystem.h"


class Player
{
public:
  Player();
  ~Player();

  void init();
  void tick(MenuManager& menu, AudioManager& audio);
  void draw(RenderSystem&);

  // Keys
  bool up;
  bool down;
  bool left;
  bool right;
  // Hero
  int hero_atk = 0;
  int hero_right_leg = 0;
  int hero_left_leg = 0;
  int hero_x = -310;
  int hero_y = -22;
  int m_hitTimer = 0;

  void hit()
  {
    m_hitTimer = 27;
  }

protected:


};
