/*
  ==============================================================================

    RestingCar.h
    Created: 31 Jul 2016 8:19:56pm
    Author:  mit2000

  ==============================================================================
*/

#ifndef RESTINGCAR_H_INCLUDED
#define RESTINGCAR_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================

class RestingCar    : public Component
{
public:
    RestingCar();
    ~RestingCar();

    void paint (Graphics&) override;
    void resized() override;
    
    virtual void mouseUp (const MouseEvent& event) override;

private:
    const Colour cl;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RestingCar)
};


#endif  // RESTINGCAR_H_INCLUDED
