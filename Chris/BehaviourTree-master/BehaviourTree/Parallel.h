#ifndef BH_PARALLEL
#define BH_PARALLEL

#include "Composite.h"

namespace BehaviourTree
{
  class Parallel : public Composite
  {
  public:
    enum class Policy { REQUIRE_ONE, REQUIRE_ALL };

    Parallel(Policy forSuccess, Policy forFailure)
      : mSuccessPolicy(forSuccess), mFailurePolicy(forFailure)
    { }

    virtual ~Parallel() {}

  protected:
    Policy mSuccessPolicy;
    Policy mFailurePolicy;

    virtual Status update() override
    {
      size_t iSuccessCount = 0, iFailureCount = 0;

      for (Behaviours::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
      {
        Behaviour &b = **it;
        if (!b.isTerminated()){
          b.tick();
        }

        if (b.getStatus() == Status::SUCCESS) {
          ++iSuccessCount;
          if (mSuccessPolicy == Policy::REQUIRE_ONE) {
            return Status::SUCCESS;
          }
        }

        if (b.getStatus() == Status::FAILURE) {
          ++iFailureCount;
          if (mFailurePolicy == Policy::REQUIRE_ONE) {
            return Status::FAILURE;
          }
        }
      }

      if (mFailurePolicy == Policy::REQUIRE_ALL && iFailureCount == mChildren.size()) {
        return Status::FAILURE;
      }

      if (mSuccessPolicy == Policy::REQUIRE_ALL && iSuccessCount == mChildren.size()) {
        return Status::SUCCESS;
      }

      return Status::RUNNING;
    }

    virtual void onTerminate(Status) override
    {
      for (Behaviours::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
        Behaviour &b = **it;
        if (b.isRunning()) {
          b.abort();
        }
      }
    }
  };
}

#endif