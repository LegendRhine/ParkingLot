/*
  ==============================================================================

    MainComponent.h
    Created: 1 Aug 2016 11:09:32am
    Author:  mit2000

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "JuceHeader.h"

class ParkingLot;
class SetupPanel;

//==============================================================================
/*
*/
class MainComponent    : public Component
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;

private:
    ScopedPointer<ParkingLot> parkinglot;
    ScopedPointer<SetupPanel> setupPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
