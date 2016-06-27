#ifndef WordMap_h
#define WordMap_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "../libs/json.hpp"
#include "../AudealizeInterfaces.h"

using json = nlohmann::json;
using std::vector;
using std::string;

namespace Audealize {
    
    class WordMap  : public Component
    {
    public:
        WordMap (AudealizeAudioProcessor& p, json descriptors);
        ~WordMap();
        
        void paint (Graphics& g) override;
        void resized() override;
        void mouseMove (const MouseEvent& e) override;
        void mouseEnter (const MouseEvent& e) override;
        void mouseExit (const MouseEvent& e) override;
        void mouseDown (const MouseEvent& e) override;
        void mouseDrag (const MouseEvent& e) override;
                
        void wordSelected (String word);
        
        void toggleLanguage(string language, bool enabled);
        
        bool searchMap(String text);
        
    private:
        AudealizeAudioProcessor& processor;
        
        json json_dict, word_dict, languages;
        
        String selected, hovered;
        
        Point<float> hover_position, circle_position;
        
        vector<String> words;
        
        vector<Point<float>> points, excluded_points;
        
        vector<vector<float>> params;
        
        vector<int> font_sizes;
        
        vector<Colour> colors;
        
        float min_variance, max_variance, variance_thresh;
        
        int center_index, word_count;
        
        bool init_map, has_been_hovered;
        
        NormalisableRange<int> alpha_range;
        
        //=====================================================================
        
        const int pad = 2;
        const float unhighlighted_alpha_value = 0.7f * 255;
        const float hover_alpha_value = 0.15f * 255;
        
        const String TYPEFACE = "Helvetica";
        const int BASE_FONT_SIZE = 14;
        
        //=====================================================================
        // Private helper functions
        
        void loadPoints();
        
        bool check_for_collision(Point<float> point, vector<Point<float>> plotted, float dist);
        
        bool inRadius(Point<float> pt , Point<float> centerpt, float r);
        
        void plot_word(String word, Colour color, int font_size, Point<float> point, Graphics& g);
        
        int find_closest_word_in_map(Point<float> point);
        
        float calc_distance(Point<float> point1, Point<float> point2, Point<float> slack = Point<float>(1,1));
        
        void normalizePoints();
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WordMap)
    };
    
}
#endif
