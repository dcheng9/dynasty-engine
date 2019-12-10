#ifndef _CommandBase
#define _CommandBase

///
///	\ingroup OtherInternalGroup
///
class CommandBase
{
public:
	virtual ~CommandBase(){};
	virtual void execute() = 0;
};

#endif _CommandBase