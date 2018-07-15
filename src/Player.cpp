#include "Player.h"
#include "graphics.h"
#include "BossRushBase.h"


Player BossRushBase::s_player;


Player::Player()
{

}


Player::~Player()
{

}


void Player::init()
{

}


void Player::tick(MenuManager& menu, AudioManager& audio)
{
  int sp = 3;

  bool canWalk = (hero_atk == 0);
  bool walking = false;
  if (canWalk)
  {

    if (up)
    {
      hero_y += sp;
      walking = true;
    }

    if (down)
    {
      hero_y += -sp;
      walking = true;
    }

    if (left)
    {
      hero_x += -sp;
      walking = true;
    }

    if (right)
    {
      hero_x += sp;
      walking = true;
    }
  }
  // steps
  if (walking)
  {
    if (hero_right_leg)
    {
      --hero_right_leg;
      if (hero_right_leg == 0) hero_left_leg = 10;
    }
    else if (hero_left_leg)
    {
      --hero_left_leg;
      if (hero_left_leg == 0) hero_right_leg = 10;
    }
    else hero_right_leg = 1;
  }
  else
  {
    hero_right_leg = 0;
    hero_left_leg = 0;
  }

  if (hero_atk > 0) hero_atk -= 1; else hero_atk = 0;

  if (hero_x < -380) hero_x = -380;
  if (hero_x > 380) hero_x = 380;
  if (hero_y < -270) hero_y = -270;
  if (hero_y > 270) hero_y = 270;

  if (m_hitTimer) --m_hitTimer;


}


void Player::draw(RenderSystem& render)
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
      int x = hero_x;
      int y = hero_y;

    //
    // Hero
    //
    if (m_hitTimer) glUniform1f(render.uniformAlpha, 0.5f);
    else glUniform1f(render.uniformAlpha, 1.f);
    glUniform3fv(render.uniformDiffuse, 1, colour);

    // Hero body
    Model =
      //glm::translate(glm::mat4(1.0f), glm::vec3(-1.0, 1.0, 0)) *
      // glm::scale(glm::mat4(1.0f), glm::vec3(1.0 / screen_width,  1.0 / screen_height, 1.0)) *
      glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) *
      glm::scale(glm::mat4(1.0f), glm::vec3(pixelWidth, pixelHeight, 1.0));

    // Our ModelViewProjection : multiplication of our 3 matrices
    MVP = VP * Model;
    // // Upload it
    glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

    render.drawObjModel_square();

    // feet
    if (hero_right_leg)
    {
      Model =
        glm::translate(glm::mat4(1.0f), glm::vec3(x + 7, y - 18, 0)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(8, 4, 1.0));

      MVP = VP * Model;
      glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
      render.drawObjModel_square();
    }
    else
    {
      Model =
        glm::translate(glm::mat4(1.0f), glm::vec3(x + 7, y - 20, 0)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(8, 8, 1.0));

      MVP = VP * Model;
      glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
      render.drawObjModel_square();
    }

    if (hero_left_leg)
    {
      Model =
        glm::translate(glm::mat4(1.0f), glm::vec3(x - 7, y - 18, 0)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(8, 4, 1.0));

      MVP = VP * Model;
      glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
      render.drawObjModel_square();
    }
    else
    {
      Model =
        glm::translate(glm::mat4(1.0f), glm::vec3(x - 7, y - 20, 0)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(8, 8, 1.0));

      MVP = VP * Model;
      glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);
      render.drawObjModel_square();
    }

    if (hero_atk)
    {
      x += pixelWidth / 2;
      pixelWidth = 64;
      x += pixelWidth / 2;

      Model =
        glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0)) *
        glm::scale(glm::mat4(1.0f), glm::vec3(pixelWidth, pixelHeight, 1.0));

      MVP = VP * Model;
      glUniformMatrix4fv(render.uniformMVP, 1, GL_FALSE, &MVP[0][0]);

      colour[0] = 1.0; colour[1] = 0.20; colour[2] = 0.20;
      glUniform3fv(render.uniformDiffuse, 1, colour);

      render.drawObjModel_square();
    }
}
