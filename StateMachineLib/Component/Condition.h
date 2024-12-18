#pragma once

template <typename StateTemplate>
class Entity;

template <typename StateTemplate>
class Conditions
{
public:
	Conditions() {}
	virtual ~Conditions() {}
	virtual bool Test( Entity<StateTemplate>& entity) = 0;
};

