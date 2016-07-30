/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"
#include "Car.h"
#include "CommonData.h"

//==============================================================================
MainContentComponent::MainContentComponent()
	: pathHudu (0.0f)
{
	addAndMakeVisible (car = new Car (this));
    addAndMakeVisible (leftPlacer = new PolePlacer());
    addAndMakeVisible (rightPlacer = new PolePlacer());

    setSize (1200, 800);
}

MainContentComponent::~MainContentComponent()
{
}
//=========================================================================
void MainContentComponent::paint (Graphics& g)
{
    g.fillAll (Colours::darkgrey);

	/*g.setColour (Colours::darkred);
	g.fillRect (car->getBounds ().expanded (8));

	g.setColour (Colours::darkgoldenrod);
	g.fillRect (car->getBoundsInParent ().expanded (5));*/	
}
//=========================================================================
void MainContentComponent::resized ()
{
    pathHudu = 0.0f;

    car->setTransform (AffineTransform());
	car->setCentreRelative (0.5f, 0.5f);
    car->reset();

    leftPlacer->setTransform (AffineTransform());
    leftPlacer->setCentrePosition (car->getX() - FromInnerWheel, car->getY() + 190);

    rightPlacer->setTransform (AffineTransform());
    rightPlacer->setCentrePosition (car->getRight() + FromInnerWheel, car->getY() + 190);
}

//=================================================================================================
void MainContentComponent::moveTheCar (const bool shunshizhen, const bool turnLeft)
{
    //todo...

	pathHudu += shunshizhen ? EachHudu : -EachHudu;

    const int x = turnLeft ? (car->getX() - FromInnerWheel)
                           : (car->getRight() + FromInnerWheel);
    const int y = car->getY() + 190;

    AffineTransform aft (AffineTransform::rotation (pathHudu, float(x), float(y)));
	car->setTransform (aft);
    rightPlacer->setTransform (aft);
    leftPlacer->setTransform (aft);
}

//=================================================================================================
void MainContentComponent::placeTheCar (const int oldFangxiang, const int newFangxiang)
{
    if (newFangxiang == 0 || oldFangxiang == newFangxiang)  
        return;

    int centerX = 0;
    int centerY = 0;
    AffineTransform aft;

    // First, place the car base on the matches placer, then transform the car. 
    // the pole base on the placer.
    // second, place two placer base on the car, then transform them.

    if (newFangxiang == -1)
    {
        centerX = leftPlacer->getBoundsInParent().getCentreX() + FromInnerWheel + 50;
        centerY = leftPlacer->getBoundsInParent().getCentreY() - 70;        
        aft = AffineTransform::rotation (pathHudu, 
            centerX - FromInnerWheel - 50.0000001f, centerY + 70.0000001f);
    }
    else
    {
        centerX = rightPlacer->getBoundsInParent().getCentreX() - FromInnerWheel - 50;
        centerY = rightPlacer->getBoundsInParent().getCentreY() - 70;        
        aft = AffineTransform::rotation (pathHudu, 
            centerX + FromInnerWheel + 50.0000001f, centerY + 70.0000001f);
    }    

    car->setCentrePosition (centerX, centerY);
    leftPlacer->setCentrePosition (car->getX() - FromInnerWheel, car->getY() + 190);
    rightPlacer->setCentrePosition (car->getRight() + FromInnerWheel, car->getY() + 190);

    car->setTransform (aft);
    leftPlacer->setTransform (aft);
    rightPlacer->setTransform (aft);
}

