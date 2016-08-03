/*
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
    addAndMakeVisible (resetBt = new TextButton (L"复位"));
    resetBt->addListener (this);

    addAndMakeVisible (clearBt = new TextButton (L"清场"));
    clearBt->addListener (this);

    addAndMakeVisible (autoMoveBt = new TextButton (L"自行"));
    autoMoveBt->setColour (TextButton::textColourOnId, Colours::lightgrey);
    autoMoveBt->addListener (this);

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

    // show pole button
    addAndMakeVisible (showPoleBt = new ToggleButton (L"转向圆圆心"));
    showPoleBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    showPoleBt->addListener (this);

    // hide car button
    addAndMakeVisible (hideCarBt = new ToggleButton (L"车体半透明"));
    hideCarBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    hideCarBt->addListener (this);

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

    // speed bts
    addAndMakeVisible (slowSpeedBt = new ToggleButton (L"慢速"));
    slowSpeedBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    slowSpeedBt->addListener (this);
    slowSpeedBt->setEnabled (false);

    addAndMakeVisible (normalSpeedBt = new ToggleButton (L"中速"));
    normalSpeedBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    normalSpeedBt->addListener (this);
    normalSpeedBt->setEnabled (false);

    addAndMakeVisible (fastSpeedBt = new ToggleButton (L"快速"));
    fastSpeedBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    fastSpeedBt->addListener (this);
    fastSpeedBt->setEnabled (false);

    slowSpeedBt->setRadioGroupId (1235);
    normalSpeedBt->setRadioGroupId (1235);
    fastSpeedBt->setRadioGroupId (1235);

    slowSpeedBt->setToggleState (true, dontSendNotification);

    // group component..
    addAndMakeVisible (pathGroup = new GroupComponent (String(), L"轨迹显示"));
    pathGroup->setColour (GroupComponent::outlineColourId, Colours::lightgrey.withAlpha (0.5f));
    pathGroup->setColour (GroupComponent::textColourId, Colours::lightgrey);

    addAndMakeVisible (typeGroup = new GroupComponent (String(), L"车位类型"));
    typeGroup->setColour (GroupComponent::outlineColourId, Colours::lightgrey.withAlpha (0.5f));
    typeGroup->setColour (GroupComponent::textColourId, Colours::lightgrey);

    addAndMakeVisible (speedGroup = new GroupComponent (String(), L"自动车速"));
    speedGroup->setColour (GroupComponent::outlineColourId, Colours::lightgrey.withAlpha (0.5f));
    speedGroup->setColour (GroupComponent::textColourId, Colours::lightgrey);
    speedGroup->setEnabled (false);

    addAndMakeVisible (othersGroup = new GroupComponent (String(), L"其他选项"));
    othersGroup->setColour (GroupComponent::outlineColourId, Colours::lightgrey.withAlpha (0.5f));
    othersGroup->setColour (GroupComponent::textColourId, Colours::lightgrey);

}
//=========================================================================
SetupPanel::~SetupPanel()
{
}

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

    // buttons
    autoMoveBt->setBounds (10, getHeight() - 30, 50, 25);
    resetBt->setBounds (getWidth() - 60, getHeight() - 30, 50, 25);
    clearBt->setBounds (resetBt->getX() - 60, getHeight() - 30, 50, 25);

    // pathes..
    const int leftGap = 20;

    pathGroup->setBounds (leftGap - 10, 70, getWidth() - 15, 90);

    leftFrontPathBt->setBounds (leftGap, pathGroup->getY() + 20, 100, 25);
    rightFrontPathBt->setBounds (leftFrontPathBt->getRight() + 5, leftFrontPathBt->getY(), 100, 25);
    leftRearPathBt->setBounds (leftGap, leftFrontPathBt->getBottom() + 5, 100, 25);
    rightRearPathBt->setBounds (leftRearPathBt->getRight() + 5, leftRearPathBt->getY(), 100, 25);

    // slope..
    typeGroup->setBounds (leftGap - 10, 170, getWidth() - 15, 60);

    nonSlopeBt->setBounds (leftGap, typeGroup->getY() + 20, 62, 25);
    slopeBt->setBounds (nonSlopeBt->getRight() + 5, nonSlopeBt->getY(), 61, 25);
    antiSlopeBt->setBounds (slopeBt->getRight() + 5, nonSlopeBt->getY(), 61, 25);

    // speed
    speedGroup->setBounds (leftGap - 10, 240, getWidth() - 15, 60);

    slowSpeedBt->setBounds (leftGap, speedGroup->getY() + 20, 62, 25);
    normalSpeedBt->setBounds (slowSpeedBt->getRight() + 5, slowSpeedBt->getY(), 61, 25);
    fastSpeedBt->setBounds (normalSpeedBt->getRight() + 5, slowSpeedBt->getY(), 61, 25);

    // others..
    othersGroup->setBounds (leftGap - 10, 310, getWidth() - 15, 60);

    showPoleBt->setBounds (leftGap, othersGroup->getY() + 20, 100, 25);
    hideCarBt->setBounds (showPoleBt->getRight() + 5, showPoleBt->getY(), 100, 25);

}

//=================================================================================================
void SetupPanel::buttonClicked (Button* bt)
{
    if (bt == autoMoveBt)
    {
        const bool autoMove = autoMoveBt->getToggleState();
        autoMoveBt->setToggleState (!autoMove, dontSendNotification);

        parkinglot->setAutoMove (!autoMove);
        speedGroup->setEnabled (!autoMove);
        slowSpeedBt->setEnabled (!autoMove);
        normalSpeedBt->setEnabled (!autoMove);
        fastSpeedBt->setEnabled (!autoMove);
    }
    else if (bt == resetBt)
    {
        parkinglot->reset();
        hideCarBt->setToggleState (false, sendNotification);
        autoMoveBt->setToggleState (false, dontSendNotification);
        clearBt->setEnabled (true);

        typeGroup->setEnabled (true);
        nonSlopeBt->setEnabled (true);
        slopeBt->setEnabled (true);
        antiSlopeBt->setEnabled (true);
    }

    else if (bt == clearBt && clearBt->isEnabled())
    {
        clearBt->setEnabled (false);
        parkinglot->clearRestingCars();

        typeGroup->setEnabled (false);
        nonSlopeBt->setEnabled (false);
        slopeBt->setEnabled (false);
        antiSlopeBt->setEnabled (false);
    }

    else if (bt == leftFrontPathBt)
        parkinglot->showLeftFrontPath (leftFrontPathBt->getToggleState());

    else if (bt == rightFrontPathBt)
        parkinglot->showRightFrontPath (rightFrontPathBt->getToggleState());

    else if (bt == leftRearPathBt)
        parkinglot->showLeftRearPath (leftRearPathBt->getToggleState());

    else if (bt == rightRearPathBt)
        parkinglot->showRightRearPath (rightRearPathBt->getToggleState());

    else if (bt == showPoleBt)
        parkinglot->showPole (showPoleBt->getToggleState());

    else if (bt == hideCarBt)
        parkinglot->showTrainingCar (hideCarBt->getToggleState());

    else if (bt == nonSlopeBt)
        parkinglot->setSlopedRestingCars (false, false);

    else if (bt == slopeBt)
        parkinglot->setSlopedRestingCars (true, false);

    else if (bt == antiSlopeBt)
        parkinglot->setSlopedRestingCars (true, true);

    else if (bt == slowSpeedBt)
        parkinglot->setSpeed (3);

    else if (bt == normalSpeedBt)
        parkinglot->setSpeed (2);

    else if (bt == fastSpeedBt)
        parkinglot->setSpeed (1);
}
