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
MainComponent::MainComponent() :
    showPanel (true)
{

    addAndMakeVisible (parkinglot = new ParkingLot());
    addAndMakeVisible (setupPanel = new SetupPanel (parkinglot));
    addAndMakeVisible (showPanelBt = new TextButton (">|"));
    showPanelBt->addListener (this);

    setSize (1360, 800);
    openGL.attachTo (*this);
}

//==============================================================================
MainComponent::~MainComponent()
{
    openGL.detach();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);

    g.setColour (Colours::yellow.withAlpha (0.4f));
    g.drawRect (setupPanel->getX(), 0, 3, getHeight());
    
    // draw stop-line of parking mode
    if (!parkinglot->dontShowRestingCars())
    {
        g.setColour (Colours::yellow.withAlpha(0.5f));
        g.fillRect (CarLength + 25, 0, 5, getHeight());
        g.fillRect (parkinglot->getWidth() / 2 - CarWidth / 2 - 18, 0, 5, getHeight());
        g.fillRect (parkinglot->getWidth() / 2 + CarWidth / 2 + 13, 0, 5, getHeight());
        g.fillRect (parkinglot->getWidth() - CarLength - 28, 0, 5, getHeight());
    }
}

//==============================================================================
void MainComponent::resized()
{
    const int panelWidth = showPanel ? 230 : 0;

    parkinglot->setBounds (0, 0, getWidth() - panelWidth, getHeight());
    setupPanel->setBounds (getWidth() - panelWidth, 0, panelWidth, getHeight()); 
    showPanelBt->setBounds (getWidth() - 40, getHeight() - 30, 30, 25);

    setupPanel->setWantsKeyboardFocus (false);
    parkinglot->setWantsKeyboardFocus (true);
    parkinglot->grabKeyboardFocus();
}

//==============================================================================
void MainComponent::buttonClicked (Button* bt)
{
    if (bt == showPanelBt)
    {
        showPanel = !showPanel;
        showPanelBt->setButtonText (showPanel ? ">|" : "|<");
        resized();
    }
}
