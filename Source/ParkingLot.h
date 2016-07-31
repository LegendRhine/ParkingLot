/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "JuceHeader.h"

class TrainingCar;

//=========================================================================
/** This class will show the Axis-point when turning. 
*/
class PolePlacer : public Component
{
public:
    PolePlacer ()       { setSize (wh, wh); }
    ~PolePlacer()       { }

    virtual void paint (Graphics& g) override
    {
        g.setColour (Colours::lightgreen.withAlpha (0.65f));
        g.fillEllipse (0.f, 0.f, float(wh), float(wh));
    }

    bool hitTest (int, int) override            { return false; }

private:
    const int wh = 10;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolePlacer)
};

//==============================================================================
/** The parking lot which holds few resting cars, the training-car and controls it. 

    Mouse click (left/right/middle) for turning the direction.
    Mouse wheel for back/forward the training-car.
*/
class ParkingLot   : public Component
{
public:
    //==============================================================================
    ParkingLot();
    ~ParkingLot();

    void paint (Graphics&) override;
    void resized() override;

    /** -1: turn left, 0: straight, 1: turn right */
    void setDirection (const int newDirection);
    void moveTheCar (const bool backward);
    
    void reset();
    
    virtual void mouseUp (const MouseEvent& event) override;
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;

private:
    //==============================================================================
    void turnDirection (const bool shunshizhen, const bool turnLeft);
    void placeTheCar (const int oldFangxiang, const int newFangxiang);

    void getCurrentCheckPoints();

    /** Return true if the training-car crashed with something (border or resting-cars, etc.) */
    const bool isCrashed();
    
    //=========================================================================
    ScopedPointer<TrainingCar> car;
    ScopedPointer<PolePlacer> leftPlacer, rightPlacer;

	float pathHudu;

    Array<Point<int>> checkPoints;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParkingLot)
};


#endif  // MAINCOMPONENT_H_INCLUDED
