#ifndef BH_COMPOSITE
#define BH_COMPOSITE

#include <vector>
#include "Behaviour.h"

namespace BehaviourTree
{
  class Composite : public Behaviour
  {
  public:
    void addChild(Behaviour* child)
    {
      mChildren.push_back(child);
    }

    void removeChild(Behaviour* child);
    
    void clearChildren();

  protected:
    using Behaviours = std::vector<Behaviour*>;
    Behaviours mChildren;
  };
}

#endif