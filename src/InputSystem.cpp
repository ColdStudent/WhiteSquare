#include "InputSystem.h"



InputSystem::InputSystem(RenderSystem* rs) : m_rs(rs)
{
}


InputSystem::~InputSystem()
{


}


void InputSystem::cursor_pos_callback(double xpos, double ypos)
{
  m_cursor_x = xpos;
  m_cursor_y = ypos;
}


void InputSystem::mouse_button_callback(int button, int action, int mods)
{
  // Button released
  if (action == GLFW_RELEASE) m_allowDrag = false;

  if (m_allowDrag) return;
}


void InputSystem::frame()
{
}
