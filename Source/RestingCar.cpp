/*
  ==============================================================================

    RestingCar.cpp
    Created: 31 Jul 2016 8:19:56pm
    Author:  mit2000

  ==============================================================================
*/

#include "CommonData.h"
#include "RestingCar.h"

//==============================================================================
RestingCar::RestingCar() 
    : cl (Random::getSystemRandom().nextFloat(), 0.8f, 0.55f, 1.0f)
{
    //setSize (CarWidth, CarLength);
}

RestingCar::~RestingCar()
{
}
//=========================================================================
void RestingCar::paint (Graphics& g)
{
    // whole car
    g.setColour (cl);
    g.fillRoundedRectangle (getLocalBounds ().toFloat (), 8.0f);

    // border
    g.setColour (Colours::lightgrey);
    g.drawRoundedRectangle (getLocalBounds ().toFloat (), 8.0f, 0.5f);
}

void RestingCar::resized()
{
    
}
