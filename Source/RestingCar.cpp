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
    : cl (Random::getSystemRandom().nextFloat(), 0.8f, 0.4f, 1.0f)
{
    //setSize (CarWidth, CarLength);
    setWantsKeyboardFocus(false);
}

RestingCar::~RestingCar()
{
}
//=========================================================================
void RestingCar::paint (Graphics& g)
{
    // whole car
    g.setColour (cl);
    g.fillRoundedRectangle (getLocalBounds ().toFloat (), 10.0f);

    // border
    g.setColour (Colours::grey);
    g.drawRoundedRectangle (getLocalBounds ().toFloat (), 10.0f, 0.6f);
}

void RestingCar::resized()
{
    
}

void RestingCar::mouseUp (const MouseEvent& e)
{
    getParentComponent()->mouseUp (e);
}
