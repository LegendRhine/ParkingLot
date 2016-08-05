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

    /** return: -X: left direction; 0:center; x: right direction.  */
    const int getTurningAngle() const                   { return turningAngle; }
    void setTurningAngle (const int newAngle, const bool shouldTellParentRepaint);

    const float getDistanceFromInnerWheel()             { return fromInnerWheel; }
    const float getCurrentEachHudu() const { return eachHudu; }

    /** turn left or right.  */
    virtual void mouseUp (const MouseEvent& event) override;

    /** tell parent component to move the car forward or back */
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;

    /** drag this object for manual place it */
    virtual void mouseDrag (const MouseEvent& event) override;

    /** turn the most left or right */
    virtual void mouseDoubleClick (const MouseEvent& e) override;
    
    /** direction = 0, repaint front wheels etc.. */
    void reset();

    void paint (Graphics&) override;
    
private:
    //=========================================================================
    void afterSetAngle (const bool shouldRepaintParent);

    ParkingLot* parkingLot;
    float fromInnerWheel;
    float eachHudu;
    int turningAngle;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrainingCar)
};


#endif  // TRAININGCAR_H_INCLUDED
