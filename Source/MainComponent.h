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
/** work area. left is parking-lot/traning field, right is setup panel. */
class MainComponent   : public Component,
                        public Button::Listener
{
public:
    MainComponent();
    ~MainComponent();

    void paint (Graphics&) override;
    void resized() override;

    virtual void buttonClicked (Button* bt) override;

private:
    OpenGLContext openGL;

    ScopedPointer<ParkingLot> parkinglot;
    ScopedPointer<SetupPanel> setupPanel;
    ScopedPointer<TextButton> showPanelBt;

    bool showPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)

};


#endif  // MAINCOMPONENT_H_INCLUDED
