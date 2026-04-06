#include "mod/PlentyHealing.h"

#include "PlentyHealing.h"
#include "ll/api/mod/RegisterHelper.h"

#include <memory>

namespace plenty_healing {

static std::unique_ptr<PlentyHealing> instance;

PlentyHealing &PlentyHealing::getInstance() { return *instance; }

bool PlentyHealing::load() {
    instance = std::make_unique<PlentyHealing>();
    return true;
}

bool PlentyHealing::enable() {
    task::registerTask();
    return true;
}

bool PlentyHealing::disable() {
    task::unregisterTask();
    return true;
}

} // namespace plenty_healing

LL_REGISTER_MOD(plenty_healing::PlentyHealing, *plenty_healing::instance);