#pragma once


#include "MenuManager.h"
#include "AudioManager.h"
#include "RenderSystem.h"
#include "Player.h"


class Dust
{
public:
  float x;
  float y;
  float dx;
  float dy;
  int age;
};


class Shootie
{
public:
  float x;
  float y;
  float dx;
  float dy;
  int age;
  float alpha;
};


class BossRushBase
{
public:

  virtual void init() {}
  virtual void draw(RenderSystem&) {}
  virtual void tick(MenuManager& menu, AudioManager& audio) {}
  //
  virtual void keyPress(int key)
  {
    if (key == GLFW_KEY_UP) s_player.up = true;
    else if (key == GLFW_KEY_DOWN) s_player.down = true;
    else if (key == GLFW_KEY_RIGHT) s_player.right = true;
    else if (key == GLFW_KEY_LEFT) s_player.left = true;
  }
  virtual void keyRelease(int key)
  {
    if (key == GLFW_KEY_UP) s_player.up = false;
    if (key == GLFW_KEY_DOWN) s_player.down = false;
    if (key == GLFW_KEY_LEFT) s_player.left = false;
    if (key == GLFW_KEY_RIGHT) s_player.right = false;
  }

  virtual void dustSmash(int x, int y) {}
  virtual void addBullet(Shootie bullet) {}

  static Player s_player;
};
