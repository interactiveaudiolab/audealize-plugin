#include "WordMap.h"

using namespace std;
using json = nlohmann::json;

namespace Audealize {
    
    
    WordMap::WordMap (AudealizeAudioProcessor& p, json descriptors) : processor(p), json_dict(descriptors), languages(0), words(0), points(0), excluded_points(0), params(0), colors(0), font_sizes(0)
    {
        
        // initialize circle positions
        circle_position = Point<float>(150,50);
        hover_position = Point<float>(100, 50);
        
        // default size of info text
        infotext_size = 12;
        
        // Instance variables
        min_variance     = json_dict.begin().value()["agreement"];
        max_variance     = (json_dict.end() - 1).value()["agreement"];
        variance_thresh  = max_variance;
        alpha_range      = NormalisableRange<int>(0,255);
        word_count       = 0;
        center_index     = -1;
        init_map         = true;
        has_been_hovered = false;
        languages = {};
        
        startTimerHz(60);
        
        // set default size of component
        setSize (800, 400);
        
        loadPoints();
    }
    
    WordMap::~WordMap()
    {
    }
    
    void WordMap::loadPoints(){
        words.clear();
        points.clear();
        excluded_points.clear();
        params.clear();
        colors.clear();
        font_sizes.clear();
        word_dict.clear();
        nums.clear();
        word_count = 0;
        
        float alpha_max  = (1 - 0.92f * logf(5 * min_variance + 1));
        
        string word, lang;
        float agreement, alpha, dat, fontsize;
        int num;
        Point<float> point;
        Colour color;
        
        for (json::iterator it = json_dict.begin(); it != json_dict.end(); ++it) {
            lang = it.value()["lang"];
            // add languages to dictionary if not already present
            if (languages.find(lang) == languages.end()){
                languages[lang] = true;
            }
            
            point.setX((float)it.value()["x"]);
            point.setY((float)it.value()["y"]);
            
            
            // if word is in selected language(s), add to map
            if (languages[lang]){
                word      = it.value()["word"];
                agreement = it.value()["agreement"];
                num       = it.value()["num"];
                
                // add properties to respective vectors/dictionaries
                words.push_back(word);
                word_dict[word] = word_count;
                points.push_back(point);
                params.push_back(it.value()["settings"]);
                nums.push_back(num);
                
                // calculate color. random rgb, alpha based on agreement score
                alpha = (1 - 0.92f * logf(5 * agreement + 1)) / alpha_max;
                
                color = Colour::fromRGBA(rand() % 210, rand() % 210, rand() % 210, alpha_range.snapToLegalValue(alpha*255));
                colors.push_back(color);
                
                // calculate font size
                dat = agreement - min_variance;
                dat = dat / (max_variance - min_variance) * 0.7f + 0.3f;
                fontsize = base_font_size * pow(5, 1 / (5 * dat)); //@TODO
                font_sizes.push_back(roundToInt(fontsize));
                
                word_count++;
            }
            else {
                excluded_points.push_back(point);
            }
        }
        normalizePoints();
        
        sendActionMessage("_languagechanged");
    }
    
    void WordMap::paint (Graphics& g)
    {
        vector<Point<float>> plotted(0);
        String word;
        int font_size, hover_center;
        Point<float> point;
        Colour color;
        bool hover_radius, in_radius, collision;
        
        setDirty(false);
        
        // Draw border, background
        g.setColour(Colour(128, 128, 128));
        g.drawRect(this->getLocalBounds());
        
        // if mouse is over map, find word being hovered over
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
        } // end word loop
        
        // Draw circles
        if (!init_map){
            g.setColour(Colour::fromRGBA(128, 128, 128, 150));
            //g.drawImage(ImageCache::getFromMemory(Resources::circleDark_png, Resources::circleDark_pngSize) , circle_position.getX()-16, circle_position.getY()-16, 32, 32, 0, 0, 32, 32);
            g.drawEllipse(circle_position.getX()-16, circle_position.getY()-16, 32, 32, 2);
        }
        if (has_been_hovered && !isMouseButtonDown()){
            g.setColour(Colour::fromRGBA(200, 200, 200, 150));
            g.drawEllipse(getMouseXYRelative().getX()-16, getMouseXYRelative().getY()-16, 32, 32, 2);
        }
        
        
        // Draw info text
        String info_text = String("Map built with " + String(word_count) + " words. Nearby words have similar effects.");
        
        Font font = Font(TYPEFACE, infotext_size, Font::plain);
        g.setFont(font);
        g.setColour(Colours::grey);
        g.drawText(info_text, getWidth() - 420, getHeight() - 22, 412, 18, Justification::bottomRight);
        
