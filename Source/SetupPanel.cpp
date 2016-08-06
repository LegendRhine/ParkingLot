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

    // buttons
    addAndMakeVisible (erasePathBt = new TextButton (L"清除已有轨迹"));
    erasePathBt->addListener (this);
    
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
    leftRearPathBt->setToggleState (true, dontSendNotification);

    addAndMakeVisible (rightRearPathBt = new ToggleButton (L"右后轮轨迹"));
    rightRearPathBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    rightRearPathBt->addListener (this);
    rightRearPathBt->setToggleState (true, dontSendNotification);

    addAndMakeVisible (forecastBt = new ToggleButton (L"转弯辅助轨迹"));
    forecastBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    forecastBt->addListener (this);
    forecastBt->setToggleState (false, dontSendNotification);

    // show pole button
    addAndMakeVisible (showViewLineBt = new ToggleButton (L"辅助观察线"));
    showViewLineBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    showViewLineBt->addListener (this);

    // hide car button
    addAndMakeVisible (hideCarBt = new ToggleButton (L"车体半透明"));
    hideCarBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    hideCarBt->addListener (this);

    // filed bts
    addAndMakeVisible (trainingBt = new ToggleButton (L"训练场"));
    trainingBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    trainingBt->addListener (this);

    addAndMakeVisible (parkingBt = new ToggleButton (L"停车场"));
    parkingBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    parkingBt->addListener (this);

    addAndMakeVisible (hardBt = new ToggleButton (L"障碍赛"));
    hardBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    hardBt->addListener (this);

    trainingBt->setRadioGroupId (1233);
    parkingBt->setRadioGroupId (1233);
    hardBt->setRadioGroupId (1233);

    parkingBt->setToggleState (true, dontSendNotification);

    // slope bts
    addAndMakeVisible (nonSlopeBt = new ToggleButton (L"非字型"));
    nonSlopeBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    nonSlopeBt->addListener (this);

    addAndMakeVisible (slopeBt = new ToggleButton (L"斜非型"));
    slopeBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    slopeBt->addListener (this);

    addAndMakeVisible (antiSlopeBt = new ToggleButton (L"反斜非"));
    antiSlopeBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    antiSlopeBt->addListener (this);

    nonSlopeBt->setRadioGroupId (1234);
    slopeBt->setRadioGroupId (1234);
    antiSlopeBt->setRadioGroupId (1234);

    nonSlopeBt->setToggleState (true, dontSendNotification);

    // group component..
    addAndMakeVisible (pathGroup = new GroupComponent (String(), L"轨迹"));
    pathGroup->setColour (GroupComponent::outlineColourId, Colours::lightgrey.withAlpha (0.5f));
    pathGroup->setColour (GroupComponent::textColourId, Colours::lightgrey);

    addAndMakeVisible (typeGroup = new GroupComponent (String(), L"场地"));
    typeGroup->setColour (GroupComponent::outlineColourId, Colours::lightgrey.withAlpha (0.5f));
    typeGroup->setColour (GroupComponent::textColourId, Colours::lightgrey);

    addAndMakeVisible (othersGroup = new GroupComponent (String(), L"其它"));
    othersGroup->setColour (GroupComponent::outlineColourId, Colours::lightgrey.withAlpha (0.5f));
    othersGroup->setColour (GroupComponent::textColourId, Colours::lightgrey);

    // ceju
    addAndMakeVisible (cejuBt = new ToggleButton (L"测距"));
    cejuBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    cejuBt->addListener (this);

    // cancel all widgets's focus for shortcut of ParkingLot (turning and moving car)
    for (int i = getNumChildComponents(); --i >= 0; )
        getChildComponent (i)->setWantsKeyboardFocus (false);
}
//=========================================================================
SetupPanel::~SetupPanel()
{
}
//=========================================================================
void SetupPanel::paint (Graphics& g)
{
    g.setColour (Colours::lightgrey);

    g.drawHorizontalLine (getHeight() - 40, 10.0f, getWidth() - 10.0f);
}
//=========================================================================
void SetupPanel::resized()
{
    // labels
    nameLb->setBounds (0, 10, getWidth(), 30);
    versionLb->setBounds (0, 35, getWidth(), 25);

    // pathes..
    const int leftGap = 20;

    pathGroup->setBounds (leftGap - 10, 70, getWidth() - 15, 115);

    leftFrontPathBt->setBounds (leftGap, pathGroup->getY() + 20, 100, 25);
    rightFrontPathBt->setBounds (leftFrontPathBt->getRight() + 5, leftFrontPathBt->getY(), 100, 25);
    leftRearPathBt->setBounds (leftGap, leftFrontPathBt->getBottom() + 5, 100, 25);
    rightRearPathBt->setBounds (leftRearPathBt->getRight() + 5, leftRearPathBt->getY(), 100, 25);
    erasePathBt->setBounds (getWidth() - 105, rightRearPathBt->getBottom() + 5, 90, 25);
    forecastBt->setBounds (leftGap, rightRearPathBt->getBottom() + 5, 100, 25);

    // slope..
    typeGroup->setBounds (leftGap - 10, erasePathBt->getBottom() + 20, getWidth() - 15, 90);

    trainingBt->setBounds (leftGap, typeGroup->getY() + 20, 62, 25);
    parkingBt->setBounds (trainingBt->getRight() + 5, trainingBt->getY(), 62, 25);
    hardBt->setBounds (parkingBt->getRight() + 5, trainingBt->getY(), 62, 25);

    nonSlopeBt->setBounds (leftGap, hardBt->getBottom() + 5, 62, 25);
    slopeBt->setBounds (nonSlopeBt->getRight() + 5, nonSlopeBt->getY(), 61, 25);
    antiSlopeBt->setBounds (slopeBt->getRight() + 5, nonSlopeBt->getY(), 61, 25);

    // others..
    othersGroup->setBounds (leftGap - 10, antiSlopeBt->getBottom() + 25, getWidth() - 15, 90);

    showViewLineBt->setBounds (leftGap, othersGroup->getY() + 20, 100, 25);
    hideCarBt->setBounds (showViewLineBt->getRight() + 5, showViewLineBt->getY(), 100, 25);
    cejuBt->setBounds (leftGap, hideCarBt->getBottom() + 5, 60, 25);
}

