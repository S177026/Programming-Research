#ifndef BH_SEQUENCE
#define BH_SEQUENCE

#include "Composite.h"

namespace BehaviourTree
{
  class Sequence : public Composite
  {
  protected:
    virtual ~Sequence()
    {
    }

    virtual void onInitialize()
    {
      mCurrentChild = mChildren.begin();
    }

    virtual Status update()
    {
      for (;;)
      {
        Status s = (*mCurrentChild)->tick();

        if (s != Status::SUCCESS) {
          return s;
        }

        // have we run all the children?
        if (++mCurrentChild == mChildren.end())
        {
          return Status::SUCCESS;
        }
      }
    }

    Behaviours::iterator mCurrentChild;
  };

}

#endif //BH_SEQUENCE