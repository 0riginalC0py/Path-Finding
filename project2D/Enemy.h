#pragma once
class Enemy
{
public:
	Enemy();
	~Enemy();



};



/*
For ai state machine

create a enum with names for behaviours
eg AI_WANDER

create a state variable within class.

make switch statement for each state within update

switch(*NameofEnum)
{
case AI_WANDER
FunctionName(float deltaTime);
break
}
Private:
//FunctionName(float deltaTime)
{

}

*/
