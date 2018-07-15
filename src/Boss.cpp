#include "Boss.h"
#include "graphics.h"


Boss::Boss()
{

}


Boss::~Boss()
{

}


void Boss::init()
{
  if (m_meshes.size() == 0)
  {
    m_meshes.resize(5);

    m_meshes[0] = new Mesh();
    m_meshes[0]->load_obj("data/pineapple.obj");
    m_meshes[0]->upload_obj();
    m_meshes[0]->m_colours.push_back(glm::vec3(0.067f, 0.445f, 0.0f));
    m_meshes[0]->m_colours.push_back(glm::vec3(0.030f, 0.209f, 0.060f));
    m_meshes[0]->m_colours.push_back(glm::vec3(1.0f, 0.815f, 0.159f));
    m_meshes[0]->m_colours.push_back(glm::vec3(0.913f, 0.716f, 0.127f));
    m_meshes[0]->m_colours.push_back(glm::vec3(1.0f, 0.371f, 0.041f));
    m_meshes[0]->m_colours.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

    m_meshes[1] = new Mesh();
    m_meshes[1]->load_obj("data/dragon.obj");
    m_meshes[1]->upload_obj();
    m_meshes[1]->m_colours.push_back(glm::vec3(0.888f, 0.153f, 0.086f));
    m_meshes[1]->m_colours.push_back(glm::vec3(0.651f, 0.095f, 0.061f));
    m_meshes[1]->m_colours.push_back(glm::vec3(0.178f, 0.604f, 0.089f));
    m_meshes[1]->m_colours.push_back(glm::vec3(0.973f, 0.356f, 0.301f));
    m_meshes[1]->m_colours.push_back(glm::vec3(0.133f, 0.133f, 0.133f));
    m_meshes[1]->m_colours.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

    m_meshes[2] = new Mesh();
    m_meshes[2]->load_obj("data/dragon_holding.obj");
    m_meshes[2]->upload_obj();
    m_meshes[2]->m_colours.push_back(glm::vec3(0.888f, 0.153f, 0.086f));
    m_meshes[2]->m_colours.push_back(glm::vec3(0.651f, 0.095f, 0.061f));
    m_meshes[2]->m_colours.push_back(glm::vec3(0.178f, 0.604f, 0.089f));
    m_meshes[2]->m_colours.push_back(glm::vec3(0.973f, 0.356f, 0.301f));
    m_meshes[2]->m_colours.push_back(glm::vec3(0.133f, 0.133f, 0.133f));
    m_meshes[2]->m_colours.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

    m_meshes[3] = new Mesh();
    m_meshes[3]->load_obj("data/banana.obj");
    m_meshes[3]->upload_obj();
    m_meshes[3]->m_colours.push_back(glm::vec3(0.067f, 0.445f, 0.0f));
    m_meshes[3]->m_colours.push_back(glm::vec3(0.030f, 0.209f, 0.060f));
    m_meshes[3]->m_colours.push_back(glm::vec3(0.266f, 0.156f, 0.125f));
    m_meshes[3]->m_colours.push_back(glm::vec3(0.0f, 0.0f, 0.0f));

    m_meshes[4] = new Mesh();
    m_meshes[4]->load_obj("data/banana.obj");
    m_meshes[4]->upload_obj();
    m_meshes[4]->m_colours.push_back(glm::vec3(1.0f, 0.815f, 0.159f));
    m_meshes[4]->m_colours.push_back(glm::vec3(0.913f, 0.716f, 0.127f));
    m_meshes[4]->m_colours.push_back(glm::vec3(0.266f, 0.156f, 0.125f));
    m_meshes[4]->m_colours.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
  }
}


void Boss::reset()
{
  //
  // Reset vars
  //
  m_timer = 0;

  m_intro = false;
  m_walking = false;
  m_smash_attack = false;
  m_lifting = false;
  m_shooting = false;
  m_transition = false;

  m_actionTimer = 0;

  x = 210 + 110;
  y = 0;

  pineapple_x = 210;
  pineapple_y = 0;

  timing = false;
  rhythm_timer = 0;
  finished = false;

  boss_hold_amount = 0;

  m_bananaMesh = 3;
}


void Boss::start()
{
  m_intro = true;
  timing = true;
}


