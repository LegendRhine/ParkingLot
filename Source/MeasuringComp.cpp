/*
  ==============================================================================

    MeasuringComp.cpp
    Created: 6 Aug 2016 5:30:29pm
    Author:  mit2000

  ==============================================================================
*/

#include "MeasuringComp.h"

//==============================================================================
MeasuringComp::MeasuringComp (const int distanceValue,
                              const Point<int> startInParent_, 
                              const Point<int> endInParent_) :
    startInParent (startInParent_),
    endInParent (endInParent_)
{

    addAndMakeVisible (lb = new Label (String(), String (distanceValue * 2) + "cm"));

    lb->setFont (Font (16.f));
    lb->setJustificationType (Justification::centred);
    lb->setColour (Label::textColourId, Colours::whitesmoke);
    lb->setSize (54, 20);
}

//=========================================================================
void MeasuringComp::resized()
{
    lb->setCentreRelative (0.5f, 0.5f);
}

//=========================================================================
void MeasuringComp::paint (Graphics& g)
{
    /*g.setColour (Colours::lightgrey);
    g.drawRoundedRectangle (getLocalBounds().toFloat(), 0.f, 0.6f);*/

    const Point<int> startPoint (getLocalPoint (getParentComponent(), startInParent));
    const Point<int> endPoint (getLocalPoint (getParentComponent(), endInParent));

    const Line<int> markLine (startPoint, endPoint);

    g.setColour (Colours::lightblue);
    g.drawLine (markLine.toFloat(), 0.8f);

    const float banjing = 3.f;
    g.fillEllipse (startPoint.getX() - banjing, startPoint.getY() - banjing, banjing * 2.f, banjing * 2.f);
    g.fillEllipse (endPoint.getX() - banjing, endPoint.getY() - banjing, banjing * 2.f, banjing * 2.f);
}


