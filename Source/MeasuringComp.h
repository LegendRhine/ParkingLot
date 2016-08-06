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
/*
*/
class MeasuringComp    : public Component
{
public:
    MeasuringComp (const Point<int> startInParent);
    ~MeasuringComp() { }

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
