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

//==============================================================================
/** The car for training. */
class TrainingCar    : public Component
{
public:
    TrainingCar ();
    ~TrainingCar() { }

    void paint (Graphics&) override;
    bool hitTest (int, int) override                { return false; }
    void reset();

    /** -1: turn left, 0: straight, 1: turn right */
    void setDirection (const int newDirection);
    const int getDirection() const                  { return direction; }

private:
	// -1: left; 0:center; 1: right. 
    // both the angle of left and right are the same: 36.87.
	int direction; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainingCar)
};


#endif  // CAR_H_INCLUDED
