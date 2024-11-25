#include "RiverbankFactory.h"

LegionUnit *RiverbankFactory::createInfantry()
{
    LegionUnit *infantry = new Infantry(player);
    LegionUnit *riverbank = new Riverbank(*infantry);
    return riverbank;
}

LegionUnit *RiverbankFactory::createCavalry()
{
    LegionUnit *cavalry = new Cavalry(player);
    LegionUnit *riverbank = new Riverbank(*cavalry);
    return riverbank;
}

LegionUnit *RiverbankFactory::createArtillery()
{
    LegionUnit *artillery = new Artillery(player);
    LegionUnit *riverbank = new Riverbank(*artillery);
    return riverbank;
}