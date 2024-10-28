# Documentation de Conception

## Patterns de Conception
### Command Pattern
Utilisé pour :
- Réversibilité des opérations
- Traçabilité des changements
- Audit de sécurité

### State Pattern
Implémente :
- Validation des transitions
- Encapsulation des règles métier
- Séparation des responsabilités

### Observer Pattern
Via boost::signals2 pour :
- Notification des changements d'état
- Découplage des composants
- Monitoring en temps réel

## Architecture
```mermaid
flowchart TB
    Client[Client] --> RS[RailwaySignal]
    RS --> State[SignalState]
    RS --> Command[SignalCommand]
    RS --> Timer[SafetyTimer]
    RS --> Validator[StateValidator]
    State --> |Validation| Validator
    Command --> |Exécution| RS
    RS --> |Notification| Observer[Observateurs]
```

## Flux de Données
### Changement d'État
```mermaid
sequenceDiagram
    participant Client
    participant Signal as RailwaySignal
    participant Command as ChangeAspectCommand
    participant State as SignalState
    participant Validator as StateValidator

    Client->>Signal: executeCommand(changeAspect)
    Signal->>Command: execute()
    Command->>Signal: setAspect()
    Signal->>State: canTransitionTo()
    State->>Validator: validateTransition()
    Validator-->>State: Résultat
    State-->>Signal: Résultat
    Signal->>Signal: updateState()
    Signal->>Observer: notifyChange()
```
