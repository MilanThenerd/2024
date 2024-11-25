#include "RiverbankFactory.h"

LegionUnit *RiverbankFactory::createInfantry()
{
    LegionUnit *infantry = new Infantry();
    LegionUnit *riverbank = new Riverbank(*infantry);
    return riverbank;
}

LegionUnit *RiverbankFactory::createCavalry()
{
    LegionUnit *cavalry = new Cavalry();
    LegionUnit *riverbank = new Riverbank(*cavalry);
    return riverbank;
}

LegionUnit *RiverbankFactory::createArtillery()
{
    LegionUnit *artillery = new Artillery();
    LegionUnit *riverbank = new Riverbank(*artillery);
    return riverbank;
}