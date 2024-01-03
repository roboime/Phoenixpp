#ifndef PROTOBUF_FILES_H
#define PROTOBUF_FILES_H

#if __has_include("target/game_event.pb.h")
#include "target/game_event.pb.h"
#else
#warning "target/game_event.pb.h" was not found.
#endif

#if __has_include("target/grSim_Commands.pb.h")
#include "target/grSim_Commands.pb.h"
#else
#warning "target/grSim_Commands.pb.h" was not found.
#endif

#if __has_include("target/grSim_Packet.pb.h")
#include "target/grSim_Packet.pb.h"
#else
#warning "target/grSim_Packet.pb.h" was not found.
#endif

#if __has_include("target/grSim_Replacement.pb.h")
#include "target/grSim_Replacement.pb.h"
#else
#warning "target/grSim_Replacement.pb.h" was not found.
#endif

#if __has_include("target/messages_robocup_ssl_detection.pb.h")
#include "target/messages_robocup_ssl_detection.pb.h"
#else
#warning "target/messages_robocup_ssl_detection.pb.h" was not found.
#endif

#if __has_include("target/messages_robocup_ssl_detection_tracked.pb.h")
#include "target/messages_robocup_ssl_detection_tracked.pb.h"
#else
#warning "target/messages_robocup_ssl_detection_tracked.pb.h" was not found.
#endif

#if __has_include("target/messages_robocup_ssl_geometry.pb.h")
#include "target/messages_robocup_ssl_geometry.pb.h"
#else
#warning "target/messages_robocup_ssl_geometry.pb.h" was not found.
#endif

#if __has_include("target/messages_robocup_ssl_geometry_legacy.pb.h")
#include "target/messages_robocup_ssl_geometry_legacy.pb.h"
#else
#warning "target/messages_robocup_ssl_geometry_legacy.pb.h" was not found.
#endif

#if __has_include("target/messages_robocup_ssl_refbox_log.pb.h")
#include "target/messages_robocup_ssl_refbox_log.pb.h"
#else
#warning "target/messages_robocup_ssl_refbox_log.pb.h" was not found.
#endif

#if __has_include("target/messages_robocup_ssl_wrapper.pb.h")
#include "target/messages_robocup_ssl_wrapper.pb.h"
#else
#warning "target/messages_robocup_ssl_wrapper.pb.h" was not found.
#endif

#if __has_include("target/messages_robocup_ssl_wrapper_legacy.pb.h")
#include "target/messages_robocup_ssl_wrapper_legacy.pb.h"
#else
#warning "target/messages_robocup_ssl_wrapper_legacy.pb.h" was not found.
#endif

#if __has_include("target/messages_robocup_ssl_wrapper_tracked.pb.h")
#include "target/messages_robocup_ssl_wrapper_tracked.pb.h"
#else
#warning "target/messages_robocup_ssl_wrapper_tracked.pb.h" was not found.
#endif

#if __has_include("target/rcon.pb.h")
#include "target/rcon.pb.h"
#else
#warning "target/rcon.pb.h" was not found.
#endif

#if __has_include("target/referee.pb.h")
#include "target/referee.pb.h"
#else
#warning "target/referee.pb.h" was not found.
#endif

#if __has_include("target/savestate.pb.h")
#include "target/savestate.pb.h"
#else
#warning "target/savestate.pb.h" was not found.
#endif

#endif // PROTOBUF_FILES_H
