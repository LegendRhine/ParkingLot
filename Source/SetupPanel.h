/*
  ==============================================================================

    SetupPanel.h
    Created: 1 Aug 2016 11:10:22am
    Author:  mit2000

  ==============================================================================
*/

#ifndef SETUPPANEL_H_INCLUDED
#define SETUPPANEL_H_INCLUDED

#include "JuceHeader.h"

class ParkingLot;

//==============================================================================
/*
*/
class SetupPanel    : public Component,
    public Button::Listener
{
public:
    //=========================================================================
    SetupPanel (ParkingLot* const parkinglot);
    ~SetupPanel();

    void paint (Graphics&) override;
    void resized() override;

    virtual void buttonClicked (Button* bt) override;

private:
    //=========================================================================
    ParkingLot* const parkinglot;

    ScopedPointer<Label> nameLb;
    ScopedPointer<Label> versionLb;

    ScopedPointer<TextButton> erasePathBt;

    ScopedPointer<ToggleButton> leftFrontPathBt;
    ScopedPointer<ToggleButton> rightFrontPathBt;
    ScopedPointer<ToggleButton> leftRearPathBt;
    ScopedPointer<ToggleButton> rightRearPathBt;
    ScopedPointer<ToggleButton> forecastBt;

    ScopedPointer<ToggleButton> trainingBt, parkingBt, hardBt;
    ScopedPointer<ToggleButton> nonSlopeBt, slopeBt, antiSlopeBt;

    ScopedPointer<ToggleButton> showPoleBt;
    ScopedPointer<ToggleButton> hideCarBt;
        
    ScopedPointer<GroupComponent> pathGroup, typeGroup, othersGroup;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SetupPanel)
};


#endif  // SETUPPANEL_H_INCLUDED
