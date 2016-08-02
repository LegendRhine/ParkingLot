/*
  ==============================================================================

    MainComponent.cpp
    Created: 1 Aug 2016 11:09:32am
    Author:  mit2000

  ==============================================================================
*/

#include "CommonData.h"
#include "MainComponent.h"
#include "ParkingLot.h"
#include "SetupPanel.h"

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible (parkinglot = new ParkingLot());
    addAndMakeVisible (setupPanel = new SetupPanel (parkinglot));

    setSize (1360, 800);
}

MainComponent::~MainComponent()
{
}

void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);

    g.setColour (Colours::yellow.withAlpha (0.4f));
    g.drawRect (setupPanel->getX(), 0, 3, getHeight());
    
    // draw stop-line
    if (!parkinglot->dontShowRestingCars())
    {
        g.setColour (Colours::yellow.withAlpha(0.5f));
        g.fillRect (CarLength + 25, 0, 5, getHeight());
        g.fillRect (parkinglot->getWidth() / 2 - CarWidth / 2 - 18, 0, 5, getHeight());
        g.fillRect (parkinglot->getWidth() / 2 + CarWidth / 2 + 13, 0, 5, getHeight());
        g.fillRect (parkinglot->getWidth() - CarLength - 28, 0, 5, getHeight());
    }
}

void MainComponent::resized()
{
    const int panelWidth = 230;

    parkinglot->setBounds (0, 0, getWidth() - panelWidth, getHeight());
    setupPanel->setBounds (getWidth() - panelWidth, 0, panelWidth, getHeight());
}
