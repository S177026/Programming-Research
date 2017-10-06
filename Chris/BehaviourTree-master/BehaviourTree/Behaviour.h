#ifndef BH_BEHAVIOUR
#define BH_BEHAVIOUR

#include "Status.h"

namespace BehaviourTree
{
  class Behaviour
  {
  public:
    Behaviour() : mStatus(Status::INVALID) {}

    virtual ~Behaviour() {}

    virtual Status update() = 0;

    virtual void onInitialize() { }

    virtual void onTerminate(Status) { }

    Status tick()
    {
      if (mStatus != Status::RUNNING) {
        onInitialize();
      }

      mStatus = update();

      if (mStatus != Status::RUNNING) {
        onTerminate(mStatus);
      }

      return mStatus;
    }

    void reset()
    {
      mStatus = Status::INVALID;
    }

    void abort()
    {
      onTerminate(Status::ABORTED);
      mStatus = Status::ABORTED;
    }

    bool isTerminated() const
    {
      return mStatus == Status::SUCCESS || mStatus == Status::FAILURE;
    }

    bool isRunning() const
    {
      return mStatus == Status::RUNNING;
    }

    Status getStatus() const
    {
      return mStatus;
    }

  private:
    Status mStatus;
  };
}

#endif