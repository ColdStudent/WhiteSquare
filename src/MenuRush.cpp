#include "MenuRush.h"
#include "imgui.h"


MenuRush::MenuRush()
{

}


MenuRush::~MenuRush()
{

}


void MenuRush::init()
{
  if (m_meshes.size() == 0)
  {
    m_meshes.resize(2);

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
    m_meshes[1]->load_obj("data/banana.obj");
    m_meshes[1]->upload_obj();
    m_meshes[1]->m_colours.push_back(glm::vec3(1.f, 0.533f,  0.002f));
    m_meshes[1]->m_colours.push_back(glm::vec3(1.f, 0.352f,  0.000f));
    m_meshes[1]->m_colours.push_back(glm::vec3(0.266f, 0.156f, 0.125f));
    m_meshes[1]->m_colours.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
  }
}


void drawCentred(const char* text)
{

}


void drawText(const char* title, const char* text, ImVec2 pos)
{
  ImVec2 pivot(0,0);
  ImGui::SetNextWindowBgAlpha(0.f);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::Begin("shadow", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), text);
  ImGui::End();
  pos.x += 1;
  pos.y -= 1;
  ImGui::SetNextWindowBgAlpha(0.f);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::Begin(title, NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::TextColored(ImVec4(1.0f,1.0f,1.0f,1.0f), text);
  ImGui::End();
}


void textRight(const char* title, const char* text, ImVec2 pos)
{
  ImVec2 pivot(0,0);
  ImVec2 size = ImGui::CalcTextSize(text);
  pos.x -= size.x/2;
  ImGui::SetNextWindowBgAlpha(0.f);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::Begin("\t\t\tshadow3", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowFontScale(0.5);
  ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), text);
  ImGui::End();
  pos.x += 1;
  pos.y -= 1;
  ImGui::SetNextWindowBgAlpha(0.f);
  ImGui::SetNextWindowPos(pos, 0, pivot);
  ImGui::Begin(title, NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowFontScale(0.5);
  ImGui::TextColored(ImVec4(1.0f,1.0f,1.0f,1.0f), text);
  ImGui::End();
  pos.x += size.x;
  pos.x += 1;
}


