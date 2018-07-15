#pragma once


#include "graphics.h"


class WindowManager
{
public:

  WindowManager();
  ~WindowManager();

  int init();

  GLFWwindow* g_window;
  int width = 800;
  int height = 600;

};
