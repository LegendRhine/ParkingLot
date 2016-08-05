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

class ParkingLot;

//==============================================================================
/** Training-car which be held and controled by the parking-lot.
*/
class TrainingCar    : public Component
{
public:
    TrainingCar (ParkingLot* park);
    ~TrainingCar() { }

    /** return: -X: left direction; 0:center; x: right direction. Value range: -32 ~ 32 */
    const int getTurningAngle() const                   { return turningAngle; }
    void setTurningAngle (const int newAngle);

    const float getDistanceFromInnerWheel()             { return fromInnerWheel; }

    /** turn left or right. each click = (+-8) degree */
    virtual void mouseUp (const MouseEvent& event) override;

    /** tell parent component to move the car forward or back */
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;

    /** drag this object for manual place it */
    virtual void mouseDrag (const MouseEvent& event) override;

    /** direction = 0, repaint front wheels etc.. */
    void reset();

    void paint (Graphics&) override;

private:
    ParkingLot* parkingLot;
    float fromInnerWheel;
    int turningAngle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainingCar)
};


#endif  // TRAININGCAR_H_INCLUDED
