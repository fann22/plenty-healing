#pragma once

#include "ll/api/thread/ServerThreadExecutor.h"
#include "ll/api/data/CancellableCallback.h"

#include <memory>

namespace task {

    extern std::shared_ptr<ll::data::CancellableCallback> thisTask;

    void registerTask();

    void unregisterTask();

    void execute();

};