void Boss::actionManager()
{
  if (timing)
  {
    // 110 ticks = 4 bets

    switch (rhythm_timer)
    {
      // BAR 0                    - Intro / Warmup
    case 0:
      m_intro = true;
      // m_actionTime = 55;
      m_actionTimer = 55;
      break;
    case 55:
      m_shooting = true;
      //m_actionTime = 55;
      break;

      // BAR 1
    case 110:
      m_shooting = false;
      break;
    case 165:
      m_lifting = true;
      break;

      // BAR 2
    case 220:
      break;
    case 275:
      m_breath_attack = true;
      m_actionTimer = 220;
      break;

      // BAR 3
    case 330:
      break;
    case 385:
      break;

      // BAR 4
    case 440:
      break;
    case 495:
      m_smash_attack = true;
      break;

      // BAR 5                    - Stage 1
    case 660:
      m_bananaShoot = 2;
      break;
    case 715:
      m_shooting = true;
      break;

      // BAR 6
    case 770:
      m_shooting = false;
      break;
    case 825:
      m_shooting = true;
      break;

      // BAR 8
    case 880:
      m_lifting = true;
      m_shooting = false;
      break;
    case 935:
      break;

      // BAR 9
    case 990:
      m_breath_attack = true;
      m_actionTimer = 220;
      break;
    case 1045:
      break;

      // BAR 10
    case 1100:
      break;
    case 1155:
      break;

      // BAR 11
    case 1210:
      m_walking = true;
      boss_dir = 1;
      m_shooting = true;
      break;
    case 1265:
      m_shooting = false;
      break;

      // BAR 12
    case 1320:
      m_shooting = true;
      break;
    case 1375: break;
      // BAR 13
    case 1430:
      break;
    case 1485: break;

      // BAR 14                    - Transition
    case 1540:
      m_walking = false;
      boss_dir = 0;
      break;
    case 1595: break;
      // BAR 15
    case 1650:
      break;
    case 1705: break;
      // BAR 16
    case 1760: break;
    case 1815: break;
      // BAR 17                    - Stage 2 A
    case 1870:
      m_bananaMesh = 4;
      m_smash_attack = true;
      m_shooting = false;
      break;
    case 1925: break;
      // BAR 18
    case 1980:
      m_bananaShoot = 2;
      break;
    case 2035:
      m_bananaShoot = 2;
      break;
      // BAR 19
    case 2090:
      m_lifting = true;
      m_shooting = false;
      break;
    case 2145:
      m_breath_attack = true;
      m_actionTimer = 220;
      break;
      // BAR 20
    case 2200:
      break;
    case 2255: break;
      // BAR 21
    case 2310: break;
    case 2365: break;
      // BAR 22                     - Stage 2 B
    case 2420:
      m_smash_attack = true;
      m_shooting = false;
      break;
    case 2475: break;
      // BAR 23
    case 2530:
      m_bananaShoot = 2;
      break;
    case 2585:
      m_bananaShoot = 2;
      break;
    // BAR 24
    case 2640:
      m_lifting = true;
      m_shooting = false;
      break;
    case 2695:
      m_breath_attack = true;
      m_actionTimer = 220;
      break;
    // BAR 25
    case 2750:
      break;
    case 2805: break;
    // BAR 26
    case 2860:
      m_walking = true;
      boss_dir = -1;
      m_shooting = true;
      m_bananaShoot = 2;
      break;
    case 2915:
      m_bananaShoot = 2;
      break;
    // BAR 27
    case 2970:
      m_bananaShoot = 2;
      break;
    case 3025:
      m_bananaShoot = 2;
      break;
    // BAR 28
    case 3080:
      m_bananaShoot = 2;
      break;
    case 3135:
      m_bananaShoot = 2;
      break;
      // BAR 29                       - Fallot
    case 3190:
      m_walking = false;
      boss_dir = 0;
      break;
    case 3245: break;
    // BAR 30
    case 3300: break;
    case 3355: break;
    // BAR 31
    case 3410: break;
    case 3465: break;
    // BAR 32
    case 3520: break;
    case 3575: break;
    // BAR 33
    case 3630: break;
    case 3685: break;
    // BAR 34
    case 3740: break;
    case 3795: break;
    // BAR 35
    case 3850: break;
    case 3905:
      boss_dir = 0;
      m_shooting = false;
      m_walking = false;
      finished = true;
      break;

    default:
      break;
    };

    if (m_actionTimer)
    {
      --m_actionTimer;

      //if (m_actionTimer == 0) m_actionTimer = m_actionTime;
    }

    ++rhythm_timer;
  }
}


