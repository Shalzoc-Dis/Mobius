#pragma once

#include <vex.h>
#include <string>

namespace Mobius {

// This is a simple profiler class to measure things like time taken or memory used
struct Profiler {
    // Type of profiler
    enum class type { TIMER, MEMORY };

    Profiler() {};
    // @param name The name of the profiler (usually the function name)
    // @param type The type of the profiler
    Profiler(const std::string& name, Profiler::type type);
    ~Profiler();



    private:
    // The name of the profiler (usually the function name)
    std::string name;
    // The type of the profiler
    Profiler::type profilerType;
    // The time the profiler was started
    vex::timer runTime;
};




} // namespace Mobius