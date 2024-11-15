#pragma once

#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "Entity.h"
#include "Transition.h"
#include "Action.h"


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

	void AddEntity(std::unique_ptr<Entity<StateTemplate>> entity)
	{
		m_Entities.push_back(std::move(entity));
	}

	void AddTransition(StateTemplate state, std::unique_ptr<Transition<StateTemplate>> transition)
	{
		m_Transitions[state] = std::move(transition);
	}

	void AddAction(StateTemplate state, std::unique_ptr<Actions<StateTemplate>> action)
	{
		m_Actions[state] = std::move(action);
	}

	void AddConditionAction(StateTemplate state, std::unique_ptr<Conditions<StateTemplate>> condition) {
		m_ConditionActions[state] = std::move(condition);
	}

	void Update() {
		for (auto& entity : m_Entities) {
			StateTemplate currentState = entity->GetState();

			// V�rifie si l'action doit �tre d�marr�e (si elle n'a pas encore �t� d�marr�e)
			if (m_Actions.count(currentState) > 0) {
				auto& action = m_Actions[currentState];
				if (!action->IsStarted()) { // M�thode � ajouter dans Action pour v�rifier si elle a commenc�
					action->Start(*entity);
					action->SetStarted(true); // Marque l'action comme commenc�e
				}

				// Met � jour l'action si elle est active
				action->Update(*entity);
			}

			// V�rifie les transitions
			if (m_Transitions.count(currentState) > 0) {
				bool hasTransitioned = m_Transitions[currentState]->Try(entity.get());

				// Si une transition a eu lieu, appelle `End()` sur l'action actuelle et met � jour l'�tat de l'entit�
				if (hasTransitioned) {
					if (m_Actions.count(currentState) > 0) {
						m_Actions[currentState]->End(*entity);
						m_Actions[currentState]->SetStarted(false); // R�initialise l'�tat de l'action
					}
					// L'�tat de l'entit� devrait �tre mis � jour dans Try() ou ici apr�s la transition
				}
			}
		}
	}

private:
	std::vector<std::unique_ptr<Entity<StateTemplate>>> m_Entities;
	std::map<StateTemplate, std::unique_ptr<Transition<StateTemplate>>> m_Transitions;
	std::map<StateTemplate, std::unique_ptr<Conditions<StateTemplate>>> m_ConditionActions;
	std::map<StateTemplate, std::unique_ptr<Actions<StateTemplate>>> m_Actions;

};

