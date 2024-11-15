#pragma once

#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "Entity.h"
#include "Condition.h"

template <typename StateTemplate>

class Transition
{
public:
    virtual ~Transition()
	{
	}

    bool Try(Entity<StateTemplate>* entity) {
        int true_conditions = 0;
        for (auto& condition : m_Conditions) {
            true_conditions += condition->Test(*entity);
        }
        if (true_conditions != 0 && true_conditions == m_Conditions.size()) {
            entity->SetState(m_TargetState);
            return true;
        }
        return false;
    }

    void setTargetState(StateTemplate target_state)
	{
		m_TargetState = target_state;
    }
    void AddCondition(std::unique_ptr<Conditions<StateTemplate>> condition)
    {
		m_Conditions.push_back(std::move(condition));
    }

protected:
	StateTemplate m_TargetState;
    std::vector<std::unique_ptr<Conditions<StateTemplate>>> m_Conditions;
};

