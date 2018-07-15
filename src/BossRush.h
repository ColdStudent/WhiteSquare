#pragma once


#include "graphics.h"
#include "RenderSystem.h"
#include "MenuManager.h"
#include "AudioManager.h"
#include "Mesh.h"
#include "BossRushBase.h"
#include "Boss.h"


class BossRush : public BossRushBase
{
public:
  BossRush();
  ~BossRush();

  void keyPress(int);
  void keyRelease(int);

  void init();

  void tick(MenuManager& menu, AudioManager& audio);

  void draw(RenderSystem&);

  void dustSmash(int x, int y);
  void addBullet(Shootie bullet);

  int m_screenTransition = 1;

protected:

  bool squareCollide(int x, int y, int w, int h);
  bool circleCollide(int x, int y, int r);

  int m_hits = 0;
  int m_keys = 0;

  int m_record_hits = -1;
  int m_record_keys = -1;

  // Some Meshes
  std::vector<Mesh*> m_meshes;


  // Rhythm/Stage
  bool timing = false;
  bool finished = false;
  int rhythm_timer = 0;

  // Dust effect particles
  std::vector<Dust> m_dusts;
  std::vector<Shootie> m_bullets;

  //
  Boss m_boss;

  //
  int m_hitX;
  int m_hitY;
  int m_hitTimer;
  int m_keyGrabX;
  int m_keyGrabY;
  int m_keyGrabTimer;

  //
  bool m_keyCollected  = false;
  int m_keyX;
  int m_keyY;
  int m_keyCounter = 0;
  int m_keyPos[72] = {
    2, 2,
    2, 3,
    1, 3,
    2, 3,
    3, 3,
    3, 2,
    2, 2,
    2, 1,
    1, 1,
    1, 2,
    2, 2,
    2, 1,
    2, 2,
    2, 3,
    1, 3,
    2, 3,
    3, 3,
    3, 2,
    2, 2,
    2, 3,
    3, 3,
    3, 2,
    2, 2,
    2, 1,
    1, 1,
    1, 2,
    2, 2,
    2, 1,
    2, 2,
    2, 3,
    1, 3,
    2, 3,
    3, 3,
    3, 2,
    2, 2,
    2, 1,
  };
};