void MenuRush::draw(RenderSystem& render)
{
  s_player.draw(render);

  int h = 600;
  int w = 800;

  ImVec2 ts = ImGui::CalcTextSize("The White Square");
  ImVec2 ts1 = ImGui::CalcTextSize("vs");
  ImVec2 ts2 = ImGui::CalcTextSize("The Draganas");
  ImVec2 pos((w-ts.x)/2, (h-ts.y)/2);
  ImVec2 pivot(0,0);

  pos = ImVec2((w-ts.x)/2, (h-3*ts.y)/2);

  if (s_player.hero_x < 125)
  {
    //ImGui::SetNextWindowPos(pos, 0, pivot);
    drawText("Title", "The White Square", pos);
    pos = ImVec2((w-ts1.x)/2, (h-3*ts.y)/2);
    drawText("Title", "vs", pos);
    pos = ImVec2((w-ts2.x)/2, (h-3*ts.y)/2);
    drawText("Title", "The Draganas", pos);
  }

  if (s_player.hero_x < -125)
  {
    pos = ImVec2(0, (h-5*ts.y)/2);
    ImGui::SetNextWindowBgAlpha(0.f);
    ImGui::SetNextWindowPos(pos, 0, pivot);
    ImGui::Begin("shadow2", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowFontScale(0.5);
    ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), "\t\tHow to Play");
    ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), "(Up Down) \t Move around");
    ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), "(Left Right)");
    ImGui::Text("");
    ImGui::Text("");
    ImGui::Text("");
    ImGui::Text("");
    ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), "Collect keys! Don't die!");
    ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), "If you die you lose");
    ImGui::TextColored(ImVec4(0.0f,0.0f,0.0f,1.0f), "\t... a life.");
    ImGui::End();
    pos = ImVec2(0+1, (h-5*ts.y)/2-1);
    ImGui::SetNextWindowBgAlpha(0.f);
    ImGui::SetNextWindowPos(pos, 0, pivot);
    ImGui::Begin("HowTo", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowFontScale(0.5);
    ImGui::Text("\t\tHow to Play");
    ImGui::Text("(Up Down) \t Move around");
    ImGui::Text("(Left Right)");
    ImGui::Text("");
    ImGui::Text("");
    ImGui::Text("");
    ImGui::Text("");
    ImGui::Text("Collect keys! Don't die!");
    ImGui::Text("If you die you lose");
    ImGui::Text("\t... a life.");
    ImGui::End();
  }

  if (s_player.hero_x < -5)
  {
    pos = ImVec2(780, (h-6*ts.y)/2-1);
    textRight("\t\t\t\t\tCredit", "\t    \t    \t     \t     \t", pos);
    textRight("\t\t\t\t\tCredit", "Made for", pos);
    textRight("\t\t\t\t\tCredit", "Weekly Game Jam #52", pos);
    textRight("\t\t\t\t\tCredit", "Programming & Animation", pos);
    textRight("\t\t\t\t\tCredit", "by Meatpudding", pos);
    textRight("\t\t\t\t\tCredit", "Music by Azemazer", pos);
    textRight("\t\t\t\t\tCredit", "Additional assets by", pos);
    textRight("\t\t\t\t\tCredit", "turkkub", pos);
    textRight("\t\t\t\t\tCredit", "perfect", pos);
    textRight("\t\t\t\t\tCredit", "& Freepik", pos);
  }

  if (s_player.hero_x == 380 && m_screenTransition == 0)
  {
    m_screenTransition = 800;
  }

  //
  // Particle
  //
  float t1 = 0.5f + 0.5f * sin(3.14 * m_colorTimer / 110.f);
  float colour[] = {0.78f + 0.22f * t1, 1.f - 0.22f * t1, 0.93f };
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

  glUniform3fv(render.uniformDiffuse, 1, colour);

  for (int i = 0; i < m_shooties.size(); ++i)
  {
    int width = 6;
    float alpha = m_shooties[i].alpha * (56.f - m_shooties[i].age) / 56.f;

    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(m_shooties[i].x, m_shooties[i].y, 0)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(width, width, 1.0));

    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

    glUniform1f(render.uniformAlpha, alpha);

    render.drawObjModel_square();
  }
  glUniform1f(render.uniformAlpha, 1.0f);


  // Fruit



    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(-128, -124, 0)) *
      glm::rotate(glm::mat4(1.0f), 0.1f + 0.03f * t1, glm::vec3(0.f, 0.f, 1.f)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(1051 + 5*m_s, -(1051 + 5*m_s), 1.0));
    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
    m_meshes[0]->draw(render.uniformDiffuse);

    Model =
      glm::translate(glm::mat4(1.0f), glm::vec3(98, -224, 0)) *
      glm::rotate(glm::mat4(1.0f), -0.1f - 0.3f * t1, glm::vec3(0.f, 0.f, 1.f)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(1001 + 55*m_s, -(1001 + 55*m_s), 1.0));
    MVP = VP * Model;
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
    m_meshes[1]->draw(render.uniformDiffuse);


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
}


void MenuRush::tick(MenuManager& menu, AudioManager& audio)
{
  s_player.tick(menu, audio);

  m_s = 0.1 * m_s + 0.45 * audio.m_convertedBuffer_save[audio.sample_offset] / (float)0xFFFF;


  // Check sound and create particles
  for (int i = 0; i < 27; ++i)
  {
    float dx = cos(3.14 * 2.0 * i / 27.0);
    float dy = sin(3.14 * 2.0 * i / 27.0);
    Shootie dust;
    dust.x = 0 + 24.0 * dx;
    dust.y = 175 + 24.0 * dy;
    dust.dx = 4.0 * dx;
    dust.dy = 4.0 * dy;
    dust.age = 0;

    // ogg_int16_t t = audio.m_convertedBuffer[audio.sample_offset];
    // char a = ((char*)t)[0];
    // char b = ((char*)t)[1];
    // dust.alpha = (a + b) / 255.0;
    dust.alpha = 2* audio.m_convertedBuffer_save[audio.sample_offset] / (float)0xFFFF;
    m_shooties.push_back(dust);
  }

  //std::cout << audio.sec_offset << std::endl;

  // Continue
  for (int i = 0; i < m_shooties.size(); ++i)
  {
    m_shooties[i].x += m_shooties[i].dx;
    m_shooties[i].y += m_shooties[i].dy;
    ++m_shooties[i].age;

    while (m_shooties[i].age >= 56)
    {
      m_shooties.erase(m_shooties.begin() + i, m_shooties.begin() + i + 1);
      if (i >= m_shooties.size()) break;
    }
  }


  //
  m_colorTimer = (m_colorTimer + 1) % 220;


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

    //
    // Hero
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


void MenuRush::keyPress(int)
{

}


void MenuRush::keyRelease(int)
{

}
