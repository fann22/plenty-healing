#pragma once

#include "Task.h"

namespace plenty_healing {

class PlentyHealing {

public:
    static PlentyHealing &getInstance();

    PlentyHealing() = default;

    /// @return True if the mod is loaded successfully.
    bool load();

    /// @return True if the mod is enabled successfully.
    bool enable();

    /// @return True if the mod is disabled successfully.
    bool disable();
};

} // namespace plenty_healing