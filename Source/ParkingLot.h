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
class ParkingLot   : public Component,
    public DragAndDropContainer,
    public DragAndDropTarget
{
public:
    //==============================================================================
    ParkingLot();
    ~ParkingLot();

    void paint (Graphics&) override;
    void resized() override;

    void placeAfterSetDirection (const int newAngle);
    const bool moveTheCar (const bool backward);
    const bool dontShowRestingCars() const              { return clearAllRestingCars; }

    void showLeftFrontPath (const bool showIt);
    void showRightFrontPath (const bool showIt);
    void showLeftRearPath (const bool showIt);
    void showRightRearPath (const bool showIt);
    void showForecastPath (const bool showIt);
    void showViewLine (const bool showIt);

    void transparentTrainingCar (const bool transparentIt);
    void setSlopedRestingCars (const bool slope, const bool backslash);

    /** return 0-non slope, 1-slope, -1-anti slope */
    const int getSlopeState() const                 { return arrangeState;  }  

    /** return 0-training field, -1-parking field, 1-block (hard) field */
    const int getFieldState() const;
    void setFieldState (const int stateCode);

    void resetPath ();
        
    virtual void mouseDown (const MouseEvent& e) override;
    virtual void mouseUp (const MouseEvent& event) override;
    virtual void mouseDrag (const MouseEvent& event) override;
    virtual void mouseWheelMove (const MouseEvent&, const MouseWheelDetails&) override;

    virtual bool isInterestedInDragSource (const SourceDetails& dragSourceDetails) override;
    virtual void itemDropped (const SourceDetails& dragSourceDetails) override;


    virtual bool keyPressed (const KeyPress& key) override;

private:
    //==============================================================================
    void arrangeRestingCars (const bool slope, const bool backslash);
    void placeTheCarAfterDraged (const int newX, const int newY);

    void getCurrentCheckPoints();    
    const bool isCrashed();
    const bool isSuccessful();

     //=========================================================================
    Point<float> polePoint;
    OwnedArray<Component> restingCars;
    ScopedPointer<TrainingCar> trainingCar;

    /** This class repersent stop-area */
    class StopArea : public Component
    {
    public:
        StopArea() { }

        virtual void paint (Graphics& g) override
        {
            g.setColour (Colours::lightgrey.withAlpha (0.4f));

            g.drawRoundedRectangle (getLocalBounds().toFloat(), 5.0f, 0.6f);
            g.fillCheckerBoard (getLocalBounds(), 28, 27, Colour (0x00), Colours::lightgrey.withAlpha (0.15f));
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
    Path forecastPath1, forecastPath2;
    float pathHudu;
    int arrangeState;

    bool leftFrontPathShow, rightFrontPathShow, leftRearPathShow, rightRearPathShow;
    bool shouldShowForecastPath, shouldShowViewLine;
    bool xiexiang, fanxiexiang;
    bool clearAllRestingCars;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParkingLot)
};


#endif  // PARKINGLOT_H_INCLUDED
