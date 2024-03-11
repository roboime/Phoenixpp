add_library(Messages
    environment.h
    referee_commands.h
    robot_commands.h
    robot_feedback_data.h
)
set_target_properties(Messages PROPERTIES LINKER_LANGUAGE CXX)
