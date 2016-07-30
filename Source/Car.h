/*
  ==============================================================================

    Car.h
    Created: 29 Jul 2016 2:58:02pm
    Author:  mit2000

  ==============================================================================
*/

#ifndef CAR_H_INCLUDED
#define CAR_H_INCLUDED

#include "JuceHeader.h"

class MainContentComponent;

//==============================================================================
/*
*/
class Car    : public Component
{
public:
    Car (MainContentComponent* mainComp);
    ~Car() { }

    void paint (Graphics&) override;

	void move (const bool backward);
    void reset();

	virtual void mouseUp (const MouseEvent& event) override;
	virtual void mouseWheelMove (const MouseEvent& , const MouseWheelDetails& ) override;

private:
	MainContentComponent* mainComp;

	// -1: left; 0:center; 1: right. both the angle of left and right are the same: 36.87.
	int fangxiang; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Car)
};


#endif  // CAR_H_INCLUDED
