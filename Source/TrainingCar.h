/*
  ==============================================================================

    Car.h
    Created: 29 Jul 2016 2:58:02pm
    Author:  mit2000

  ==============================================================================
*/

#ifndef TRAININGCAR_H_INCLUDED
#define TRAININGCAR_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/** Training-car which be held and controled by the parking-lot.
*/
class TrainingCar    : public Component
{
public:
    TrainingCar ();
    ~TrainingCar() { }

    void paint (Graphics&) override;
    void reset();

    /** The argument: -1: left-turning, 0: straight, 1: right-turning */
    void setDirection (const int newDirection);

    /** Return: -1: left-turning, 0: straight, 1: right-turning */
    const int getDirection() const { return direction; }

    /** drag this object */
    virtual void mouseDrag (const MouseEvent& event) override;

    virtual void mouseUp (const MouseEvent& event) override;
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;

private:
	// -1: left; 0:center; 1: right. 
    // both left-turning and right-turning are the same angle.
	int direction; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainingCar)
};


#endif  // TRAININGCAR_H_INCLUDED
