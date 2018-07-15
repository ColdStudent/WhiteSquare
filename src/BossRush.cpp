#include "BossRush.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include "imgui.h"


BossRush::BossRush()
{

}


BossRush::~BossRush()
{

}


void BossRush::init()
{
  if (m_meshes.size() == 0)
  {
    m_meshes.resize(5);

    m_meshes[0] = new Mesh();
    m_meshes[0]->load_obj("data/backscene.obj");
    m_meshes[0]->upload_obj();
    m_meshes[0]->m_colours.push_back(glm::vec3(117.0f/255.f, 186.f/255.f, 231.f/255.f));
    m_meshes[0]->m_colours.push_back(glm::vec3(82.0f/255.f, 166.f/255.f, 230.f/255.f));
    m_meshes[0]->m_colours.push_back(glm::vec3(0.0f, 99.f/255.f, 178.f/255.f));

    m_meshes[1] = new Mesh();
    m_meshes[1]->load_obj("data/fire(1).obj");
    m_meshes[1]->upload_obj();
    m_meshes[1]->m_colours.push_back(glm::vec3(0.973f, 0.356f, 0.301f));
    m_meshes[1]->m_colours.push_back(glm::vec3(0.913f, 0.716f, 0.127f));

    m_meshes[2] = new Mesh();
    m_meshes[2]->load_obj("data/key.obj");
    m_meshes[2]->upload_obj();
    m_meshes[2]->m_colours.push_back(glm::vec3(232.f/255.f, 81.f/255.f, 68.f/255.f));
    m_meshes[2]->m_colours.push_back(glm::vec3(0.f, 0.f, 0.f));

    m_meshes[3] = new Mesh();
    m_meshes[3]->load_obj("data/key.obj");
    m_meshes[3]->upload_obj();
    m_meshes[3]->m_colours.push_back(glm::vec3(247.f/255.f, 227.f/255.f, 0.f/255.f));
    m_meshes[3]->m_colours.push_back(glm::vec3(0.f, 0.f, 0.f));

    m_meshes[4] = new Mesh();
    m_meshes[4]->load_obj("data/key.obj");
    m_meshes[4]->upload_obj();
    m_meshes[4]->m_colours.push_back(glm::vec3(0.f/255.f, 160.f/255.f, 121.f/255.f));
    m_meshes[4]->m_colours.push_back(glm::vec3(0.f, 0.f, 0.f));
  }

  //
  // m_meshes[2] = new Mesh();
  // m_meshes[2]->load_obj("data/dragon_holding.obj");
  // m_meshes[2]->upload_obj();

  m_boss.init();
  m_boss.reset();

  m_keyCounter = 0;
  m_keyCollected = false;
  rhythm_timer = 0;
  m_keyX = 30.f;
  m_keyY = 0.f;

  m_hitTimer = 0;
  m_keyGrabTimer = 0;
}


void BossRush::keyPress(int key)
{
  BossRushBase::keyPress(key);
}


void BossRush::keyRelease(int key)
{
  BossRushBase::keyRelease(key);
}


