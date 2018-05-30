// Created by: Andrew Steven Michel
// Date Created: May 2018

// IMPORTED PACKAGES:
#include "StateMachine.h"

// Namespace declaration
namespace Drewski
{
	// Member functions

	// Function that pushes a state onto the stack
	void StateMachine::addState(StateRef newStateIn, bool isReplacingIn)
	{
		this->isAdding = true;
		this->isReplacing = isReplacingIn;
		this->newState = move(newStateIn);
	}

	// Function that removes prepares for a state removal
	void StateMachine::removeState()
	{
		this->isRemoving = true;
	}

	// Function that processes any added or removal of states
	void StateMachine::processStateChanges()
	{
		if (this->isRemoving && !this->states.empty())
		{
			this->states.pop();

			if (!this->states.empty())
			{
				this->states.top()->resume();
			}

			this->isRemoving = false;
		}

		if (this->isAdding)
		{
			if (!this->states.empty())
			{
				if (this->isReplacing)
				{
					this->states.pop();
				}
				else
				{
					this->states.top()->pause();
				}
			}

			this->states.push(move(this->newState));
			this->states.top()->init();
			this->isAdding = false;
		}
	}

	// Function that returns the top most state by reference
	StateRef &StateMachine::getActivateState()
	{
		return this->states.top();
	}

	// Function that returns the current size of the state stack
	int StateMachine::getStackSize()
	{
		return states.size();
	}
}