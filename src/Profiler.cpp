#include "Profiler.h"


namespace Mobius {


Mobius::Profiler::Profiler(const std::string& name, Mobius::Profiler::type type) 
 : name(name), profilerType(type) {
    switch (type) {
        case Profiler::type::TIMER:
            runTime.clear();
            break;
        case Profiler::type::MEMORY:
            // Begin memory tracking
            break;
    }
};

Profiler::~Profiler() {
    switch (profilerType) {
        case Profiler::type::TIMER:
            printf("[TIMER] \"%s\" took %fms.\n", name.c_str(), runTime.time(vex::timeUnits::msec));
            break;
        case Profiler::type::MEMORY:
            // Log memory tracking results
            break;
    }
};




} // namespace Mobius