        if (!init_map) {
            info_text = String("\"" + words[center_index] + "\" learned from " + String(nums[center_index]) + " contributions.");
            g.drawText(info_text, 6, getHeight() - 22, 250, 18, Justification::bottomLeft);
        }
    }
    
    void WordMap::resized()
    {
        // update circle position
        if (!init_map){
            Point<float> point;
            point.setX((0.1f + points[center_index].getX() * 0.8f) * getWidth());
            point.setY((0.05f + points[center_index].getY() * 0.9f) * getHeight());
            
            circle_position = point;
        }
    }
    
    void WordMap::mouseMove (const MouseEvent& e)
    {
        hover_position = getMouseXYRelative().toFloat();
        setDirty();
    }
    
    void WordMap::mouseEnter (const MouseEvent& e)
    {
        has_been_hovered = true;
        hover_position = getMouseXYRelative().toFloat();
        setDirty();
    }
    
    void WordMap::mouseExit(const MouseEvent& e){
        hover_position = getMouseXYRelative().toFloat();
    }
    
    void WordMap::mouseDown (const MouseEvent& e)
    {
        init_map = false;
        circle_position = getMouseXYRelative().toFloat();
        center_index = find_closest_word_in_map(getMouseXYRelative().toFloat());
        wordSelected(words[center_index]);
        setDirty();
    }
    
    void WordMap::mouseDrag (const MouseEvent& e)
    {
        circle_position = getMouseXYRelative().toFloat();
        center_index = find_closest_word_in_map(getMouseXYRelative().toFloat());
        wordSelected(words[center_index]);
        setDirty();
    }
    
    void WordMap::wordSelected(String word){
        sendActionMessage(word); // broadcast a message containing the descriptor to all ActionListeners. this will
        
        init_map = false; // word has been selected, map is no longer in initial state
        
        int index = word_dict[word.toRawUTF8()]; // find the index of the word that was selected
        
        if (index < words.size()) // make sure it's a valid index
        {
            center_index = index;
            
            // calculate the position of the word in the map and update the circle position
            Point<float> point;
            point.setX((0.1f + points[index].getX() * 0.8f) * getWidth());
            point.setY((0.05f + points[index].getY() * 0.9f) * getHeight());
            circle_position = point;
            
            processor.settingsFromMap(params[index]); // tell the AudioProcessor to apply the effect associated witht the descriptor
            
            setDirty(); // wordmap needs to be repainted
        }
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
    
    bool WordMap::inRadius(Point<float> point, Point<float> centerpoint, float radius){
        return calc_distance(point, centerpoint) < radius;
    }
    
    void WordMap::plot_word(String word, Colour color, int font_size, Point<float> point, Graphics& g){
        float x, y, width;
        
        width = word.length() * font_size * 2; // not precise, that's ok
        x = point.getX() - width * 0.5f;
        y = point.getY() - font_size * 0.5f;
        
        Rectangle<float> rect(x, y, width, font_size);
        
        Font font = Font(TYPEFACE, font_size, Font::plain);
        g.setFont(font);
        
        g.setColour(color);
        
        g.drawText(word, rect, Justification::centred);
    }
    
    int WordMap::find_closest_word_in_map(Point<float> point){
        int bestword = 0;
        float mindist = FLT_MAX;
        float dist;
        Point<float> pt;
        
        for (int i = 0; i < points.size(); i++){
            // calculate the position of the points in pixels
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
    
    bool WordMap::compareX(Point<float> p1, Point<float> p2){
        return p1.getX() < p2.getX();
    }
    
    bool WordMap::compareY(Point<float> p1, Point<float> p2){
        return p1.getY() < p2.getY();
    }
    
    void WordMap::normalizePoints(){
        if (points.size() > 0){
            float x_max = max_element(points.begin(), points.end(), compareX)->getX();
            
            float x_min = min_element(points.begin(), points.end(), compareX)->getX();
            
            float y_max = max_element(points.begin(), points.end(), compareY)->getY();
            
            float y_min = min_element(points.begin(), points.end(), compareY)->getY();
            
            if (excluded_points.size() > 0){
                x_max = max(x_max, max_element(excluded_points.begin(), excluded_points.end(), compareX)->getX());
                x_min = min(x_min, min_element(excluded_points.begin(), excluded_points.end(), compareX)->getX());
                
                y_max = max(y_max, max_element(excluded_points.begin(), excluded_points.end(), compareY)->getY());
                y_min = min(y_min, min_element(excluded_points.begin(), excluded_points.end(), compareY)->getY());
            }
            
            vector<Point<float>>::iterator it;
            for (it = points.begin(); it < points.end(); it++){
                it->setX((it->getX() - x_min) / (x_max - x_min));
                it->setY((it->getY() - y_min) / (y_max - y_min));
            }
        }
    }
    
    void WordMap::toggleLanguage(string language, bool enabled){
        languages[language] = enabled;
        loadPoints();
        setDirty();
    }
    
    bool WordMap::searchMap(juce::String text){
        for(vector<String>::iterator it = words.begin(); it < words.end(); it++){
            if (text.equalsIgnoreCase(*it)){
                wordSelected(*it);
                return true;
            }
        }
        return false;
    }
    
    void WordMap::timerCallback(){
        if (isdirty){
            repaint();
        }
    }
    
    void WordMap::setMinFontSize(int fontSize){
        vector<Colour> temp = colors;
        base_font_size = fontSize;
        loadPoints();
        colors = temp;
    }
    
    void WordMap::setDirty(bool dirty){
        isdirty = dirty;
    }
    
}// namespace Audealize