#ifndef BH_DECORATOR
#define BH_DECORATOR

#include "Behaviour.h"

namespace BehaviourTree
{
  class Decorator : public Behaviour
  {
  protected:
    Behaviour* mChild;

  public:
    Decorator(Behaviour* child) : mChild(child) {}
  };
}

#endif