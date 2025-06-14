#include "LoadGameCommand.h"

void LoadGameCommand::execute(Monopoly* monopoly) const
{

}

Command* LoadGameCommand::clone() const
{
    return new LoadGameCommand();
}