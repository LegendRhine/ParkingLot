/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "JuceHeader.h"

class Car;

//=========================================================================
class PolePlacer : public Component
{
public:
    PolePlacer ()       { setSize (wh, wh); }
    ~PolePlacer()       { }

    virtual void paint (Graphics& g) override
    {
        g.setColour (Colours::red.withAlpha (0.65f));
        g.fillEllipse (0.f, 0.f, float(wh), float(wh));
    }

    bool hitTest (int, int) override            { return false; }

private:
    const int wh = 20;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolePlacer)
};

//==============================================================================
/** The parking lot. holds the car and control it.    
*/
class MainContentComponent   : public Component
{
public:
    //==============================================================================
    MainContentComponent();
    ~MainContentComponent();

    void paint (Graphics&) override;
    void resized() override;

    /** -1: turn left, 0: straight, 1: turn right */
    void setDirection (const int newDirection);
    void moveTheCar (const bool backward);

    void reset()                                    { resized(); }
    
    virtual void mouseUp (const MouseEvent& event) override;
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;

private:
    //==============================================================================
    void turnDirection (const bool shunshizhen, const bool turnLeft);
    void placeTheCar (const int oldFangxiang, const int newFangxiang);
    PolePlacer* getPlacer (const bool isLeft) { return isLeft ? leftPlacer : rightPlacer; }

    ScopedPointer<Car> car;
    ScopedPointer<PolePlacer> leftPlacer, rightPlacer;

	float pathHudu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