void Boss::update(BossRushBase& rush)
{
  actionManager();

  //
  // Actions 2
  //
  if (m_intro)
  {
    if (m_actionTimer == 0) m_intro = false;

    x -= 2;
  }

  if (m_shooting)
  {
    if (rhythm_timer % 55 == 0)
    {
      Shootie boom;
      boom.x = x;
      boom.y = y;
      boom.dx = -1.6;
      boom.dy = -2.1 + 0.91*boss_dir;
      boom.age = 0;
      rush.addBullet(boom);
    }
    if (rhythm_timer % 55 == 13)
    {
      Shootie boom;
      boom.x = x;
      boom.y = y;
      boom.dx = -1.6;
      boom.dy = 2.1 + 0.91*boss_dir;
      boom.age = 0;
      rush.addBullet(boom);
    }
    if (rhythm_timer % 55 == 27)
    {
      Shootie boom;
      boom.x = x;
      boom.y = y;
      boom.dx = -2.1;
      boom.dy = -1.6 + 0.91*boss_dir;
      boom.age = 0;
      rush.addBullet(boom);
    }
    if (rhythm_timer % 55 == 40)
    {
      Shootie boom;
      boom.x = x;
      boom.y = y;
      boom.dx = -2.1;
      boom.dy = 1.6 + 0.91*boss_dir;
      boom.age = 0;
      rush.addBullet(boom);
    }
  }

  if (m_lifting)
  {
    boss_lift = 1;
    boss_hold_amount += boss_lift;
    if (boss_hold_amount > 100)
    {
      boss_hold_amount = 100;
      m_lifting = 0;
      //boss_breath = 55 * 4;
    }
  }

  if (m_smash_attack)
  {
    boss_drop = 3;
    boss_hold_amount -= boss_drop;
    if (boss_hold_amount < 0)
    {
      boss_hold_amount = 0;
      m_smash_attack = false;
      m_shooting = true;
      // boss_drop = 0;
      // boss_left_hook = 55;
      // boss_right_hook = 55;

      rush.dustSmash(x, y);
    }
  }

  if (m_breath_attack)
  {
    if (m_actionTimer == 0) m_breath_attack = false;
  }

  // if (m_walking)
  // {
  //   y += boss_dir;
  //   pineapple_y += boss_dir;
  //
  //   if (boss_y < -200) boss_dir = 1;
  //   if (boss_y > 200) boss_dir = -1;
  // }

  if (m_bananaShoot > 0)
  {
    if (rhythm_timer % 55 == 0)
    {
      Shootie ban;
      ban.x = x;
      ban.y = y;
      ban.dx = -3.2;
      ban.dy = 6.5;
      ban.age = 0;
      m_bananas.push_back(ban);
      --m_bananaShoot;
    }

    if (rhythm_timer % 55 == 27)
    {
      Shootie ban;
      ban.x = x;
      ban.y = y;
      ban.dx = -2.9;
      ban.dy = -6.6;
      ban.age = 1;
      m_bananas.push_back(ban);
      --m_bananaShoot;
    }
  }

  //
  // Boss Actions
  //
  bool canWalk = m_walking;// && (boss_hit == 0);

  if (boss_hold_amount < 100) canWalk = false;
  if (m_breath_attack) canWalk = false;


  //
  // Boss
  //

  if (canWalk)
  {
    y += boss_dir;
    pineapple_y += boss_dir;

    if (y < -200) boss_dir = 1;
    if (y > 200) boss_dir = -1;
  }

  if (boss_y == 0)
  {
    boss_shield = 0;
    //boss_drop = 5;
  }

  if ((boss_y == -100 && boss_dir == 1) || (boss_y == 100 && boss_dir == -1))
  {
    boss_shield = 1;
    boss_drop = 5;
  }

  if (boss_shield_mode) boss_shield = 1;

  if (boss_hit > 0) boss_hit -= 1; else boss_hit = 0;

  //
  //  Banana
  //
  for (int i = 0; i < m_bananas.size(); ++i)
  {
    m_bananas[i].x += m_bananas[i].dx;
    m_bananas[i].y += m_bananas[i].dy;
    m_bananas[i].age += 2;

    //m_bananas[i].dx -= 0.04f;
    if (m_bananas[i].age % 2)
    {
      m_bananas[i].dy += 0.09f;
    }
    else
    {
      m_bananas[i].dy -= 0.09f;
    }

    while (m_bananas[i].age >= 799)
    {
      m_bananas.erase(m_bananas.begin() + i, m_bananas.begin() + i + 1);
      if (i >= m_bananas.size()) break;
    }
  }
}


