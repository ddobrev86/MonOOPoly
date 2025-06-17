#include "AddPaymentCardCommand.h"

void AddPaymentCardCommand::execute(Monopoly* monopoly) const
{
    int value;
    std::cin >> value;

    monopoly->addPaymentCard(value);
    std::cout << "Payment Card added successfully\n";
}

Command* AddPaymentCardCommand::clone() const
{
    return new AddPaymentCardCommand(*this);
}
