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
        g.setColour (Colours::whitesmoke);
        //g.fillEllipse (0.f, 0.f, float(wh), float(wh));
    }

private:
    const int wh = 1;

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

	void moveTheCar (const bool shunshizhen, const bool turnLeft);
	void placeTheCar (const int oldFangxiang, const int newFangxiang);
    void reset()        { resized(); }

    PolePlacer* getPlacer (const bool isLeft)   { return isLeft ? leftPlacer : rightPlacer; }

private:
    //==============================================================================
	ScopedPointer<Car> car;
    ScopedPointer<PolePlacer> leftPlacer, rightPlacer;

	float pathHudu;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
