/*
  ==============================================================================

    Main application class.

  ==============================================================================
*/

#include "JuceHeader.h"
#include "MainComponent.h"

//=========================================================================
class ParkingLotLaF : public LookAndFeel_V3
{
public:
    /*virtual Font getTextButtonFont (TextButton&, int) override
    {
        return Font (16.f);
    }
    //=========================================================================
    virtual void drawToggleButton (Graphics& g, ToggleButton& button, 
        bool isMouseOverButton, bool isButtonDown) override
    {
        float fontSize = jmin (17.0f, button.getHeight() * 0.95f);
        const float tickWidth = fontSize * 1.1f;

        drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
            tickWidth, tickWidth,
            button.getToggleState(),
            button.isEnabled(),
            isMouseOverButton,
            isButtonDown);

        g.setColour (button.findColour (ToggleButton::textColourId));
        g.setFont (fontSize);

        if (!button.isEnabled())
            g.setOpacity (0.5f);

        const int textX = (int) tickWidth + 5;

        g.drawFittedText (button.getButtonText(),
            textX, 0,
            button.getWidth() - textX - 2, button.getHeight(),
            Justification::centredLeft, 10);
    }*/

};

//==============================================================================
class ParkingLotApplication  : public JUCEApplication
{
public:
    //==============================================================================
    ParkingLotApplication() {}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return true; }

    //==============================================================================
    void initialise (const String&) override    
    { 
        laf = new ParkingLotLaF();
        LookAndFeel::setDefaultLookAndFeel (laf);
        laf->setDefaultSansSerifTypefaceName ("Microsoft Yahei");
        
        mainWindow = new MainWindow (getApplicationName()); 
    }
    
    void shutdown() override    { mainWindow = nullptr; }
    void systemRequestedQuit() override    { quit(); }
    void anotherInstanceStarted (const String& ) override    { }

    //==============================================================================
    /** Main window */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);

			setResizable (true, false);
			setResizeLimits (1280, 780, 3800, 3800);

			centreWithSize (getWidth (), getHeight ());
			setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
    ScopedPointer<ParkingLotLaF> laf;
};

//==============================================================================

START_JUCE_APPLICATION (ParkingLotApplication)
