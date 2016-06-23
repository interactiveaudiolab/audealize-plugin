#include "AudealizeUI.h"

using namespace std;

AudealizeUI::AudealizeUI (AudealizeAudioProcessor& p, String pathToPoints) : processor(p), mPathToPoints(pathToPoints)
{
    //Load file with points, parse into nlohman::json object
    ifstream infile;
    infile.open(mPathToPoints.toUTF8());
    mPoints = json::parse(infile);

    //addAndMakeVisible (mMap = new Component());
    mMap->setName ("Descriptor Map");

//    addAndMakeVisible (textEditor = new TextEditor ("new text editor"));
//    textEditor->setMultiLine (false);
//    textEditor->setReturnKeyStartsNewLine (false);
//    textEditor->setReadOnly (false);
//    textEditor->setScrollbarsShown (true);
//    textEditor->setCaretVisible (true);
//    textEditor->setPopupMenuEnabled (true);
//    textEditor->setColour (TextEditor::outlineColourId, Colours::green);
//    textEditor->setColour (TextEditor::shadowColourId, Colour (0x00a1a1a1));
//    textEditor->setText (String());


    setSize (600, 400);
}

AudealizeUI::~AudealizeUI()
{
    mMap = nullptr;
    textEditor = nullptr;
}

//==============================================================================
void AudealizeUI::paint (Graphics& g)
{
    vector<Point<float>> plotted(0);
    String word, lang;
    float agreement;
    int num, font_size;
    Point<float> point(0,0), center_point(0,0);
    Colour color;
    
    bool hover_radius, in_radius, collision;
    
    int i = 0;
    for (json::iterator it = mPoints.begin(); it != mPoints.end(); ++it, ++i) {
        word      = it.value()["word"];
        lang      = it.value()["lang"];
        agreement = it.value()["agreement"];
        num       = it.value()["num"];
        point.setX((0.1f + (float)it.value()["x"] * 0.8f) * getWidth());
        point.setY((0.05f + (float)it.value()["y"] * 0.9f) * getHeight());
        //@TODO font_size, color, calc center_point
        
        collision = check_for_collision(point, plotted, font_size + word.length() + pad);
        
        
        if (hovering) {
            hover_radius = inRadius(point, hover_position, 75);
        }
        
        if(!collision || hover_radius || in_radius){
            plot_word(word, color, font_size, point, g);
        }
        
        plotted.push_back(point);
    }
}

void AudealizeUI::resized()
{
    mMap->setBounds (0, 0, 616, 400);
    textEditor->setBounds (8, 8, 150, 24);
}

void AudealizeUI::mouseMove (const MouseEvent& e)
{
}

void AudealizeUI::mouseEnter (const MouseEvent& e)
{
}

void AudealizeUI::mouseDown (const MouseEvent& e)
{
}

void AudealizeUI::mouseDrag (const MouseEvent& e)
{
}

bool AudealizeUI::check_for_collision(Point<float> point, vector<Point<float>> plotted, float dist){
    float distance, dx, dy;
    Point<float> slack(0.125f, 1.5f);
    vector<Point<float>>::iterator it;
    for (it = plotted.begin(); it < plotted.end(); it++){
        dx = point.getX() - it->getX();
        dy = point.getY() - it->getY();
        distance = sqrt(slack.getX() * powf(dx, 2) + slack.getY() * powf(dy, 2));
        if (distance < dist){
            return true;
        }
    }
    return false;
}

bool AudealizeUI::inRadius(Point<float> pt , Point<float> centerpt, float r){
    float distance, dx, dy;
    dx = pt.getX() - centerpt.getX();
    dy = pt.getY() - centerpt.getY();
    
    distance = sqrt(powf(dx, 2) + powf(dy, 2));
    
    if (distance < r){
        return true;
    }
    return false;
}

void AudealizeUI::plot_word(String word, Colour color, int font_size, Point<float> point, Graphics& g){
    float x, y, width;
    
    width = word.length() * font_size; //@TODO verify that this makes sense
    x = point.getX() - width * 0.5f;
    y = point.getY() - font_size * 0.5f;
    
    Rectangle<float> rect(x, y, width, font_size);
    
    Font font = Font(font_name, font_size, Font::plain);
    g.setFont(font);

    g.drawText(word, rect, Justification::centred);
}
