#pragma once

#include <vector>

#include "Condition.h"
#include "StateBase.h"
#include "Transition.h"
#include "Component.h"
#include "Updatable.h"

#define DEBUG false

template<typename T>
class StateMachine : public Component{
private:

	int m_currentState = 0;
	std::vector<StateBase<T>*> m_states;
	std::vector<std::vector<Transition<T>*>> m_transitions;

public:
	void AddState(StateBase<T>* newState)
	{
		m_states.push_back(newState);

		m_transitions.resize(m_states.size());
	}

	void Update(T* type, float dt)
	{
		if (DEBUG == false)
			m_states[m_currentState]->Update(type, dt);

		std::vector<Transition<T>*>& transitions = m_transitions[m_currentState];
		for (int i = 0; i < transitions.size(); ++i)
		{
			int nextState = transitions[i]->TryTransition(type);
			if (nextState == -1)
				continue;

			TryTransitionTo(type, nextState);
			break;
		}
	}

	void TryTransitionTo(T* type, int nextState)
	{
		if (m_states[(int)nextState]->CanTransitionFrom(type, (int)m_currentState) == false)
			return;
		if (DEBUG == false)
			m_states[(int)m_currentState]->End(type);

		m_currentState = nextState;
		if (DEBUG == false)
			m_states[(int)m_currentState]->Start(type);
	}

	Transition<T>* AddTransition(int fromState, int toState)
	{
		Transition<T>* transition = new Transition<T>(toState);
		m_transitions[fromState].push_back(transition);

		return transition;
	}

	int GetState() const
	{
		return m_currentState;
	}
};