void BossRush::tick(MenuManager& menu, AudioManager& audio)
{

  s_player.tick(menu, audio);
  bool walking = false;

  //
  // Boss
  //
  m_boss.update(*this);

  //
  // Dusts
  //
  for (int i = 0; i < m_dusts.size(); ++i)
  {
    m_dusts[i].x += m_dusts[i].dx;
    m_dusts[i].y += m_dusts[i].dy;
    ++m_dusts[i].age;

    while (m_dusts[i].age >= 29)
    {
      m_dusts.erase(m_dusts.begin() + i, m_dusts.begin() + i + 1);
      if (i >= m_dusts.size()) break;
    }
  }

  for (int i = 0; i < m_bullets.size(); ++i)
  {
    m_bullets[i].x += m_bullets[i].dx;
    m_bullets[i].y += m_bullets[i].dy;
    ++m_bullets[i].age;

    if (m_bullets[i].y < -280 && m_bullets[i].dy < 0) m_bullets[i].dy = -m_bullets[i].dy;
    if (m_bullets[i].y > 280 && m_bullets[i].dy > 0) m_bullets[i].dy = -m_bullets[i].dy;

    while (m_bullets[i].age >= 399)
    {
      m_bullets.erase(m_bullets.begin() + i, m_bullets.begin() + i + 1);
      if (i >= m_bullets.size()) break;
    }
  }

  //
  // Updates
  //

  // Start scene
  if (s_player.hero_x > 0 && !timing && !finished)
  {
    timing = true;
    audio.play(1);
    rhythm_timer = 0;
    m_boss.start();
    m_hits = 0;
    m_keys = 0;
  }

  if (s_player.hero_x < 0 && finished)
  {
    // Save Record
    if (m_record_hits == -1)
    {
      m_record_hits = m_hits;
      m_record_keys = m_keys;
    }
    else if (m_keys - m_hits > m_record_keys - m_record_hits)
    {
      m_record_hits = m_hits;
      m_record_keys = m_keys;
    }

    init(); // reset
    finished = false;

  }

  if (s_player.hero_x == -380 && !timing)
  {
    m_screenTransition = 760;
  }

  //
  // Collides
  //
  if (s_player.m_hitTimer == 0)
  {
    // bullets
    for (int i = 0; i < m_bullets.size(); ++i)
    {
      if (squareCollide(m_bullets[i].x, m_bullets[i].y, 10, 10))
      {
        ++m_hits;
        s_player.hit();
        m_hitTimer = 27;
        m_hitX = m_bullets[i].x;
        m_hitY = m_bullets[i].y;
        break;
      }
    }
  }
  if (s_player.m_hitTimer == 0)
  {
    // Boss
    if (squareCollide(m_boss.x, m_boss.y, 48, 64))
    {
      ++m_hits;
      s_player.hit();
      m_hitTimer = 27;
      m_hitX = m_boss.x;
      m_hitY = m_boss.y;
    }
  }
  if (s_player.m_hitTimer == 0)
  {
    // Pine
    if (squareCollide(m_boss.pineapple_x2, m_boss.pineapple_y2, 16, 64))
    {
      ++m_hits;
      s_player.hit();
      m_hitTimer = 27;
      m_hitX = m_boss.pineapple_x2;
      m_hitY = m_boss.pineapple_y2;
    }
  }
  if (s_player.m_hitTimer == 0)
  {
    // Breath
    if (m_boss.m_breath_attack)
    {
      if (squareCollide(m_boss.m_breath_x, m_boss.y, 16, 64))
      {
        ++m_hits;
        s_player.hit();
        m_hitTimer = 27;
        m_hitX = m_boss.m_breath_x;
        m_hitY = m_boss.y;
      }
    }
  }
  if (s_player.m_hitTimer == 0)
  {
    // banana
    for (int i = 0; i < m_boss.m_bananas.size(); ++i)
    {
      if (squareCollide(m_boss.m_bananas[i].x, m_boss.m_bananas[i].y, 14, 14))
      {
        ++m_hits;
        s_player.hit();
        m_hitTimer = 27;
        m_hitX = m_bullets[i].x;
        m_hitY = m_bullets[i].y;
        break;
      }
    }
  }

  //
  if (!m_keyCollected)
  {
    if (squareCollide(m_keyX, m_keyY, 12, 12))
    {
      m_keyCollected = true;
      ++m_keys;
      m_keyGrabTimer = 27;
      m_keyGrabX = m_keyX;
      m_keyGrabY = m_keyY;
    }
  }
  if (m_hitTimer) --m_hitTimer;
  if (m_keyGrabTimer) --m_keyGrabTimer;

  //
  // Keys
  //
  if (timing && rhythm_timer % 110 == 109)
  {
    if (m_keyCounter < 36)
    {
      m_keyCollected = false;
      m_keyX = 90.f - 120.f * m_keyPos[m_keyCounter * 2];
      m_keyY = 300.f - 150.f * m_keyPos[m_keyCounter * 2 + 1];
      ++m_keyCounter;
    }
    else m_keyCollected = true;
  }

  if (timing)
  {
    ++rhythm_timer;

    if (rhythm_timer < 60 * 9.6)
    {
      //menu.m_display = "Warm Up";
    }
    else if (rhythm_timer < 60 * 25)
    {
      //menu.m_display = "Stage 1";
    }
    else if (rhythm_timer < 60 * 30)
    {
      //menu.m_display = "Transition";
    }
    else if (rhythm_timer < 60 * 40)
    {
      //menu.m_display = "Stage 2 - A";
    }
    else if (rhythm_timer < 60 * 54)
    {
      //menu.m_display = "Stage 2 - B";
    }
    else if (rhythm_timer < 60 * 69)
    {
      //menu.m_display = "Fallout";
    }
    else
    {
      //menu.m_display = "End";
      finished = true;
      timing = false;
    }
  }


  //
  // Hero
  //
  //
  if (s_player.hero_left_leg)
  {
    Dust dust;
    dust.x = s_player.hero_x - 7;
    dust.y = s_player.hero_y - 20;
    dust.dx = 0.f;
    dust.dy = 0.5f;
    dust.age = 0;
    m_dusts.push_back(dust);
  }
  if (s_player.hero_right_leg)
  {
    Dust dust;
    dust.x = s_player.hero_x + 7;
    dust.y = s_player.hero_y - 20;
    dust.dx = 0.f;
    dust.dy = 0.5f;
    dust.age = 0;
    m_dusts.push_back(dust);
  }

}


