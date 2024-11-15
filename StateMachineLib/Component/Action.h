#pragma once

#include "Entity.h"

template <typename StateTemplate>
class Actions {
public:
    Actions() : m_IsStarted(false) {}
    virtual ~Actions() = default;

    virtual void Start(Entity<StateTemplate>& entity) = 0; // Passer par référence pour éviter la copie
    virtual void Update(Entity<StateTemplate>& entity) = 0;
    virtual void End(Entity<StateTemplate>& entity) = 0;

    bool IsStarted() const { return m_IsStarted; }
    void SetStarted(bool started) { m_IsStarted = started; }

private:
    bool m_IsStarted;
};