/*
  ==============================================================================

    SetupPanel.cpp
    Created: 1 Aug 2016 11:10:22am
    Author:  mit2000

  ==============================================================================
*/

#include "CommonData.h"
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

    addAndMakeVisible (screenShotBt = new TextButton (L"截屏"));
    screenShotBt->addListener (this);
    
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

    // show help-lines button
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

    // auto move group..
    addAndMakeVisible (autoMoveGroup = new GroupComponent (String(), L"自行"));
    autoMoveGroup->setColour (GroupComponent::outlineColourId, Colours::lightgrey.withAlpha (0.5f));
    autoMoveGroup->setColour (GroupComponent::textColourId, Colours::lightgrey);

    addAndMakeVisible (autoMoveBt = new ToggleButton (L"开启"));
    autoMoveBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    autoMoveBt->addListener (this);

    addAndMakeVisible (autoSlowBt = new ToggleButton (L"慢速"));
    autoSlowBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    autoSlowBt->addListener (this);

    addAndMakeVisible (autoNormalBt = new ToggleButton (L"中速"));
    autoNormalBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    autoNormalBt->addListener (this);

    addAndMakeVisible (autoFastBt = new ToggleButton (L"快速"));
    autoFastBt->setColour (ToggleButton::textColourId, Colours::lightgrey);
    autoFastBt->addListener (this);

    autoSlowBt->setRadioGroupId (1235);
    autoNormalBt->setRadioGroupId (1235);
    autoFastBt->setRadioGroupId (1235);

    autoSlowBt->setToggleState (true, dontSendNotification);

    autoSlowBt->setEnabled (false);
    autoNormalBt->setEnabled (false);
    autoFastBt->setEnabled (false);

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

    g.drawHorizontalLine (getHeight() - 38, 8.0f, getWidth() - 8.0f);
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

    // field group..
    typeGroup->setBounds (leftGap - 10, erasePathBt->getBottom() + 20, getWidth() - 15, 85);
    trainingBt->setBounds (leftGap, typeGroup->getY() + 20, 62, 25);
    parkingBt->setBounds (trainingBt->getRight() + 5, trainingBt->getY(), 62, 25);
    hardBt->setBounds (parkingBt->getRight() + 5, trainingBt->getY(), 62, 25);

    nonSlopeBt->setBounds (leftGap, hardBt->getBottom() + 5, 62, 25);
    slopeBt->setBounds (nonSlopeBt->getRight() + 5, nonSlopeBt->getY(), 61, 25);
    antiSlopeBt->setBounds (slopeBt->getRight() + 5, nonSlopeBt->getY(), 61, 25);

    // auto move..
    autoMoveGroup->setBounds (leftGap - 10, antiSlopeBt->getBottom() + 20, getWidth() - 15, 55);
    autoMoveBt->setBounds (leftGap, autoMoveGroup->getY() + 20, 45, 25);
    autoSlowBt->setBounds (autoMoveBt->getRight() + 5, autoMoveGroup->getY() + 20, 45, 25);
    autoNormalBt->setBounds (autoSlowBt->getRight() + 5, autoMoveGroup->getY() + 20, 45, 25);
    autoFastBt->setBounds (autoNormalBt->getRight() + 5, autoMoveGroup->getY() + 20, 45, 25);

    // others..
    othersGroup->setBounds (leftGap - 10, autoFastBt->getBottom() + 20, getWidth() - 15, 85);
    showViewLineBt->setBounds (leftGap, othersGroup->getY() + 20, 100, 25);
    hideCarBt->setBounds (showViewLineBt->getRight() + 5, showViewLineBt->getY(), 100, 25);
    cejuBt->setBounds (leftGap, hideCarBt->getBottom() + 5, 60, 25);

    // bottom buttons
    screenShotBt->setBounds (leftGap, getHeight () - 30, 45, 25);
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
        parkinglot->stopTimer();

        cejuBt->setToggleState (false, sendNotificationSync);
        nonSlopeBt->setEnabled (false);
        slopeBt->setEnabled (false);
        antiSlopeBt->setEnabled (false);
    }

    else if (bt == parkingBt && parkinglot->getFieldState() != -1)
    {
        parkinglot->setFieldState (-1);
        hideCarBt->setToggleState (false, sendNotification);
        parkinglot->stopTimer();

        cejuBt->setToggleState (false, sendNotificationSync);
        nonSlopeBt->setEnabled (true);
        slopeBt->setEnabled (true);
        antiSlopeBt->setEnabled (true);
    }

    else if (bt == hardBt && parkinglot->getFieldState() != 1)
    {
        parkinglot->setFieldState (1);
        hideCarBt->setToggleState (false, sendNotification);
        parkinglot->stopTimer();

        cejuBt->setToggleState (false, sendNotificationSync);
        nonSlopeBt->setEnabled (false);
        slopeBt->setEnabled (false);
        antiSlopeBt->setEnabled (false);
    }

    else if (bt == nonSlopeBt && parkinglot->getSlopeState() != 0)
    {
        parkinglot->setSlopedRestingCars (false, false);
        cejuBt->setToggleState (false, sendNotificationSync);
        parkinglot->stopTimer();
    }

    else if (bt == slopeBt && parkinglot->getSlopeState() != 1)
    {
        parkinglot->setSlopedRestingCars (true, false);
        cejuBt->setToggleState (false, sendNotificationSync);
        parkinglot->stopTimer();
    }


    else if (bt == antiSlopeBt && parkinglot->getSlopeState() != -1)
    {
        parkinglot->setSlopedRestingCars (true, true);
        cejuBt->setToggleState (false, sendNotificationSync);
        parkinglot->stopTimer();
    }

    else if (bt == autoMoveBt)
    {
        parkinglot->setAutoMoveMode (autoMoveBt->getToggleState());

        autoSlowBt->setEnabled (autoMoveBt->getToggleState());
        autoNormalBt->setEnabled (autoMoveBt->getToggleState());
        autoFastBt->setEnabled (autoMoveBt->getToggleState());
    }
    else if (bt == autoSlowBt)
        parkinglot->setAutoMoveSpped (SpeedWhenAutoMove * 3);
    
    else if (bt == autoNormalBt)
        parkinglot->setAutoMoveSpped (SpeedWhenAutoMove * 2);
    
    else if (bt == autoFastBt)
        parkinglot->setAutoMoveSpped (SpeedWhenAutoMove);

    else if (bt == screenShotBt)
        saveScreenShot();
        
}

//=================================================================================================
void SetupPanel::saveScreenShot()
{
    screenShot = parkinglot->getParentComponent()->createComponentSnapshot (parkinglot->getLocalBounds());

    FileChooser fc (L"保存屏幕截图", File::nonexistent, "*.png");

    if (fc.browseForFileToSave (true))
    {
        File imgFile = fc.getResult();

        if (!imgFile.hasFileExtension (".png"))
            imgFile = imgFile.withFileExtension (".png");

        if (imgFile.existsAsFile() && !imgFile.deleteFile())
        {
            AlertWindow::showMessageBox (AlertWindow::NoIcon, L"提示", L"无法写入所选文件！");
            return;
        }

        PNGImageFormat pngFormat;
        ScopedPointer<FileOutputStream> imgOutStram (imgFile.createOutputStream());

        if (pngFormat.writeImageToStream (screenShot, *imgOutStram))
        {
            imgOutStram->flush();
            imgOutStram = nullptr;
        }
        else
        {
            AlertWindow::showMessageBox (AlertWindow::NoIcon, L"提示", L"图像数据写入失败！");
        }
    }        
}

