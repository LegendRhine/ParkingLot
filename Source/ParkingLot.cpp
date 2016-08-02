/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "CommonData.h"
#include "ParkingLot.h"
#include "TrainingCar.h"
#include "RestingCar.h"

const float alphaOfThings = 1.0f;

//==============================================================================
ParkingLot::ParkingLot()
	: pathHudu (0.0f),
    leftFrontPathShow (false),
    rightFrontPathShow (false),
    leftRearPathShow (false),
    rightRearPathShow (false),
    shouldShowPole (false)
{
	addAndMakeVisible (trainingCar = new TrainingCar());
    addChildComponent (leftPlacer = new PolePlacer());
    addChildComponent (rightPlacer = new PolePlacer());

    trainingCar->setAlpha (alphaOfThings);
    leftPlacer->setAlpha (alphaOfThings);
    rightPlacer->setAlpha (alphaOfThings);
}

ParkingLot::~ParkingLot()
{
}
//=========================================================================
void ParkingLot::paint (Graphics& g)
{
    // draw pathes...
    if (leftFrontPathShow)
    {
        g.setColour (Colours::lightgreen);
        g.strokePath (leftFrontPath, PathStrokeType (0.5f));
    }

    if (rightFrontPathShow)
    {
        g.setColour (Colours::lightgreen);
        g.strokePath (rightFrontPath, PathStrokeType (0.5f));
    }

    if (leftRearPathShow)
    {
        g.setColour (Colours::lightpink);
        g.strokePath (leftRearPath, PathStrokeType (0.5f));
    }

    if (rightRearPathShow)
    {
        g.setColour (Colours::lightpink);
        g.strokePath (rightRearPath, PathStrokeType (0.5f));
    }

	/*g.setColour (Colours::darkred);
	g.fillRect (car->getBounds ().expanded (8));

	g.setColour (Colours::darkgoldenrod);
	g.fillRect (car->getBoundsInParent ().expanded (5));	*/
}
//=========================================================================
void ParkingLot::resized ()
{
    pathHudu = 0.0f;

    trainingCar->setTransform (AffineTransform ());
	trainingCar->setCentrePosition(CarLength + 120, getHeight() - 200);
    trainingCar->reset();

    leftPlacer->setTransform (AffineTransform());
    leftPlacer->setCentrePosition (trainingCar->getX() - FromInnerWheel, trainingCar->getY() + 190);
    leftPlacer->setVisible (false);

    rightPlacer->setTransform (AffineTransform());
    rightPlacer->setCentrePosition (trainingCar->getRight() + FromInnerWheel, trainingCar->getY() + 190);
    rightPlacer->setVisible (false);

    getCurrentCheckPoints();
    arrangeRestingCars();

    resetPath();
}

//=================================================================================================
void ParkingLot::resetPath ()
{
    leftFrontPath.clear();
    rightFrontPath.clear();
    leftRearPath.clear();
    rightRearPath.clear();

    leftFrontPath.startNewSubPath (checkPoints[0].toFloat());
    rightFrontPath.startNewSubPath (checkPoints[1].toFloat());
    leftRearPath.startNewSubPath (checkPoints[2].toFloat());
    rightRearPath.startNewSubPath (checkPoints[3].toFloat());
}

//=================================================================================================
void ParkingLot::setDirection (const int newDirection)
{
    const int oldFangxiang = trainingCar->getDirection();

    trainingCar->setDirection (newDirection);
    placeTheCar (oldFangxiang, newDirection);

    leftPlacer->setVisible (false);
    rightPlacer->setVisible (false);

    if (shouldShowPole && newDirection == -1)
    {
        leftPlacer->setVisible (true);
        leftPlacer->toFront(false);
    }
    else if (shouldShowPole && newDirection == 1)
    {
        rightPlacer->setVisible (true);
        rightPlacer->toFront(false);
    }
}

