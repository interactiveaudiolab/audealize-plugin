#include "WordMap.h"

using namespace std;

WordMap::WordMap (AudealizeAudioProcessor& p, String pathToPoints) : processor(p), path_to_points(pathToPoints), languages(0), words(0), points(0), excluded_points(0), params(0), colors(0), font_sizes(0)
{
    // Load file with json_dict, parse into nlohman::json object
    ifstream infile;
    infile.open(path_to_points.toUTF8());
    json_dict = json::parse(infile);
    //
    
    languages.push_back("English"); //@TODO: language select
    
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

    min_variance     = json_dict.begin().value()["agreement"];
    max_variance     = (json_dict.end() - 1).value()["agreement"];
    variance_thresh  = max_variance;
    alpha_range      = NormalisableRange<int>(0,255);
    float alpha_max  = (1 - 0.92f * logf(5 * min_variance + 1));
    word_count       = 0;
    center_index     = -1;
    init_map         = true;
    has_been_hovered = false;
    
    // loop variables
    String word, lang;
    float agreement, alpha, dat, fontsize;
    int num;
    Point<float> point;
    Colour color;
    
    // loop through words
    for (json::iterator it = json_dict.begin(); it != json_dict.end(); ++it) {
        lang = it.value()["lang"];
        point.setX((float)it.value()["x"]);
        point.setY((float)it.value()["y"]);

        // if word is in selected language(s), add to map
        if (std::find(languages.begin(), languages.end(), lang) != languages.end()){
            word      = it.value()["word"];
            agreement = it.value()["agreement"];
            num       = it.value()["num"];

        
            // add properties to respective vectors/dictionaries
            words.push_back(word);
            word_dict[word.toRawUTF8()] = word_count;
            points.push_back(point);
            params.push_back(it.value()["settings"]);
            
            // calculate color. random rgb, alpha based on agreement score
            alpha = (1 - 0.92f * logf(5 * agreement + 1)) / alpha_max;

            color = Colour::fromRGBA(rand() % 256, rand() % 256, rand() % 256, alpha_range.snapToLegalValue(alpha*255));
            colors.push_back(color);
            
            // calculate font size
            dat = agreement - min_variance;
            dat = dat / (max_variance - min_variance) * 0.7f + 0.3f;
            fontsize = BASE_FONT_SIZE * pow(5, 1 / (5 * dat)); //@TODO
            font_sizes.push_back(roundToInt(fontsize));
            
            if ( word == "muffled"){
                DBG("agreement: " << agreement);
                DBG("fontsize: " << fontsize);
                DBG("minvariance: " << min_variance);
                DBG("maxvariance: " << max_variance);
            }
            
            word_count++;
        }
        else {
            excluded_points.push_back(point);
        }
    } // loop through json_dict

    DBG("wordcount: " << word_count);
    DBG("unhighlighted alpha: " << alpha_range.snapToLegalValue( unhighlighted_alpha_value));
    normalize_points();
    
    circle_position = Point<float>(150,50);
    hover_position = Point<float>(100, 50);
    
    setSize (800, 600);
}

WordMap::~WordMap()
{
    text_editor = nullptr;
}

//==============================================================================
void WordMap::paint (Graphics& g)
{
    vector<Point<float>> plotted(0);
    String word;
    int font_size, hover_center;
    Point<float> point;
    Colour color;
    bool hover_radius, in_radius, collision;
    
    // Draw border, background
    g.setColour(Colour(128, 128, 128));
    g.drawRect(getBounds());
    
    if (isMouseOverOrDragging()){
        hover_center = find_closest_word_in_map(hover_position);
    }
    
    // Draw words
    for (int i = 0; i < words.size(); i++) {
        in_radius    = false;
        hover_radius = false;
        word         = words[i];
        color        = colors[i];
        font_size    = font_sizes[i];
        
        point.setX((0.1f + points[i].getX() * 0.8f) * getWidth());
        point.setY((0.05f + points[i].getY() * 0.9f) * getHeight());
        
        collision = check_for_collision(point, plotted, font_size + word.length() + pad);
        
        if (!init_map) {
            in_radius = inRadius(point, circle_position, 75);
        }
        
        if (isMouseOverOrDragging()) {
            hover_radius = inRadius(point, hover_position, 75);
        }

        // set word alpha
        if (i == center_index || i == hover_center){
            color = Colour::fromRGBA(color.getRed(), color.getGreen(), color.getBlue(), 255);
        }
        else {
            if (in_radius || hover_radius) {
                color = Colour::fromRGBA(color.getRed(), color.getGreen(), color.getBlue(), alpha_range.snapToLegalValue(hover_alpha_value));
            }
            else {
                color = Colour::fromRGBA(color.getRed(), color.getGreen(), color.getBlue(), alpha_range.snapToLegalValue( unhighlighted_alpha_value));
            }
        }
        if (init_map && !hover_radius){
            color = Colour::fromRGBA(color.getRed(), color.getGreen(), color.getBlue(), 255);
        }
        // end set alpha
        
        if(!collision || hover_radius || in_radius) {
            plot_word(word, color, font_size, point, g);
        }
        
        
        plotted.push_back(point);
    } // end for
    
    // Draw circles
    if (!init_map){
        g.setColour(Colour(128,128,128));
        //g.drawImage(ImageCache::getFromMemory(Resources::circleDark_png, Resources::circleDark_pngSize) , circle_position.getX()-16, circle_position.getY()-16, 32, 32, 0, 0, 32, 32);
        g.drawEllipse(circle_position.getX()-16, circle_position.getY()-16, 32, 32, 2);
    }
    if (has_been_hovered){
        g.setColour(Colour(200,200,200));
        g.drawEllipse(hover_position.getX()-16, hover_position.getY()-16, 32, 32, 2);
    }
    
    
    // Draw info text
    String info_text = String("Map built with " + String(word_count) + " words. Nearby words have similar effects.");
    plot_word(info_text, Colours::grey, 10, Point<float>(140, getHeight() - 10), g);
}

