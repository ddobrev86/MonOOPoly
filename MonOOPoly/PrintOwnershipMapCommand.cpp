#include "PrintOwnershipMapCommand.h"

void PrintOwnershipMapCommand::execute(Monopoly* monopoly) const
{
    monopoly->printOwnershipMap();
}

Command* PrintOwnershipMapCommand::clone() const
{
    return new PrintOwnershipMapCommand(*this);
}