//=================================================================================================
void ParkingLot::placeTheCar (const int oldFangxiang, const int newFangxiang)
{
    if (newFangxiang != 0 && oldFangxiang != newFangxiang)  
    {
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

        trainingCar->setCentrePosition (centerX, centerY);
        leftPlacer->setCentrePosition (trainingCar->getX() - FromInnerWheel, trainingCar->getY() + 190);
        rightPlacer->setCentrePosition (trainingCar->getRight() + FromInnerWheel, trainingCar->getY() + 190);

        trainingCar->setTransform (aft);
        leftPlacer->setTransform (aft);
        rightPlacer->setTransform (aft);
    }
}

//=================================================================================================
void ParkingLot::mouseUp (const MouseEvent& e)
{
    if (e.mods.isLeftButtonDown())
        setDirection (-1);
    else if (e.mods.isRightButtonDown())
        setDirection (1);
    else if (e.mods.isMiddleButtonDown())
        setDirection (0);
}

//=================================================================================================
void ParkingLot::mouseWheelMove (const MouseEvent&, const MouseWheelDetails& wheel)
{
    moveTheCar (wheel.deltaY > 0);
}

//=================================================================================================
void ParkingLot::moveTheCar (const bool backward)
{
    if (0 == trainingCar->getDirection())  // straight forward
    {
        const int dist (backward ? StraightStep : -StraightStep);
        trainingCar->setTopLeftPosition (trainingCar->getX(), trainingCar->getY() + dist);

        leftPlacer->setTopLeftPosition (leftPlacer->getX(), leftPlacer->getY() + dist);
        rightPlacer->setTopLeftPosition (rightPlacer->getX(), rightPlacer->getY() + dist);
    }
    else if (-1 == trainingCar->getDirection()) // -1 is turn left
    {
        turnDirection (backward, true);
    }
    else  if (1 == trainingCar->getDirection()) // 1 is turn right
    {
        turnDirection (!backward, false);
    }

    getCurrentCheckPoints();

    if (isCrashed())
    {
        if (AlertWindow::showNativeDialogBox (L"撞了!!",
                                              L"点击[确定]按钮或直接回车继续玩。\n"
                                              L"点击[取消]按钮复位车辆重新开始。",
                                              true))
            moveTheCar (!backward);
        else
            reset();
    }
    else  // link path point and draw them...
    {
        AffineTransform atf (trainingCar->getTransform());

        leftFrontPath.lineTo (checkPoints[0].toFloat().transformedBy (atf));
        rightFrontPath.lineTo (checkPoints[1].toFloat().transformedBy (atf));
        leftRearPath.lineTo (checkPoints[2].toFloat().transformedBy (atf));
        rightRearPath.lineTo (checkPoints[3].toFloat().transformedBy (atf));

        repaint();
    }
}

//=================================================================================================
void ParkingLot::showLeftFrontPath (const bool showThem)
{
    leftFrontPathShow = showThem;
    repaint();
}

//=================================================================================================
void ParkingLot::showRightFrontPath (const bool showIt)
{
    rightFrontPathShow = showIt;
    repaint();
}

//=================================================================================================
void ParkingLot::showLeftRearPath (const bool showIt)
{
    leftRearPathShow = showIt;
    repaint();
}

//=================================================================================================
void ParkingLot::showRightRearPath (const bool showIt)
{
    rightRearPathShow = showIt;
    repaint();
}

//=================================================================================================
void ParkingLot::showPole (const bool showIt)
{
    shouldShowPole = showIt;

    leftPlacer->setVisible (false);
    rightPlacer->setVisible (false);

    if (shouldShowPole && trainingCar->getDirection() == -1)
        leftPlacer->setVisible (true);
    else if (shouldShowPole && trainingCar->getDirection() == 1)
        rightPlacer->setVisible (true);
}

//=================================================================================================
void ParkingLot::showTrainingCar (const bool showIt)
{
    trainingCar->setAlpha (showIt ? 0.2f : alphaOfThings);
}

//=================================================================================================
const bool ParkingLot::isCrashed()
{
    AffineTransform atf (trainingCar->getTransform());

    for (int i = checkPoints.size(); --i >= 0; )
    {
        Point<int> p (checkPoints[i].transformedBy (atf));
        Component* comp = getComponentAt (p);

        if (!contains (p) || (comp != nullptr && comp != this && comp != trainingCar))
            return true;
    }

    return false;
}