void WordMap::resized()
{
    //textEditor->setBounds (8, 8, 150, 24);
}

void WordMap::mouseMove (const MouseEvent& e)
{
    hover_position = getMouseXYRelative().toFloat();
    repaint();
}

void WordMap::mouseEnter (const MouseEvent& e)
{
    has_been_hovered = true;
    hover_position = getMouseXYRelative().toFloat();
    //setMouseCursor(MouseCursor(ImageCache::getFromMemory(Resources::circleLight_png, Resources::circleLight_pngSize), 16, 16));
    repaint();
}

void WordMap::mouseExit(const MouseEvent& e){
    hover_position = getMouseXYRelative().toFloat();
    //setMouseCursor(MouseCursor::StandardCursorType::NormalCursor);
}

void WordMap::mouseDown (const MouseEvent& e)
{
    init_map = false;
    circle_position = getMouseXYRelative().toFloat();
    center_index = find_closest_word_in_map(getMouseXYRelative().toFloat());
    wordSelected(words[center_index]);
    repaint();
}

void WordMap::mouseDrag (const MouseEvent& e)
{
    circle_position = getMouseXYRelative().toFloat();
    center_index = find_closest_word_in_map(getMouseXYRelative().toFloat());
    wordSelected(words[center_index]);
    repaint();
}

void WordMap::wordSelected(String word){
    int index = word_dict[word.toRawUTF8()];
    processor.settingsFromMap(params[index]);
}

bool WordMap::check_for_collision(Point<float> point, vector<Point<float>> plotted, float dist){
    Point<float> slack(0.25f, 1.5f);
    vector<Point<float>>::iterator it;

    for (it = plotted.begin(); it < plotted.end(); it++){
        if (calc_distance(point, *it, slack) < dist){
            return true;
        }
    }
    return false;
}

bool WordMap::inRadius(Point<float> pt , Point<float> centerpt, float r){
    return calc_distance(pt, centerpt) < r;
}

void WordMap::plot_word(String word, Colour color, int font_size, Point<float> point, Graphics& g){
    float x, y, width;
    
    width = word.length() * font_size * 2; //@TODO verify that this makes sense
    x = point.getX() - width * 0.5f;
    y = point.getY() - font_size * 0.5f;
    
    Rectangle<float> rect(x, y, width, font_size);
    
    Font font = Font(TYPEFACE, font_size, Font::plain);
    g.setFont(font);
    g.setColour(color);
    g.drawText(word, rect, Justification::centred);
    
    //DBG("\nPlotting word: \"" << word << "\" at point (" << point.getX() << ", " << point.getY() << ")");
    //DBG("Font size: " << font_size);
    //DBG("Color: " << color.getRed() << ", " << color.getGreen() << ", " << color.getBlue() << ", " << color.getAlpha());
}

int WordMap::find_closest_word_in_map(Point<float> point){
    int bestword = 0;
    float mindist = FLT_MAX;
    float dist;
    Point<float> pt;
    for (int i = 0; i < points.size(); i++){
        pt.setX((0.1f + points[i].getX() * 0.8f) * getWidth());
        pt.setY((0.05f + points[i].getY() * 0.9f) * getHeight());
        
        dist = calc_distance(pt, point);
        
        if (dist < mindist){
            mindist = dist;
            bestword = i;
        }
    }
    return bestword;
}

float WordMap::calc_distance(Point<float> point1, Point<float> point2, Point<float> slack){
    float dx = point1.getX() - point2.getX();
    float dy = point1.getY() - point2.getY();
    
    return sqrt(slack.getX() * powf(dx, 2) + slack.getY() * powf(dy, 2));
}

// Comparison functions for normalizing a vector<Point<float>>
bool compareX(Point<float> p1, Point<float> p2){
    return p1.getX() < p2.getX();
}

bool compareY(Point<float> p1, Point<float> p2){
    return p1.getY() < p2.getY();
}


void WordMap::normalize_points(){
    float x_max = max_element(points.begin(), points.end(), compareX)->getX();
    x_max = max(x_max, max_element(excluded_points.begin(), excluded_points.end(), compareX)->getX());
    
    float x_min = min_element(points.begin(), points.end(), compareX)->getX();
    x_min = min(x_min, min_element(excluded_points.begin(), excluded_points.end(), compareX)->getX());
    
    float y_max = max_element(points.begin(), points.end(), compareY)->getY();
    y_max = max(y_max, max_element(excluded_points.begin(), excluded_points.end(), compareY)->getY());
    
    float y_min = min_element(points.begin(), points.end(), compareY)->getY();
    y_min = min(y_min, min_element(excluded_points.begin(), excluded_points.end(), compareY)->getY());
    
    vector<Point<float>>::iterator it;
    for (it = points.begin(); it < points.end(); it++){
        it->setX((it->getX() - x_min) / (x_max - x_min));
        it->setY((it->getY() - y_min) / (y_max - y_min));
    }
}

