#include "FreeParking.h"

FreeParking::FreeParking() : CornerField()
{}

void FreeParking::printLandingMessage() const
{
    std::cout << "You have landed on Free Parking. Enjoy!\n";
}

void FreeParking::printFieldInfo() const
{
    std::cout << "Free Parking";
}

bool FreeParking::action(SharedPtr<Player>& player)
{
    return true;
}