#pragma once


#include "RenderSystem.h"
#include "Mesh.h"
#include "BossRushBase.h"


class Boss
{
public:

  Boss();
  ~Boss();

  void init();

  void reset();

  void start();

  void update(BossRushBase&);

  void draw(RenderSystem&);

  int x;
  int y;
  int pineapple_x;
  int pineapple_y;
  int pineapple_x2;
  int pineapple_y2;

  bool m_breath_attack;
  int m_breath_x;

  std::vector<Shootie> m_bananas;

protected:

  void actionManager();

  int m_timer;

  bool m_intro;
  bool m_walking;
  bool m_smash_attack;
  bool m_lifting;
  bool m_shooting;
  bool m_transition;
  int m_bananaShoot = 0;

  int m_actionTime;
  int m_actionTimer;

  std::vector<Mesh*> m_meshes;



  //
  // - old -
  //

    bool timing = true;
    int rhythm_timer = 0;
    bool finished = false;

    // Boss
    int boss_x = 210;
    int boss_y = 0;
    int boss_shield = 0;
    int boss_hit = 0;
    int boss_dir = 1;
    bool boss_move_mode = false;
    bool boss_shield_mode = false;

    // Boss actions
    int boss_hold_amount = 0;
    int boss_lift = 0;
    int boss_drop = 0;

    int boss_breath = 0;

    int boss_left_hook = 0;
    int boss_right_hook = 0;
    bool boss_no_breath = true;


    int m_bananaMesh = 3;
};
