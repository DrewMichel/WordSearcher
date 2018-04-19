#include "StateMachine.h"

namespace Drewski
{
	void StateMachine::addState(StateRef newStateIn, bool isReplacingIn)
	{
		this->isAdding = true;
		this->isReplacing = isReplacingIn;
		this->newState = move(newStateIn);
	}

	void StateMachine::removeState()
	{
		this->isRemoving = true;
	}

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

	StateRef &StateMachine::getActivateState()
	{
		return this->states.top();
	}

	int StateMachine::getStackSize()
	{
		return states.size();
	}
}