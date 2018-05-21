#ifndef DREW_STATE_MACHINE_H
#define DREW_STATE_MACHINE_H

// IMPORTED PACKAGES:
#include <memory>
#include <stack>
#include "State.h"

// Namespace usage which allows the direct use of declarations
using namespace std;

// Namespace declaration
namespace Drewski
{
	// Creates a type definition of a unique pointer to a state as StateRef
	typedef std::unique_ptr<State> StateRef;

	// Class that is responsible for managing state objects via a stack
	class StateMachine
	{
		private:
			// Member variables
			stack<StateRef> states;
			StateRef newState;

			bool isRemoving;
			bool isAdding;
			bool isReplacing;

		public:
			// Constructor
			StateMachine(){}

			// Destructor
			~StateMachine(){}

			// Member functions
			void addState(StateRef newStateIn, bool isReplacingIn = true);
			void removeState();

			void processStateChanges();

			StateRef &getActivateState();

			int getStackSize();
	};
}

#endif