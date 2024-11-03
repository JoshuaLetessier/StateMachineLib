#pragma once

template <typename StateTemplate>

class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}

	virtual void Init() = 0;
	virtual void Update() = 0;

	void SetState(int state)
	{
		m_State = state;
	}

private:
	StateTemplate m_State;
};

