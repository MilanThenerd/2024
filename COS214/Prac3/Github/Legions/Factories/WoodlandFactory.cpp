#include "WoodlandFactory.h"

LegionUnit *WoodlandFactory::createInfantry()
{
    LegionUnit *infantry = new Infantry(player);
    LegionUnit *woodland = new Woodland(*infantry);
    return woodland;
}

LegionUnit *WoodlandFactory::createCavalry()
{
    LegionUnit *cavalry = new Cavalry(player);
    LegionUnit *woodland = new Woodland(*cavalry);
    return woodland;
}

LegionUnit *WoodlandFactory::createArtillery()
{
    LegionUnit *artillery = new Artillery(player);
    LegionUnit *woodland = new Woodland(*artillery);
    return woodland;
}