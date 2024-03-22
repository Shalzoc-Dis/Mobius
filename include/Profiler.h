#pragma once

#include <vex.h>
#include <string>

namespace Mobius {

struct Profiler {
    enum class type { TIMER, MEMORY };

    Profiler() {};
    Profiler(const std::string& name, Mobius::Profiler::type type);
    ~Profiler();



    private:
    std::string name;
    Mobius::Profiler::type profilerType;
    vex::timer runTime;
};




} // namespace Mobius