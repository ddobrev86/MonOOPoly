#include "AddGroupPaymentCardCommand.h"

void AddGroupPaymentCardCommand::execute(Monopoly* monopoly)
{
    int value;
    std::cin >> value;

    monopoly->addGroupPaymentCard(value);

    system("cls");
    std::cout << "Group Payment Card added successfully\n";
}

Command* AddGroupPaymentCardCommand::clone() const
{
    return new AddGroupPaymentCardCommand(*this);
}
