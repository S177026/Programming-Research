#ifndef BH_SELECTOR
#define BH_SELECTOR

#include "Status.h"
#include "Composite.h"

namespace BehaviourTree
{
  class Selector : public Composite
  {
  protected:
    virtual ~Selector() { }

    virtual void onInitialize()
    {
      mCurrent = mChildren.begin();
    }

    virtual Status update()
    {
      for (;;) {
        Status s = (*mCurrent)->tick();

        if (s != Status::FAILURE) {
          return s;
        }

        if (++mCurrent == mChildren.end()) {
          return Status::FAILURE;
        }
      }
    }

    Behaviours::iterator mCurrent;
  };
}

#endif