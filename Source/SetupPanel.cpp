/*
  ==============================================================================

    SetupPanel.cpp
    Created: 1 Aug 2016 11:10:22am
    Author:  mit2000

  ==============================================================================
*/

#include "SetupPanel.h"

//==============================================================================
SetupPanel::SetupPanel (ParkingLot* const parkinglot_)
    : parkinglot (parkinglot_)
{

}

SetupPanel::~SetupPanel()
{
}

void SetupPanel::paint (Graphics& g)
{
    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText ("SetupPanel", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void SetupPanel::resized()
{

}
