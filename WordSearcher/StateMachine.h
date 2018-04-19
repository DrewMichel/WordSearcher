#ifndef DREW_STATE_MACHINE_H
#define DREW_STATE_MACHINE_H

#include <memory>
#include <stack>

#include "State.h"

using namespace std;

namespace Drewski
{
	typedef std::unique_ptr<State> StateRef;

	class StateMachine
	{
		public:
			StateMachine(){}
			~StateMachine(){}

			void addState(StateRef newStateIn, bool isReplacingIn = true);
			void removeState();

			void processStateChanges();

			StateRef &getActivateState();

			int getStackSize();

		private:
			stack<StateRef> states;
			StateRef newState;

			bool isRemoving;
			bool isAdding;
			bool isReplacing;

	};
}

#endif