## Trabalho Extra - Branch "Extra"
- Deletei o CPPFromG e CPPCompiler neste branch porque estavam atrapalhando a compilação.
- Não consegui salvar componentes dentro de outros porque me atrapalhei com como conseguir o model para passar como parâmetro do construtor no processo de load.
- A mudança das chaves do PersistenceRecord para serem iguais aos getters é para, no futuro, utilizar como cpp, correto? Não vão ser problemáticos:
  - funções booleanas (is ao invés de get)?
  - momentos como no Assign, onde o field Assignments retorna apenas o tamanho, enquanto o getAssignments() retorna a lista toda?
- A chave do PersistenceRecord precisa ser única? Se sim, como ele lida com mais de uma instância de um mesmo componente ou com componentes diferentes, mas com o mesmo nome de atributo?
  - Se não, pra que utilizar o índice das listas como parte da chave? Para manter o ordenamento?

### Apenas igualados ao getter
- Assign
- Batch
  - Não sei se faltou _queue
- Decide
- Delay
  - Faltou refatorar os getters para começar com "get"
- Enter
- Leave
- QueueableItem
- Record
- Release
  - Faltou refatorar priority() para getPriority()
- Route
- SeizableItem
- Seize
- Write

- AssignmentItem
- DummyElement
- Label
- Queue
- Resource
  - Faltou salvar _capacitySchedule, \_failures e não sei se \_resourceEventHandlers
- Sequence
- Set
- Storage
- Variable


### Criados
- Clone
- DummyComponent
  - Faltou salvar o DummyElement
  - Faltaram getters e setters para os atributos, mas como é um Dummy, não sei se foi intencional.
- Match
  - Criado o load, o save foi apenas igualado ao getter
  - Não sei se faltaram _queues e _entitiesByAttrib
- PickStation
  - Faltou o _pickableStationItems
- Remove
  - Faltou _removeFrom
- Search
  - Faltou _searchIn
  - Acredito que exista um typo em "FounRank" e deveria ser "FoundRank"
- Signal
  - Faltou refatorar o getter de _limitExpression
- Wait
  - Não sei se faltou _queue e _signaldata
- Failure
  - Não sei se faltou _releaseCounts
  - Faltou _failingResources
- Schedule
  - Faltou _schedulableItems


### Faltando
- Create
  - ambos os _timeBetweenCreations
- PickableStationItem
- Process
  - save/load diferente do resto, não sei se apenas por ser antigo ou se existe um motivo
- EntityGroup
  - _groupmap?
- Formula
  - _formulaExpressions?
- SignalData
  - _signalDataEventHandlers?
