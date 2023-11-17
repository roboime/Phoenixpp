QT       += core gui network

unix: LIBS += -lprotobuf

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    target/game_event.pb.cc \
    target/grSim_Commands.pb.cc \
    target/grSim_Packet.pb.cc \
    target/grSim_Replacement.pb.cc \
    target/messages_robocup_ssl_detection.pb.cc \
    target/messages_robocup_ssl_detection_tracked.pb.cc \
    target/messages_robocup_ssl_geometry.pb.cc \
    target/messages_robocup_ssl_geometry_legacy.pb.cc \
    target/messages_robocup_ssl_refbox_log.pb.cc \
    target/messages_robocup_ssl_wrapper.pb.cc \
    target/messages_robocup_ssl_wrapper_legacy.pb.cc \
    target/messages_robocup_ssl_wrapper_tracked.pb.cc \
    target/rcon.pb.cc \
    target/referee.pb.cc \
    target/savestate.pb.cc \
    widget.cpp

HEADERS += \
    protobuf_files.h \
    target/game_event.pb.h \
    target/grSim_Commands.pb.h \
    target/grSim_Packet.pb.h \
    target/grSim_Replacement.pb.h \
    target/messages_robocup_ssl_detection.pb.h \
    target/messages_robocup_ssl_detection_tracked.pb.h \
    target/messages_robocup_ssl_geometry.pb.h \
    target/messages_robocup_ssl_geometry_legacy.pb.h \
    target/messages_robocup_ssl_refbox_log.pb.h \
    target/messages_robocup_ssl_wrapper.pb.h \
    target/messages_robocup_ssl_wrapper_legacy.pb.h \
    target/messages_robocup_ssl_wrapper_tracked.pb.h \
    target/rcon.pb.h \
    target/referee.pb.h \
    target/savestate.pb.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    proto/compile.sh \
    proto/game_event.proto \
    proto/grSim_Commands.proto \
    proto/grSim_Packet.proto \
    proto/grSim_Replacement.proto \
    proto/messages_robocup_ssl_detection.proto \
    proto/messages_robocup_ssl_detection_tracked.proto \
    proto/messages_robocup_ssl_geometry.proto \
    proto/messages_robocup_ssl_geometry_legacy.proto \
    proto/messages_robocup_ssl_refbox_log.proto \
    proto/messages_robocup_ssl_wrapper.proto \
    proto/messages_robocup_ssl_wrapper_legacy.proto \
    proto/messages_robocup_ssl_wrapper_tracked.proto \
    proto/rcon.proto \
    proto/referee.proto \
    proto/savestate.proto
