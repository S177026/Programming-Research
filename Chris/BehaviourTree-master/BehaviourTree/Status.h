#ifndef BH_STATUS
#define BH_STATUS

namespace BehaviourTree
{
  enum class Status
  {
    INVALID,
    SUCCESS,
    FAILURE,
    RUNNING,
    ABORTED
  };
}

#endif // BH_STATUS