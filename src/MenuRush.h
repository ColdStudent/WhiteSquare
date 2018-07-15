#include "BossRushBase.h"
#include "Mesh.h"


class MenuRush : public BossRushBase
{
public:

  MenuRush();
  ~MenuRush();

  void init();
  void draw(RenderSystem&);
  void tick(MenuManager& menu, AudioManager& audio);

  void keyPress(int);
  void keyRelease(int);

  int m_screenTransition = 0;

protected:

  //void drawText(const char*);

  std::vector<Shootie> m_shooties;

  std::vector<Mesh*> m_meshes;

  std::vector<Dust> m_dusts;

  int m_colorTimer = 0;
  float m_s = 0.f;
};
