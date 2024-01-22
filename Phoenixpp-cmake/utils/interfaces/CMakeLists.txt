add_library(Interfaces
    communicator.h
    logic.h
    referee.h
    robot_feedback.h
    vision.h
)
set_target_properties(Interfaces PROPERTIES LINKER_LANGUAGE CXX)