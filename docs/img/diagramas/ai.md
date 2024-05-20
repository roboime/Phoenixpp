```
@startuml teste
class Skill {
    StateMachine stateMachine
}

class Tactic {
    vector<<Skill>> skills
}

class Role {
    vector<<Tactic>> tactics
}

class Play {
    vector<<Role>> roles
}

class AI {
    vector<<Play>> allPlays
    void cadastrarPlay()
}

class PlaySelection {
    vector<<Play>> allPlays
    Play selectPlay(FieldState fieldState)
}
class FieldState {
    vector<<Ball>> balls
    vector<<Robot>> blueRobots
    vector<<Robot>> yellowRobots
    FieldGeometry fieldGeometry
}

PlaySelection -- FieldState
Skill "1..*" -- "1" Tactic
Tactic "1..*" -- "1" Role
Role "1..*" -- "1" Play

note "Each Play, Role, Tactic and Skill implements\nIPlay, IRole, ITactic and ISkill" as N1
@enduml
```
