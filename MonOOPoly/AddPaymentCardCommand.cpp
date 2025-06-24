#include "AddPaymentCardCommand.h"

void AddPaymentCardCommand::execute(Monopoly* monopoly)
{
    int value;

    std::cout << "Enter amount(positive or negative): ";
    std::cin >> value;

    monopoly->addPaymentCard(value);

    system("cls");
    std::cout << "Payment Card added successfully\n";
}

Command* AddPaymentCardCommand::clone() const
{
    return new AddPaymentCardCommand(*this);
}
