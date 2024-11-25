#include "OpenFieldFactory.h"

LegionUnit *OpenFieldFactory::createInfantry()
{
    LegionUnit *infantry = new Infantry();
    LegionUnit *openField = new OpenField(*infantry);
    return openField;
}

LegionUnit *OpenFieldFactory::createCavalry()
{
    LegionUnit *cavalry = new Cavalry();
    LegionUnit *openField = new OpenField(*cavalry);
    return openField;
}

LegionUnit *OpenFieldFactory::createArtillery()
{
    LegionUnit *artillery = new Artillery();
    LegionUnit *openField = new OpenField(*artillery);
    return openField;
}