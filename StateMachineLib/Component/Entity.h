#pragma once

template <typename StateTemplate>

class Entity
{
public:
	Entity() {}
	virtual ~Entity() {}

	virtual void Init() = 0;
	virtual void Update() = 0;

	void SetState(StateTemplate state)
	{
		m_State = state;
	}

	StateTemplate GetState() const
	{
		return m_State;
	}

private:
	StateTemplate m_State;
};

