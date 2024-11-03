#pragma once

#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "Entity.h"
#include "Transitions.h"
#include "Actions.h"


template <typename StateTemplate>

class Behavior
{
public:
	Behavior()
	{
	}

	~Behavior()
	{
	}

	void AddEntity(std::unique_ptr<Entity> entity)
	{
		m_Entities.push_back(std::move(entity));
	}

	void AddTransition(StateTemplate state, std::unique_ptr<Transition> transition)
	{
		m_Transitions[state] = std::move(transition);
	}

	void AddAction(StateTemplate state, std::unique_ptr<Action> action)
	{
		m_Actions[state] = std::move(action);
	}

	void AddConditionAction(StateTemplate state, std::unique_ptr<Conditions<StateTemplate>> condition) {
		m_ConditionActions[state] = std::move(condition);
	}

	void Start()
	{
		// Start all entities
	}

	void Update()
	{
		for (auto& entity : m_Entities) {
			StateTemplate currentState = entity->GetState();

			// Vérifie les conditions d'action
			if (m_ConditionActions.count(currentState) > 0 && m_ConditionActions[currentState]->Test(*entity)) {
				if (m_Actions.count(currentState) > 0) {
					m_Actions[currentState]->Start();
					m_Actions[currentState]->Update();
					m_Actions[currentState]->End();
				}
			}

			// Vérifie les transitions
			if (m_Transitions.count(currentState) > 0) {
				m_Transitions[currentState]->Try(entity.get());
			}
		}
	}

	void Stop()
	{
		// Stop all entities
	}
private:
	std::vector<std::unique_ptr<Entity>> m_Entities;
	std::map<StateTemplate, std::unique_ptr<Transition>> m_Transitions;
	std::map<StateTemplate, std::unique_ptr<ConditionActions>> m_ConditionActions;
	std::map<StateTemplate, std::unique_ptr<Action>> m_Actions;

};

