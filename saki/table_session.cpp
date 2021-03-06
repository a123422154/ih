#include "table_session.h"
#include "table_opob.h"

TableSession::TableSession(int id0, int id1, int id2, int id3)
{
	std::array<int, 4> girlIds { id0, id1, id2, id3 };
    mOpOb = new TableOpOb(girlIds);
}

TableSession::~TableSession()
{
    delete mOpOb;
}

std::vector<Mail> TableSession::Start() 
{
    return mOpOb->popMails();
}

std::vector<Mail> TableSession::Action(int who, 
                                       const std::string &actStr,
									   int actArg,
                                       const std::string &actTile) 
{
    mOpOb->action(who, actStr, actArg, actTile);
    return mOpOb->popMails();
}

std::vector<Mail> TableSession::SweepAll(int *targets) 
{
	std::vector<int> whos = mOpOb->sweepAll();
	*targets = 0;
	for (int w : whos)
		*targets |= (1 << w);
    return mOpOb->popMails();
}

std::vector<Mail> TableSession::SweepOne(int who)
{
    mOpOb->sweepOne(who);
    return mOpOb->popMails();
}

bool TableSession::GameOver() const
{
	return mOpOb->gameOver();
}

