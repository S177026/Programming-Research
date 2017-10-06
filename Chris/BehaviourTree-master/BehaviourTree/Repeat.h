#ifndef BH_REPEAT
#define BH_REPEAT

#include "Decorator.h"

namespace BehaviourTree
{
  class Repeat : public Decorator
  {
  public:
    Repeat(Behaviour* child) : Decorator(child) {}

    void setCount(int count)
    {
      mCount = count;
    }

    void onInitialize()
    {
      mCounter = 0;
    }

    Status update()
    {
      for (;;)
      {
        mChild->tick();

        if (mChild->getStatus() == Status::RUNNING) {
          break;
        }

        if (mChild->getStatus() == Status::FAILURE) {
          return Status::FAILURE;
        }

        if (++mCounter == mCount) {
          return Status::SUCCESS;
        }

        mChild->reset();
      }

      return Status::INVALID;
    }

  protected:
    int mCount;
    int mCounter;
  };
}

#endif