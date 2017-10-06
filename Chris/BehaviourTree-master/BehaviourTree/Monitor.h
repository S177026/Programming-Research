#ifndef BH_MONITOR
#define BH_MONITOR

#include "Parallel.h"

namespace BehaviourTree
{
  class Monitor : public Parallel
  {
  public:
    Monitor() 
      : Parallel(Parallel::Policy::REQUIRE_ONE, Parallel::Policy::REQUIRE_ONE)
      {}

    void addCondition(Behaviour* condition)
    {
      mChildren.insert(mChildren.begin(), condition);
    }

    void addAction(Behaviour* action)
    {
      mChildren.push_back(action);
    }
  };
}

#endif