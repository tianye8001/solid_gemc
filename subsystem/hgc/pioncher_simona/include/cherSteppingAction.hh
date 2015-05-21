#ifndef cherSteppingAction_H
#define cherSteppingAction_H 1

#include "G4UserSteppingAction.hh"

class cherSteppingAction : public G4UserSteppingAction
{
	public:
		cherSteppingAction();
		~cherSteppingAction();

	public:
		void UserSteppingAction(const G4Step*);
};

#endif
