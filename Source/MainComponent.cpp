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
	addAndMakeVisible (car = new Car());
    addChildComponent (leftPlacer = new PolePlacer());
    addChildComponent (rightPlacer = new PolePlacer());

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
void MainContentComponent::setDirection (const int newDirection)
{
    const int oldFangxiang = car->getDirection();

    car->setDirection (newDirection);
    placeTheCar (oldFangxiang, newDirection);

    if (newDirection == 0)
    {
        leftPlacer->setVisible (false);
        rightPlacer->setVisible (false);
    }
    else if (newDirection == -1)
    {
        leftPlacer->setVisible (true);
        rightPlacer->setVisible (false);

        leftPlacer->toFront(false);
    }
    else if (newDirection == 1)
    {
        leftPlacer->setVisible (false);
        rightPlacer->setVisible (true);

        rightPlacer->toFront(false);
    }
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

//=================================================================================================
void MainContentComponent::mouseUp (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown())
        setDirection (-1);
    else if (e.mods.isRightButtonDown())
        setDirection (1);
    else if (e.mods.isMiddleButtonDown())
        setDirection (0);
}

//=================================================================================================
void MainContentComponent::mouseWheelMove (const MouseEvent&, const MouseWheelDetails& wheel)
{
    moveTheCar (wheel.deltaY > 0);
}

//=================================================================================================
void MainContentComponent::moveTheCar (const bool backward)
{
    if (0 == car->getDirection())  // straight forward
    {
        const int dist (backward ? StraightStep : -StraightStep);
        car->setTopLeftPosition (car->getX(), car->getY() + dist);

        Component* leftPole (getPlacer (true));
        Component* rightPole (getPlacer (false));

        leftPole->setTopLeftPosition (leftPole->getX(), leftPole->getY() + dist);
        rightPole->setTopLeftPosition (rightPole->getX(), rightPole->getY() + dist);
    }
    else if (-1 == car->getDirection()) // -1 is turn left
    {
        turnDirection (backward, true);
    }
    else  if (1 == car->getDirection()) // 1 is turn right
    {
        turnDirection (!backward, false);
    }
}

//=================================================================================================
void MainContentComponent::turnDirection (const bool shunshizhen, const bool turnLeft)
{
    pathHudu += shunshizhen ? EachHudu : -EachHudu;

    const int x = turnLeft ? (car->getX() - FromInnerWheel) : (car->getRight() + FromInnerWheel);
    const int y = car->getY() + 190;

    AffineTransform aft (AffineTransform::rotation (pathHudu, float(x), float(y)));
    car->setTransform (aft);
    rightPlacer->setTransform (aft);
    leftPlacer->setTransform (aft);
}