//=================================================================================================
void ParkingLot::getCurrentCheckPoints ()
{
    checkPoints.clearQuick();

    // add 48 points of the car for crash-check
    const int x = trainingCar->getX();
    const int y = trainingCar->getY();
    const int w = trainingCar->getWidth();
    const int h = trainingCar->getHeight();
    const int r = trainingCar->getRight();
    const int b = trainingCar->getBottom();

    // front conners
    const int frontGap = 3;
    checkPoints.add (Point<int> (x + frontGap, y + frontGap));
    checkPoints.add (Point<int> (r - frontGap, y + frontGap));

    // rear path point
    checkPoints.add (Point<int> (x, b - h / 4)); 
    checkPoints.add (Point<int> (r, b - h / 4)); 

    // rear conners
    checkPoints.add (Point<int> (x + 4, b - 4));
    checkPoints.add (Point<int> (r - 4, b - 4));

    // top and bottom sides
    for (int i = 1; i < 8; ++i)
    {
        checkPoints.add (Point<int> (x + i * (w / 8), y - 1));
        checkPoints.add (Point<int> (x + i * (w / 8), b + 1));
    }
    
    // left and right sides
    for (int i = 1; i < 16; ++i)
    {
        if (i != 11)  // alreay added (rear path point)
        {
            checkPoints.add (Point<int> (x - 1, y + i * (h / 16)));
            checkPoints.add (Point<int> (r + 1, y + i * (h / 16)));
        }
    }
}

//=================================================================================================
void ParkingLot::arrangeRestingCars()
{
    restingCars.clear (true);
    
    const int hGap = 20;
    const int vGap = 45;
    
    const int hNumbers = getHeight() / (CarWidth + hGap) +
                         ((getHeight() % (CarWidth + hGap) == 0) ? 0 : 1);
    
    const int vNumbers = getHeight() / (CarLength + vGap) +
                         ((getHeight() % (CarLength + vGap) == 0) ? 0 : 1);
    
    // one side for h-car arrange
    for (int i = hNumbers; --i >= 0; )
    {
        if (i != 3)
        {
            RestingCar* car = new RestingCar();
            restingCars.add (car);
            addAndMakeVisible (car);
            car->setSize (CarLength, CarWidth);
            car->setTopLeftPosition (8, (CarWidth + hGap) * i + 10);
        }
    }
    
    for (int i = hNumbers; --i >= 0; )
    {
        if (!(i == 1 || i == 5))
        {
            RestingCar* car = new RestingCar();
            restingCars.add (car);
            addAndMakeVisible (car);
            car->setSize (CarLength, CarWidth);
            car->setTopLeftPosition (getWidth() - 8 - CarLength, (CarWidth + hGap) * i + 10);
        }
    }
    
    // v-car arrange
    for (int i = 0; i < vNumbers; ++i)
    {
        if (i != 1)
        {
            RestingCar* car = new RestingCar();
            restingCars.add (car);
            addAndMakeVisible (car);
            car->setSize (CarWidth, CarLength);
            car->setTopLeftPosition (getWidth() / 2 - CarWidth / 2, (CarLength + vGap) * i + 10);
        }
    }
}

//=================================================================================================
void ParkingLot::reset()
{
    leftPlacer->setVisible (false);
    rightPlacer->setVisible (false);

    trainingCar->setAlpha (alphaOfThings);

    resized();
    repaint();
}

//=================================================================================================
void ParkingLot::turnDirection (const bool shunshizhen, const bool turnLeft)
{
    pathHudu += shunshizhen ? EachHudu : -EachHudu;

    const int x = turnLeft ? (trainingCar->getX() - FromInnerWheel) : (trainingCar->getRight() + FromInnerWheel);
    const int y = trainingCar->getY() + 190;

    AffineTransform aft (AffineTransform::rotation (pathHudu, float(x), float(y)));
    trainingCar->setTransform (aft);
    rightPlacer->setTransform (aft);
    leftPlacer->setTransform (aft);
}

