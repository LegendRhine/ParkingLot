/*
  ==============================================================================

    MainComponent.cpp
    Created: 1 Aug 2016 11:09:32am
    Author:  mit2000

  ==============================================================================
*/

#include "MainComponent.h"
#include "ParkingLot.h"
#include "SetupPanel.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (parkinglot = new ParkingLot());
    addAndMakeVisible (setupPanel = new SetupPanel (parkinglot));

    setSize (1280, 800);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);

    g.setColour (Colours::yellow.withAlpha (0.4f));
    g.drawRect (setupPanel->getX(), 0, 3, getHeight());
}

void MainComponent::resized()
{
    const int panelWidth = 230;

    parkinglot->setBounds (0, 0, getWidth() - panelWidth, getHeight());
    setupPanel->setBounds (getWidth() - panelWidth, 0, panelWidth, getHeight());
}
