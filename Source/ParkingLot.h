/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef PARKINGLOT_H_INCLUDED
#define PARKINGLOT_H_INCLUDED

#include "JuceHeader.h"

class TrainingCar;
class RestingCar;

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
    const bool moveTheCar (const bool backward);
    const bool dontShowRestingCars() const              { return clearAllRestingCars; }

    void showLeftFrontPath (const bool showIt);
    void showRightFrontPath (const bool showIt);
    void showLeftRearPath (const bool showIt);
    void showRightRearPath (const bool showIt);

    void showPole (const bool showIt);
    void showTrainingCar (const bool showIt);
    void setSlopedRestingCars (const bool slope, const bool backslash);
    void clearRestingCars();

    void reset();
        
    virtual void mouseUp (const MouseEvent& event) override;
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;

private:
    //==============================================================================
    void arrangeRestingCars (const bool slope, const bool backslash);
    void turnDirection (const bool shunshizhen, const bool turnLeft);
    void placeTheCar (const int oldFangxiang, const int newFangxiang);

    void resetPath ();
    void getCurrentCheckPoints();    
    const bool isCrashed();
    const bool isSuccessful();

    //=========================================================================
    /** This class will show the Axis-point when turning. */
    class PolePlacer : public Component
    {
    public:
        PolePlacer () { setSize (wh, wh); }
        ~PolePlacer() { }

        virtual void paint (Graphics& g) override
        {
            g.setColour (Colours::lightgreen.withAlpha (0.65f));
            g.fillEllipse (0.f, 0.f, float(wh), float(wh));
        }

        bool hitTest (int, int) override { return false; }

    private:
        const int wh = 2;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PolePlacer)
    };
    //=========================================================================
    ScopedPointer<PolePlacer> leftPlacer, rightPlacer;
    OwnedArray<Component> restingCars;
    ScopedPointer<TrainingCar> trainingCar;

    /** This class repersent stop-area */
    class StopArea : public Component
    {
    public:
        StopArea() { }

        virtual void paint (Graphics& g) override
        {
            g.setColour (Colours::lightgrey.withAlpha (0.5f));
            //g.fillRoundedRectangle (getLocalBounds().toFloat(), 5.0f);
            g.drawRoundedRectangle (getLocalBounds().toFloat(), 5.0f, 0.6f);

            for (int i = -60; i <= getBottom() + 60; i += 20)
            {
                Line<int> lineOne (-80, i, getWidth() + 80, i);
                lineOne.applyTransform (AffineTransform::rotation (
                    45.0f / 180.0f * float_Pi, getWidth() / 2.0f, getHeight() / 2.0f));

                g.drawLine (lineOne.toFloat(), 0.6f);

                Line<int> lineTwo (-80, i, getWidth() + 80, i);
                lineTwo.applyTransform (AffineTransform::rotation (
                    -45.0f / 180.0f * float_Pi, getWidth() / 2.0f, getHeight() / 2.0f));

                g.drawLine (lineTwo.toFloat(), 0.6f);
            }
        }

        void mouseUp (const MouseEvent& e) override
        {
            getParentComponent()->mouseUp (e);
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StopArea)
    };
    //=========================================================================
    ScopedPointer<StopArea> stopAreaOne, stopAreaTwo, stopAreaThree;
    
    Array<Point<int>> checkPoints;
    Path leftFrontPath, rightFrontPath, leftRearPath, rightRearPath;
    float pathHudu;

    bool leftFrontPathShow, rightFrontPathShow, leftRearPathShow, rightRearPathShow;
    bool shouldShowPole;
    bool xiexiang, fanxiexiang;
    bool clearAllRestingCars;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParkingLot)
};


#endif  // PARKINGLOT_H_INCLUDED