//=================================================================================================
void SetupPanel::buttonClicked (Button* bt)
{
    if (bt == leftFrontPathBt)
        parkinglot->showLeftFrontPath (leftFrontPathBt->getToggleState());

    else if (bt == rightFrontPathBt)
        parkinglot->showRightFrontPath (rightFrontPathBt->getToggleState());

    else if (bt == leftRearPathBt)
        parkinglot->showLeftRearPath (leftRearPathBt->getToggleState());

    else if (bt == rightRearPathBt)
        parkinglot->showRightRearPath (rightRearPathBt->getToggleState());

    else if (bt == erasePathBt)
        parkinglot->resetPath();

    else if (bt == forecastBt)
        parkinglot->showForecastPath (forecastBt->getToggleState());

    else if (bt == showViewLineBt)
        parkinglot->showViewLine (showViewLineBt->getToggleState());

    else if (bt == cejuBt)
        parkinglot->measureDistance (cejuBt->getToggleState());

    else if (bt == hideCarBt)
        parkinglot->transparentTrainingCar (hideCarBt->getToggleState());

    else if (bt == trainingBt && parkinglot->getFieldState() != 0)
    {
        parkinglot->setFieldState (0);
        hideCarBt->setToggleState (false, sendNotification);

        cejuBt->setToggleState (false, sendNotificationSync);
        nonSlopeBt->setEnabled (false);
        slopeBt->setEnabled (false);
        antiSlopeBt->setEnabled (false);
    }

    else if (bt == parkingBt && parkinglot->getFieldState() != -1)
    {
        parkinglot->setFieldState (-1);
        hideCarBt->setToggleState (false, sendNotification);

        cejuBt->setToggleState (false, sendNotificationSync);
        nonSlopeBt->setEnabled (true);
        slopeBt->setEnabled (true);
        antiSlopeBt->setEnabled (true);
    }

    else if (bt == hardBt && parkinglot->getFieldState() != 1)
    {
        parkinglot->setFieldState (1);
        hideCarBt->setToggleState (false, sendNotification);

        cejuBt->setToggleState (false, sendNotificationSync);
        nonSlopeBt->setEnabled (false);
        slopeBt->setEnabled (false);
        antiSlopeBt->setEnabled (false);
    }

    else if (bt == nonSlopeBt && parkinglot->getSlopeState() != 0)
        parkinglot->setSlopedRestingCars (false, false);

    else if (bt == slopeBt && parkinglot->getSlopeState() != 1)
        parkinglot->setSlopedRestingCars (true, false);

    else if (bt == antiSlopeBt && parkinglot->getSlopeState() != -1)
        parkinglot->setSlopedRestingCars (true, true);
        
}
