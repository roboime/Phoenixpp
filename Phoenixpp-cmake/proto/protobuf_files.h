#ifndef PROTOBUF_FILES_H
#define PROTOBUF_FILES_H

#if __has_include("game_event.pb.h")
#include "game_event.pb.h"
#else
#warning "game_event.pb.h" was not found.
#endif

#if __has_include("grSim_Commands.pb.h")
#include "grSim_Commands.pb.h"
#else
#warning "grSim_Commands.pb.h" was not found.
#endif

#if __has_include("grSim_Packet.pb.h")
#include "grSim_Packet.pb.h"
#else
#warning "grSim_Packet.pb.h" was not found.
#endif

#if __has_include("grSim_Replacement.pb.h")
#include "grSim_Replacement.pb.h"
#else
#warning "grSim_Replacement.pb.h" was not found.
#endif

#if __has_include("messages_robocup_ssl_detection.pb.h")
#include "messages_robocup_ssl_detection.pb.h"
#else
#warning "messages_robocup_ssl_detection.pb.h" was not found.
#endif

#if __has_include("messages_robocup_ssl_detection_tracked.pb.h")
#include "messages_robocup_ssl_detection_tracked.pb.h"
#else
#warning "messages_robocup_ssl_detection_tracked.pb.h" was not found.
#endif

#if __has_include("messages_robocup_ssl_geometry.pb.h")
#include "messages_robocup_ssl_geometry.pb.h"
#else
#warning "messages_robocup_ssl_geometry.pb.h" was not found.
#endif

#if __has_include("messages_robocup_ssl_geometry_legacy.pb.h")
#include "messages_robocup_ssl_geometry_legacy.pb.h"
#else
#warning "messages_robocup_ssl_geometry_legacy.pb.h" was not found.
#endif

#if __has_include("messages_robocup_ssl_refbox_log.pb.h")
#include "messages_robocup_ssl_refbox_log.pb.h"
#else
#warning "messages_robocup_ssl_refbox_log.pb.h" was not found.
#endif

#if __has_include("messages_robocup_ssl_wrapper.pb.h")
#include "messages_robocup_ssl_wrapper.pb.h"
#else
#warning "messages_robocup_ssl_wrapper.pb.h" was not found.
#endif

#if __has_include("messages_robocup_ssl_wrapper_legacy.pb.h")
#include "messages_robocup_ssl_wrapper_legacy.pb.h"
#else
#warning "messages_robocup_ssl_wrapper_legacy.pb.h" was not found.
#endif
/*
#if __has_include("messages_robocup_ssl_wrapper_tracked.pb.h")
#include "messages_robocup_ssl_wrapper_tracked.pb.h"
#else
#warning "messages_robocup_ssl_wrapper_tracked.pb.h" was not found.
#endif
*/
#if __has_include("rcon.pb.h")
#include "rcon.pb.h"
#else
#warning "rcon.pb.h" was not found.
#endif

#if __has_include("referee.pb.h")
#include "referee.pb.h"
#else
#warning "referee.pb.h" was not found.
#endif

#if __has_include("savestate.pb.h")
#include "savestate.pb.h"
#else
#warning "savestate.pb.h" was not found.
#endif

#endif // PROTOBUF_FILES_H
