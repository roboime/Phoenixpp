add_library(Structs
    environment.h
    referee_commands.h
    robot_commands.h
    robot_feedback_data.h
)
set_target_properties(Structs PROPERTIES LINKER_LANGUAGE CXX)