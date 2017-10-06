#ifndef BH_ACTIVE_SELECTOR
#define BH_ACTIVE_SELECTOR

#include "Selector.h"

namespace BehaviourTree
{
  class ActiveSelector : public Selector
  {
  protected:
    virtual void onInitialize() override
    {
      mCurrent = mChildren.end();
    }

    virtual Status update() override
    {
      Behaviours::iterator previous = mCurrent;

      Selector::onInitialize();
      Status result = Selector::update();

      if (previous != mChildren.end() && mCurrent != previous) {
        (*previous)->onTerminate(Status::ABORTED);
      }

      return result;
    }
  };
}

#endif