void Boss::draw(RenderSystem& render)
{
  float colour[] = {1.f, 1.f, 1.f };

  glm::mat4 Model;
  glm::mat4 MVP;
  float v_side = 0.5f;
  glm::mat4 Projection = glm::ortho(-v_side*800.f, v_side*800.f, -v_side*600.f, v_side*600.f, 1.0f, 100.0f);

  // Camera matrix
  glm::mat4 View = glm::lookAt(
                glm::vec3(0, 0, 10), // Camera is at (4,3,3), in World Space
                glm::vec3(0, 0, 0), // and looks at the origin
                glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
               );

  glm::mat4 VP = Projection * View;

  int pixelWidth = 32;
  int pixelHeight = 32;
  int screen_width = 800;
  int screen_height = 600;

  if (m_breath_attack)
  {
    pixelWidth = 96;
    pixelHeight = 128;

    int l = 2;
    if (m_actionTimer < 3*55)
    {
      l = 3*55 - m_actionTimer;
      l *= 6;
    }

    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(x - l / 2, y, 0)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(l, pixelHeight, 1.0));
    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

    colour[0] = 0.8; colour[1] = 0.6; colour[2] = 0.8;
    glUniform3fv(render.uniformDiffuse, 1, colour);

    glUniform1f(render.uniformAlpha, 0.6f);
    render.drawObjModel_square();

    m_breath_x = x - l;
    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(x - l, y, 0)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(32, pixelHeight, 1.0));
    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

    colour[0] = 1.0; colour[1] = 0.6; colour[2] = 0.6;
    glUniform3fv(render.uniformDiffuse, 1, colour);

    glUniform1f(render.uniformAlpha, 1.f);
    render.drawObjModel_square();
  }


  //
  // Boss
  //

  pixelWidth = 96;
  pixelHeight = 128;


  if (boss_hit) {colour[0] = 1.0; colour[1] = 0.4; colour[2] = 0.4;}
  else {colour[0] = 1.0; colour[1] = 1.0; colour[2] = 1.0;}
  glUniform3fv(render.uniformDiffuse, 1, colour);

  // Model =
  //   glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) *
  //   glm::scale(glm::mat4(1.0f), glm::vec3(pixelWidth, pixelHeight, 1.0));
  // MVP = VP * Model;
  // glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
  //render.drawObjModel_square();

  int dx = -88 * cos(3.14 * (boss_hold_amount) / 200.0);
  int dy = 129 * sin(3.14 * (boss_hold_amount) / 200.0);
  pineapple_x2 = pineapple_x + dx;
  pineapple_y2 = pineapple_y + dy;

  Model =
    glm::translate(glm::mat4(1.0f), glm::vec3(pineapple_x + dx - 48, pineapple_y + dy + 64, 0)) *
    glm::scale(glm::mat4(1.0f), glm::vec3(1001, -1001, 1.0));
  MVP = VP * Model;
  glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
  m_meshes[0]->draw(render.uniformDiffuse);

  Model =
    glm::translate(glm::mat4(1.0f), glm::vec3(x - 48, y + 64, 0)) *
    glm::scale(glm::mat4(1.0f), glm::vec3(1001, -1001, 1.0));
  MVP = VP * Model;
  glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

  if (boss_hold_amount < 50)
    m_meshes[1]->draw(render.uniformDiffuse);
  else
    m_meshes[2]->draw(render.uniformDiffuse);

  //
  //  Banana
  //
  for (int i = 0; i < m_bananas.size(); ++i)
  {
    int width = 300;

    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(m_bananas[i].x, m_bananas[i].y, 0)) *
      glm::rotate(glm::mat4(1.0f), 0.04f*m_bananas[i].age, glm::vec3(0.f, 0.f, 1.f)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(width, width, 1.0));
    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

    //render.drawObjModel_square();
    m_meshes[m_bananaMesh]->draw(render.uniformDiffuse);
  }


  // if (boss_shield)
  // {
  //   x -= pixelWidth / 2;
  //   pixelWidth = 8;
  //   x -= pixelWidth / 2;
  //
  //   Model =
  //     glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) *
  //     glm::scale(glm::mat4(1.0f), glm::vec3(pixelWidth, pixelHeight, 1.0));
  //
  //   // Our ModelViewProjection : multiplication of our 3 matrices
  //   MVP = VP * Model;
  //   // // Upload it
  //   glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
  //
  //   colour[0] = 0.6; colour[1] = 0.6; colour[2] = 0.6;
  //   glUniform3fv(render.uniformDiffuse, 1, colour);
  //
  //   render.drawObjModel_square();
  // }
  // else
  // {
  //   y += pixelHeight / 2;
  //   pixelHeight = 8;
  //   y += pixelHeight / 2;
  //
  //   pixelWidth = 128;
  //
  //   Model =
  //     glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) *
  //     glm::scale(glm::mat4(1.0f), glm::vec3(pixelWidth, pixelHeight, 1.0));
  //
  //   // Our ModelViewProjection : multiplication of our 3 matrices
  //   MVP = VP * Model;
  //   // // Upload it
  //   glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
  //
  //   colour[0] = 0.6; colour[1] = 0.6; colour[2] = 0.6;
  //   glUniform3fv(render.uniformDiffuse, 1, colour);
  //
  //   render.drawObjModel_square();
  // }
}
