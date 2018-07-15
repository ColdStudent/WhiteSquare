#include <stdio.h>
#include <string.h>
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "WindowManager.h"
#include "AudioManager.h"
#include "RenderSystem.h"
#include "MenuManager.h"
#include "BossRush.h"
#include "MenuRush.h"


AudioManager audio;
RenderSystem render;
WindowManager window;
MenuManager menu;
BossRush bossDragon;
MenuRush bossMenu;
//BossRushBase& boss = bossMenu;

int g_menuMode = 1;

void gameloop()
{
  if (bossMenu.m_screenTransition)
  {
     bossMenu.m_screenTransition = 0;
     BossRushBase::s_player.hero_x = -380;
     g_menuMode = 2;
  }

  if (bossDragon.m_screenTransition)
  {
    bossDragon.m_screenTransition = 0;
    g_menuMode = 1;
    audio.play(0, true);
  }

  audio.tick();
  if (g_menuMode == 1) bossMenu.tick(menu, audio);
  else bossDragon.tick(menu, audio);
  render.draw();
  menu.predraw();
  //boss.draw(render);
  if (g_menuMode == 1) bossMenu.draw(render);
  else bossDragon.draw(render);
  menu.postdraw(window);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

  if (action == GLFW_PRESS)
      bossDragon.keyPress(key);
  if (action == GLFW_RELEASE)
      bossDragon.keyRelease(key);
}


int main()
{
  window.init();
  audio.init();
  audio.save = true;
  audio.load_ogg("data/bossrushelectro.ogg");
  audio.save = false;
  audio.load_ogg("data/bossrush.ogg");
  audio.play(0, true);
  render.init();
  menu.init(window);
  bossMenu.init();
  bossDragon.init();

  // Cursor callbacks
  // glfwSetCursorPosCallback(window.g_window, cursor_pos_callback);
  // glfwSetMouseButtonCallback(window.g_window, mouse_button_callback);
  // glfwSetScrollCallback(window.g_window, scroll_callback);
  glfwSetKeyCallback(window.g_window, key_callback);

  emscripten_set_main_loop(gameloop, 0, 1);
}