void BossRush::draw(RenderSystem& render)
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


  //
  // Back Scene
  //

  Model =
    glm::scale(glm::mat4(1.0f), glm::vec3(29, 29, 1.0));
  MVP = VP * Model;
  glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

  m_meshes[0]->draw(render.uniformDiffuse);

  //
  // Dusts
  //

  colour[0] = 1.0; colour[1] = 1.0; colour[2] = 1.0;
  glUniform3fv(render.uniformDiffuse, 1, colour);

  for (int i = 0; i < m_dusts.size(); ++i)
  {
    int width = 2 + 0.5 * m_dusts[i].age;
    float alpha = 0.8 * 0.003f*(30.f - m_dusts[i].age);

    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(m_dusts[i].x, m_dusts[i].y, 0)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(width, width, 1.0));

    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

    glUniform1f(render.uniformAlpha, alpha);

    render.drawObjModel_square();
  }
  glUniform1f(render.uniformAlpha, 1.0f);

  //
  // Boss
  //

  m_boss.draw(render);

  //
  //  Key
  //
  if (!m_keyCollected)
  {
    int width = 24;

    width = 200;
    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(m_keyX, m_keyY, 0)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(width, -width, 1.0));

    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

    int n = 2 + m_keyCounter % 3;
    m_meshes[n]->draw(render.uniformDiffuse);
  }

  //
  // Player
  //
  s_player.draw(render);

  //
  // Bullets
  //
  colour[0] = 1.0; colour[1] = 1.0; colour[2] = 1.0;
  glUniform3fv(render.uniformDiffuse, 1, colour);
  glUniform1f(render.uniformAlpha, 1.f);

  for (int i = 0; i < m_bullets.size(); ++i)
  {
    int width = 172;

    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(m_bullets[i].x, m_bullets[i].y, 0)) *
      glm::rotate(glm::mat4(1.0f), atan2f(-m_bullets[i].dx, m_bullets[i].dy), glm::vec3(0.f, 0.f, 1.f)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(width, width, 1.0));
    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

    //render.drawObjModel_square();
    m_meshes[1]->draw(render.uniformDiffuse);
  }

  //
  // UI
  //
  ImVec2 pos;
  ImVec2 pivot(0.f, 0.f);
  std::string msg = std::string("Hits: ") + std::to_string(m_hits) + std::string("    ");
  pos = ImVec2(11, 11);
  ImGui::SetNextWindowBgAlpha(0.f);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::Begin("shadow2", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowFontScale(0.5);
  ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), msg.c_str());
  ImGui::End();
  pos = ImVec2(11+1, 11-1);
  ImGui::SetNextWindowBgAlpha(0.f);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::Begin("\t\tScore Hits", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowFontScale(0.5);
  ImGui::Text(msg.c_str());
  ImGui::End();

  msg = std::string("Keys: ") + std::to_string(m_keys) + std::string("    ");
  pos = ImVec2(211, 11);
  ImGui::SetNextWindowBgAlpha(0.f);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::Begin("shadow4s", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowFontScale(0.5);
  ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), msg.c_str());
  ImGui::End();
  pos = ImVec2(211+1, 11-1);
  ImGui::SetNextWindowBgAlpha(0.f);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::Begin("\t\tScore Keys", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowFontScale(0.5);
  ImGui::Text(msg.c_str());
  ImGui::End();

  if (m_record_hits != -1)
  {
     msg = std::string("Record (Hits: ") + std::to_string(m_record_hits) + std::string("    ");
     pos = ImVec2(511, 11);
     ImGui::SetNextWindowBgAlpha(0.f);
     ImGui::SetNextWindowPos(pos, 0, pivot);
     ImGui::Begin("shadow9s", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
     ImGui::SetWindowFontScale(0.5);
     ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), msg.c_str());
     ImGui::End();
     pos = ImVec2(511+1, 11-1);
     ImGui::SetNextWindowBgAlpha(0.f);
     ImGui::SetNextWindowPos(pos, 0, pivot);
     ImGui::Begin("\t\tScore Hits Hi", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
     ImGui::SetWindowFontScale(0.5);
     ImGui::Text(msg.c_str());
     ImGui::End();

     msg = std::string("Keys: ") + std::to_string(m_record_keys) + std::string(")   ");
     pos = ImVec2(711, 11);
     ImGui::SetNextWindowBgAlpha(0.f);
     ImGui::SetNextWindowPos(pos, 0, pivot);
     ImGui::Begin("shadow5s", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
     ImGui::SetWindowFontScale(0.5);
     ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), msg.c_str());
     ImGui::End();
     pos = ImVec2(711+1, 11-1);
     ImGui::SetNextWindowBgAlpha(0.f);
     ImGui::SetNextWindowPos(pos, 0, pivot);
     ImGui::Begin("\t\tScore Keys Hi", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
     ImGui::SetWindowFontScale(0.5);
     ImGui::Text(msg.c_str());
     ImGui::End();
   }

   if (m_hitTimer)
   {
      std::string msg = std::string("-1");
      pos = ImVec2(400+m_hitX, 300-m_hitY + m_hitTimer);
      ImGui::SetNextWindowBgAlpha(0.f);
      ImGui::SetNextWindowPos(pos, 0, pivot);
      ImGui::Begin("shadow92s", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(0.5);
      ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), msg.c_str());
      ImGui::End();
      pos = ImVec2(400+m_hitX+1, 300-m_hitY + m_hitTimer-1);
      ImGui::SetNextWindowBgAlpha(0.f);
      ImGui::SetNextWindowPos(pos, 0, pivot);
      ImGui::Begin("hit-1", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(0.5);
      ImGui::Text(msg.c_str());
      ImGui::End();
    }

   if (m_keyGrabTimer)
   {
      std::string msg = std::string("+1");
      pos = ImVec2(400+m_keyGrabX, 300-m_keyGrabY + m_keyGrabTimer);
      ImGui::SetNextWindowBgAlpha(0.f);
      ImGui::SetNextWindowPos(pos, 0, pivot);
      ImGui::Begin("shadow93", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(0.5);
      ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), msg.c_str());
      ImGui::End();
      pos = ImVec2(400+m_keyGrabX+1, 300-m_keyGrabY + m_keyGrabTimer-1);
      ImGui::SetNextWindowBgAlpha(0.f);
      ImGui::SetNextWindowPos(pos, 0, pivot);
      ImGui::Begin("keygrab", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
      ImGui::SetWindowFontScale(0.5);
      ImGui::Text(msg.c_str());
      ImGui::End();
    }
}


void BossRush::dustSmash(int boss_x, int boss_y)
{
  //
  for (int i = 0; i < 29; ++i)
  {
    float dx = cos(3.14 * 2.0 * i / 29.0);
    float dy = sin(3.14 * 2.0 * i / 29.0);
    Dust dust;
    dust.x = boss_x + dx - 66;// - 88;
    dust.y = boss_y + dy - 64 - 10;
    dust.dx = 4.0 * dx;
    dust.dy = 2.0 * dy + 0.5f;
    dust.age = 0;
    m_dusts.push_back(dust);
  }
}


void BossRush::addBullet(Shootie bullet)
{
  m_bullets.push_back(bullet);
}


bool BossRush::squareCollide(int x, int y, int w, int h)
{
  int dx = x - s_player.hero_x;
  int dy = y - s_player.hero_y;

  if (abs(dx) < w + 16 &&
      abs(dy) < h + 16)
  {
    return true;
  }

  return false;
}


bool BossRush::circleCollide(int x, int y, int r)
{

}
