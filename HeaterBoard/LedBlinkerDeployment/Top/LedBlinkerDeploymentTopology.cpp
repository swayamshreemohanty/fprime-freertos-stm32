// ======================================================================
// \title  LedBlinkerDeploymentTopology.cpp
// \brief cpp file containing the topology instantiation code
//
// ======================================================================
// Provides access to autocoded functions
#include <HeaterBoard/LedBlinkerDeployment/Top/LedBlinkerDeploymentTopologyAc.hpp>
// Note: Uncomment when using Svc:TlmPacketizer
//#include <HeaterBoard/LedBlinkerDeployment/Top/LedBlinkerDeploymentPacketsAc.hpp>

// Necessary project-specified types
#include <Fw/Types/MallocAllocator.hpp>

// Public functions for use in main program are namespaced with deployment module LedBlinkerDeployment
// This is also the namespace where the topology components are instantiated by FPP.
namespace LedBlinkerDeployment {

// The reference topology uses a single rate group: 1Hz
Svc::RateGroupDriver::DividerSet rateGroupDivisorsSet{{{1, 0}}};

// Rate group context tokens (unused in this minimal deployment)
U32 rateGroup1Context[Svc::ActiveRateGroup::CONNECTION_COUNT_MAX] = {};

/**
 * \brief configure/setup components in project-specific way
 *
 * This is a *helper* function which configures/sets up each component requiring project specific input.
 */
void configureTopology() {
    // Rate group driver needs a divisor list
    rateGroupDriver.configure(rateGroupDivisorsSet);

    // Rate group requires context array
    rateGroup1.configure(rateGroup1Context, FW_NUM_ARRAY_ELEMENTS(rateGroup1Context));
}

void setupTopology(const TopologyState& state) {
    // Autocoded initialization. Function provided by autocoder.
    initComponents(state);
    // Autocoded id setup. Function provided by autocoder.
    setBaseIds();
    // Autocoded connection wiring. Function provided by autocoder.
    connectComponents();
    // Autocoded command registration. Function provided by autocoder.
    regCommands();
    // Autocoded configuration. Function provided by autocoder.
    configComponents(state);
    // Project-specific component configuration. Function provided above.
    configureTopology();
    // Autocoded parameter loading. Function provided by autocoder.
    loadParameters();
    // Autocoded task kick-off (active components). Function provided by autocoder.
    startTasks(state);
}

void startRateGroups() {
    // For embedded FreeRTOS, the rate group driver is called directly in a loop
    // This function is a placeholder for compatibility
}

void stopRateGroups() {
    // Placeholder for compatibility
}

void teardownTopology(const TopologyState& state) {
    // Autocoded (active component) task clean-up. Functions provided by topology autocoder.
    stopTasks(state);
    freeThreads(state);

    tearDownComponents(state);
}
};  // namespace LedBlinkerDeployment
