#include "Task.h"

#include "PlentyHealing.h"
#include "ll/api/service/Bedrock.h"
#include "ll/api/thread/ServerThreadExecutor.h"
#include "mc/world/actor/player/Player.h"
#include "mc/world/attribute/Attribute.h"
#include "mc/world/attribute/AttributeInstance.h"
#include "mc/world/attribute/SharedAttributes.h"
#include "mc/world/level/level.h"

#include <cmath>
#include <functional>
#include <memory>

namespace task {

    std::shared_ptr<ll::data::CancellableCallback> thisTask;

    // 10 ticks = 500ms
    static constexpr auto kInterval = std::chrono::milliseconds(500);

void execute() {
    ll::service::getLevel()->forEachPlayer([](Player &player) -> bool {
        auto saturation = player.getMutableAttribute(Player::SATURATION())->getCurrentValue();
        auto hunger     = player.getMutableAttribute(Player::HUNGER())->getCurrentValue();
        auto health     = player.getHealth();
        auto maxHealth  = player.getMaxHealth();

        if (hunger != 20 || saturation == 0 || health == maxHealth) return true;

        player.getMutableAttribute(SharedAttributes::HEALTH())->setCurrentValue(fmin(maxHealth, health + 1));
        auto exhaustion = player.getMutableAttribute(Player::EXHAUSTION());
        exhaustion->setCurrentValue(fmin(exhaustion->getCurrentValue() + 6, exhaustion->getMaxValue()));
        return true;
    });
}

void registerTask() {
    auto& executor = ll::thread::ServerThreadExecutor::getDefault();
    std::function<void()> repeat = [&executor, &repeat]() {
        execute();
        thisTask = executor.executeAfter(repeat, kInterval);
    };
    thisTask = executor.executeAfter(repeat, kInterval);
}

void unregisterTask() {
    if (thisTask) {
        thisTask->cancel();
        thisTask.reset();
    }
}

} // namespace task