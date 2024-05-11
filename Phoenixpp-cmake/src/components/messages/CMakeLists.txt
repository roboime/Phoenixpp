add_library(Messages
    raw_environment.h
    referee_commands.h
    robot_commands.h
    robot_feedback_data.h
    robot_path.h
    robot_decision.h
    dummy_message.h
)
set_target_properties(Messages PROPERTIES LINKER_LANGUAGE CXX)
