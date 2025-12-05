// ======================================================================
// \title  LedBlinkerDeploymentTopologyDefs.hpp
// \brief required header file containing the required definitions for the topology autocoder
//
// ======================================================================
#ifndef LEDBLINKERDEPLOYMENT_LEDBLINKERDEPLOYMENTTOPOLOGYDEFS_HPP
#define LEDBLINKERDEPLOYMENT_LEDBLINKERDEPLOYMENTTOPOLOGYDEFS_HPP

// Include autocoded FPP constants
#include "HeaterBoard/LedBlinkerDeployment/Top/FppConstantsAc.hpp"

/**
 * \brief required ping constants
 *
 * The topology autocoder requires a WARN and FATAL constant definition for each component that supports the health-ping
 * interface. These are expressed as enum constants placed in a namespace named for the component instance. These
 * are all placed in the PingEntries namespace.
 *
 * Each constant specifies how many missed pings are allowed before a WARNING_HI/FATAL event is triggered. In the
 * following example, the health component will emit a WARNING_HI event if the component instance cmdDisp does not
 * respond for 3 pings and will FATAL if responses are not received after a total of 5 pings.
 *
 * ```c++
 * namespace PingEntries {
 * namespace cmdDisp {
 *     enum { WARN = 3, FATAL = 5 };
 * }
 * }
 * ```
 */
namespace PingEntries {
    namespace LedBlinkerDeployment_rateGroup1 {enum { WARN = 3, FATAL = 5 };}
}  // namespace PingEntries

// Definitions are placed within the same namespace as the FPP module that contains the topology.
namespace LedBlinkerDeployment {

/**
 * \brief required type definition to carry state
 *
 * The topology autocoder requires an object that carries state with the name `LedBlinkerDeployment::TopologyState`. Only the type
 * definition is required by the autocoder and the contents of this object are otherwise opaque to the autocoder. The
 * contents are entirely up to the definition of the project. This is a minimal embedded deployment.
 */
struct TopologyState {
    // Empty for this minimal deployment
};

namespace PingEntries = ::PingEntries;
}  // namespace LedBlinkerDeployment

#endif
