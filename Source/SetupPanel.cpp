﻿/*
  ==============================================================================

    SetupPanel.cpp
    Created: 1 Aug 2016 11:10:22am
    Author:  mit2000

  ==============================================================================
*/

#include "SetupPanel.h"
#include "ParkingLot.h"

//==============================================================================
SetupPanel::SetupPanel (ParkingLot* const parkinglot_)
    : parkinglot (parkinglot_)
{
    // labels..
    addAndMakeVisible (nameLb = new Label ("nameLabel", ProjectInfo::projectName));
    nameLb->setFont (Font (25.0f));
    nameLb->setJustificationType (Justification::centredBottom);
    nameLb->setColour (Label::textColourId, Colours::lightgrey);

    addAndMakeVisible (versionLb = new Label ("versionLabel", ProjectInfo::versionString));
    versionLb->setFont (Font (15.0f));
    versionLb->setJustificationType (Justification::centredBottom);
    versionLb->setColour (Label::textColourId, Colours::lightgrey);

    // reset button
    addAndMakeVisible (resetBt = new TextButton (L"复位重来"));
    resetBt->addListener (this);

    // show path buttons
    addAndMakeVisible (leftFrontPathBt = new ToggleButton (L"左前角轨迹"));
    leftFrontPathBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    leftFrontPathBt->addListener (this);

    addAndMakeVisible (rightFrontPathBt = new ToggleButton (L"右前角轨迹"));
    rightFrontPathBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    rightFrontPathBt->addListener (this);

    addAndMakeVisible (leftRearPathBt = new ToggleButton (L"左后轮轨迹"));
    leftRearPathBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    leftRearPathBt->addListener (this);

    addAndMakeVisible (rightRearPathBt = new ToggleButton (L"右后轮轨迹"));
    rightRearPathBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    rightRearPathBt->addListener (this);

    // show pole button
    addAndMakeVisible (showPoleBt = new ToggleButton (L"转向圆圆心"));
    showPoleBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    showPoleBt->addListener (this);

    // hide car button
    addAndMakeVisible (hideCarBt = new ToggleButton (L"隐藏教练车"));
    hideCarBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    hideCarBt->addListener (this);

    // set toggle state of buttons...
    showPoleBt->setToggleState (false, dontSendNotification);
}
//=========================================================================
SetupPanel::~SetupPanel()
{
}

void SetupPanel::paint (Graphics& g)
{

}
//=========================================================================
void SetupPanel::resized()
{
    // labels
    nameLb->setBounds (0, 10, getWidth(), 30);
    versionLb->setBounds (0, 35, getWidth(), 25);

    // reset button
    resetBt->setBounds (getWidth() - 90, getHeight() - 30, 80, 25);

    // pathes buttons..
    const int leftGap = 15;

    leftFrontPathBt->setBounds (leftGap, 80, 100, 25);
    rightFrontPathBt->setBounds (leftFrontPathBt->getRight() + 5, leftFrontPathBt->getY(), 100, 25);
    leftRearPathBt->setBounds (leftGap, leftFrontPathBt->getBottom() + 5, 100, 25);
    rightRearPathBt->setBounds (leftRearPathBt->getRight() + 5, leftRearPathBt->getY(), 100, 25);

    // others..
    showPoleBt->setBounds (leftGap, leftRearPathBt->getBottom() + 5, 100, 25);
    hideCarBt->setBounds (showPoleBt->getRight() + 5, showPoleBt->getY(), 100, 25);
}

//=================================================================================================
void SetupPanel::buttonClicked (Button* bt)
{
    if (bt == resetBt)
    {
        parkinglot->reset();
        hideCarBt->setToggleState (false, sendNotification);
    }
    else if (bt == leftFrontPathBt)
    {
        parkinglot->showLeftFrontPath (leftFrontPathBt->getToggleState());
    }
    else if (bt == rightFrontPathBt)
    {
        parkinglot->showRightFrontPath (rightFrontPathBt->getToggleState());
    }
    else if (bt == leftRearPathBt)
    {
        parkinglot->showLeftRearPath (leftRearPathBt->getToggleState());
    }
    else if (bt == rightRearPathBt)
    {
        parkinglot->showRightRearPath (rightRearPathBt->getToggleState());
    }
    else if (bt == showPoleBt)
    {
        parkinglot->showPole (showPoleBt->getToggleState());
    }
    else if (bt == hideCarBt)
    {
        parkinglot->showTrainingCar (hideCarBt->getToggleState());
    }
}
