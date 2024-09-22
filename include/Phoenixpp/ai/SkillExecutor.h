//
// Created by lucas on 20/09/2024.
//

#ifndef SKILLEXECUTOR_H
#define SKILLEXECUTOR_H

namespace phoenixpp::ai {

    class SkillExecutor {
    public:
        static void executeSkills(const std::map<unsigned int, Role>& rolesMap, messaging::EnvironmentPtr environment) {
            for (auto& pair : rolesMap) {
                Role role = pair.second;
                role.execute(environment);
            }
        }
    };
}

#endif //SKILLEXECUTOR_H
