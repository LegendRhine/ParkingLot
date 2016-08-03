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
const int timerIntervel = 50;

//==============================================================================
ParkingLot::ParkingLot()
	: pathHudu (0.0f),
    speedLevel (2),
    leftFrontPathShow (false),
    rightFrontPathShow (false),
    leftRearPathShow (true),
    rightRearPathShow (true),
    shouldShowPole (false),
    xiexiang (false),
    fanxiexiang (false),
    clearAllRestingCars (false),
    isBackNow (false)
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
	trainingCar->setCentrePosition (getWidth() - CarLength - 95, getHeight() - 140);
    trainingCar->reset();

    leftPlacer->setTransform (AffineTransform());
    leftPlacer->setCentrePosition (trainingCar->getX() - FromInnerWheel, trainingCar->getY() + 190);
    leftPlacer->setVisible (false);

    rightPlacer->setTransform (AffineTransform());
    rightPlacer->setCentrePosition (trainingCar->getRight() + FromInnerWheel, trainingCar->getY() + 190);
    rightPlacer->setVisible (false);

    getCurrentCheckPoints();
    resetPath();
    repaint();

    arrangeRestingCars (xiexiang, fanxiexiang);
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
    isBackNow = (wheel.deltaY > 0);
    moveTheCar (isBackNow);
}

//=================================================================================================
void ParkingLot::timerCallback ()
{
    moveTheCar (isBackNow);
}

