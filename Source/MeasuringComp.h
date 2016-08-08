/*
  ==============================================================================

    MeasuringComp.h
    Created: 6 Aug 2016 5:30:29pm
    Author:  mit2000

  ==============================================================================
*/

#ifndef MEASURINGCOMP_H_INCLUDED
#define MEASURINGCOMP_H_INCLUDED

#include "JuceHeader.h"

//==============================================================================
/** This class represent the measure-mark 

    (a label and a line which has a start-point and a end-point). 
    The object could be created by its parent's mouseDown(), then add it to an ownedArray, 
    and its size and content could be set by parent-component's mouseDrag() and mouseUp().
*/
class MeasuringComp    : public Component
{
public:
    MeasuringComp (const Point<int> startInParent);
    ~MeasuringComp() { }

    /** Update the label's text in real-time */
    void setEndPoint (const Point<int> endInParent);

    void paint (Graphics&) override;
    void resized() override;

    virtual bool hitTest (int, int) override            { return false; }

private:
    ScopedPointer<Label> lb;
    Point<int> startInParent, endInParent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MeasuringComp)
};


#endif  // MEASURINGCOMP_H_INCLUDED
