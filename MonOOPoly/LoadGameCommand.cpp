#include "LoadGameCommand.h"

void LoadGameCommand::execute(Monopoly* monopoly)
{

}

Command* LoadGameCommand::clone() const
{
    return new LoadGameCommand();
}