//=================================================================================================
void ParkingLot::moveTheCar (const bool backward)
{
    if (0 == trainingCar->getDirection())  // straight forward
    {
        const int dist = (backward ? StraightStep : -StraightStep);
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
        stopTimer();

        if (AlertWindow::showNativeDialogBox (L"撞了!!",
                                              L"点击[确定]按钮或直接回车继续玩。\n"
                                              L"点击[取消]按钮复位车辆重新开始。",
                                              true))
            moveTheCar (!backward);
        else
            reset();
    }
    else if (isSuccessful())
    {
        stopTimer();
        AlertWindow::showNativeDialogBox (L"漂亮!!", L"完美入位!!", false);
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

    //if (speedLevel == 2)
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
void ParkingLot::setSlopedRestingCars (const bool slope, const bool backslash)
{
    xiexiang = slope;
    fanxiexiang = backslash;

    resized();
}

//=================================================================================================
void ParkingLot::clearRestingCars ()
{
    clearAllRestingCars = true;
    restingCars.clear();

    stopAreaOne = stopAreaTwo = stopAreaThree = nullptr;

    // tell maincomponent don't draw stop-lines
    getParentComponent()->repaint();
}

//=================================================================================================
void ParkingLot::setSpeed (const int speedLevel_)
{
    stopTimer();
    speedLevel = speedLevel_;

    startTimer (speedLevel * timerIntervel);
}

//=================================================================================================
const bool ParkingLot::isCrashed()
{
    AffineTransform atf (trainingCar->getTransform());

    for (int i = checkPoints.size(); --i >= 0; )
    {
        Point<int> p (checkPoints[i].transformedBy (atf));

        if (!contains (p))
            return true;

        Component* comp = getComponentAt (p);

        for (int j = 0; j < restingCars.size(); ++j)
        {
            if (comp == restingCars[j])
                return true;
        }
    }

    return false;
}

//=================================================================================================
const bool ParkingLot::isSuccessful ()
{
    if (stopAreaOne == nullptr || stopAreaTwo == nullptr || stopAreaThree == nullptr)
        return false;

    AffineTransform atf (trainingCar->getTransform());

    for (int i = checkPoints.size(); --i >= 0; )
    {
        Point<int> p (checkPoints[i].transformedBy (atf));

        Rectangle<int> stopOne (stopAreaOne->getBounds().transformedBy (stopAreaOne->getTransform()));
        Rectangle<int> stopTwo (stopAreaTwo->getBounds().transformedBy (stopAreaTwo->getTransform()));
        Rectangle<int> stopThree (stopAreaThree->getBounds().transformedBy (stopAreaThree->getTransform()));

        if (stopOne.contains (p) || stopTwo.contains (p) || stopThree.contains (p))
            continue;
        else
            return false;
    }

    return true;
}

//=================================================================================================
void ParkingLot::getCurrentCheckPoints ()
{
    checkPoints.clearQuick();

    // add 50 points of the car for crash-check
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
    checkPoints.add (Point<int> (x, b - h / 4 + 10)); 
    checkPoints.add (Point<int> (r, b - h / 4 + 10)); 

    // addtional 2 points
    checkPoints.add (Point<int> (x, b - h / 4 - 5));
    checkPoints.add (Point<int> (r, b - h / 4 - 5));

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
void ParkingLot::arrangeRestingCars (const bool slope, const bool backslash)
{
    restingCars.clear();
    stopAreaOne = stopAreaTwo = stopAreaThree = nullptr;

    if (clearAllRestingCars)
        return;
    
    const int hGap = 25 + (slope ? 50 : 0);
    const int vGap = 45;    
    const int hNumbers = getHeight() / (CarWidth + hGap) +
                         ((getHeight() % (CarWidth + hGap) == 0) ? 0 : 1);    
    const int vNumbers = getHeight() / (CarLength + vGap) +
                         ((getHeight() % (CarLength + vGap) == 0) ? 0 : 1);
    
    // left side for h-car arrange
    for (int i = hNumbers; --i >= 0; )
    {
        Component* car = nullptr;

        if (i == 3)
        {
            car = stopAreaOne = new StopArea();
            car->setSize (CarLength + 8, CarWidth + 8);
            car->setTopLeftPosition (6, (CarWidth + hGap) * i + 14);
        }
        else
        {
            car = new RestingCar();
            restingCars.add (car);
            car->setSize (CarLength, CarWidth);
            car->setTopLeftPosition (10, (CarWidth + hGap) * i + 18);            
        }
        
        addAndMakeVisible (car);
        car->toBack();

        // slope and backslash
        if (slope)
        {
            const float cx (car->getBounds().toFloat().getCentreX());
            const float cy (car->getBounds().toFloat().getCentreY());
            const float hudu = float_Pi / 4.0f;

            car->setTransform (AffineTransform::rotation (backslash ? hudu : -hudu, cx, cy));
        }
    }
    
    // right side for h-car arrange
    for (int i = hNumbers; --i >= 0; )
    {
        Component* car = nullptr;

        if (i == 1)
        {
            car = stopAreaTwo = new StopArea();
            car->setSize (CarLength + 8, CarWidth + 8);
            car->setTopLeftPosition (getWidth() - 14 - CarLength, (CarWidth + hGap) * i + 4);
        }
        else
        {
            car = new RestingCar();
            restingCars.add (car);
            car->setSize (CarLength, CarWidth);
            car->setTopLeftPosition (getWidth() - 8 - CarLength, (CarWidth + hGap) * i + 8);
        }
        
        addAndMakeVisible (car);
        car->toBack();

        // slope and backslash
        if (slope)
        {
            const float cx (car->getBounds().toFloat().getCentreX());
            const float cy (car->getBounds().toFloat().getCentreY());
            const float hudu = float_Pi / 4.0f;

            car->setTransform (AffineTransform::rotation (backslash ? -hudu : hudu, cx, cy));
        }
    }
    
    // v-car arrange
    for (int i = 0; i < vNumbers; ++i)
    {
        Component* car = nullptr;

        if (i != 1)
        {
            car = new RestingCar();
            restingCars.add (car);
            car->setSize (CarWidth, CarLength);
            car->setTopLeftPosition (getWidth() / 2 - CarWidth / 2, (CarLength + vGap) * i + 8);
        }
        else
        {
            car = stopAreaThree = new StopArea();
            car->setSize (CarWidth + 8, CarLength + 8);
            car->setTopLeftPosition (getWidth() / 2 - CarWidth / 2 - 4, (CarLength + vGap) * i + 10);
        }

        addAndMakeVisible (car);
        car->toBack();
    }
}

//=================================================================================================
void ParkingLot::setAutoMove (const bool shouldAutoMove)
{
    if (shouldAutoMove)
    {
        startTimer (speedLevel * timerIntervel);
    }
    else
    {
        stopTimer();
    }
}

//=================================================================================================
void ParkingLot::reset()
{
    leftPlacer->setVisible (false);
    rightPlacer->setVisible (false);

    trainingCar->setAlpha (alphaOfThings);
    clearAllRestingCars = false;

    stopTimer();
    resized();
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

