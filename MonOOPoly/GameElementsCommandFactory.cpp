#include "GameElementsCommandFactory.h"
#include "AddPlayerCommand.h"
#include "AddPropertyFamilyCommand.h"
#include "AddPropertyCommand.h"
#include "AddStationCommand.h"
#include "AddFacilityCommand.h"
#include "AddCardFieldCommand.h"
#include "AddMoveCardCommand.h"
#include "AddPaymentCardCommand.h"
#include "AddGroupPaymentCardCommand.h"

Command* GameElementsCommandFactory::createCommand(const MyString& command)
{
    if (command == "add_player")
        return new AddPlayerCommand();
    else if (command == "add_property_family")
        return new AddPropertyFamilyCommand();
    else if (command == "add_property")
        return new AddPropertyCommand();
    else if (command == "add_station")
        return new AddStationCommand();
    else if (command == "add_facility")
        return new AddFacilityCommand();
    else if (command == "add_card_field")
        return new AddCardFieldCommand();
    else if (command == "add_movement_card")
        return new AddMoveCardCommand();
    else if (command == "add_payment_card")
        return new AddPaymentCardCommand();
    else if (command == "add_group_payment_card")
        return new AddGroupPaymentCardCommand();

    return nullptr;
}
