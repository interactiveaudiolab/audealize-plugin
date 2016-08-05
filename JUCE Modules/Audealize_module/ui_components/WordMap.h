//
//  WordMap.h
//
//  A JUCE gui component that creates a map of descriptors for Audealize plugins
//
//  Instantiate with an AudealizeAudioProcessor and an nlohmann::json dictionary of descriptors and their associated data
//

#ifndef WordMap_h
#define WordMap_h

#include "../utils/json.hpp"
#include "../audio_processors/AudealizeAudioProcessor.h"
#include "TraditionalUIComponent.h"
#include <float.h> // needed for FLT_MAX

using json = nlohmann::json;
using std::vector;
using std::string;

namespace Audealize {
    
    class WordMap  : public Component,
                     public Timer,
                     public ActionBroadcaster
    {
    public:
        /**
         *  Constructor
         *
         *  @param p            an AudealizeAudioProcessor
         *  @param descriptors  an nlohmann::json dictionary of descriptors and their associated data
         */
        WordMap (AudealizeAudioProcessor& p, json descriptors);
        ~WordMap();
        
        //==========================================================
        // inherited from JUCE::Component
        void paint (Graphics& g) override;
        void resized() override;
        void mouseMove (const MouseEvent& e) override;
        void mouseEnter (const MouseEvent& e) override;
        void mouseExit (const MouseEvent& e) override;
        void mouseDown (const MouseEvent& e) override;
        void mouseDrag (const MouseEvent& e) override;
        //==========================================================

        
        /**
         *  Enable/disable a language to be plotted on the map
         *
         *  @param language
         *  @param enabled  true if language should be plotted
         */
        void toggleLanguage(string language, bool enabled);
        
        /**
         *  Search the map for a descriptor, and select it if it is present
         *
         *  @param text the descriptor to be searched for
         *
         *  @return true if descriptor is in map
         */
        bool searchMapAndSelect(String text);
        
        /**
         *  Inherited from JUCE::Timer
         */
        void timerCallback() override;
        
        /**
         *  Set the minimum font size for the map
         */
        void setMinFontSize(int fontSize);
        
        /**
         *  Sets the size of the info text strings displayed at the bottom of the map
         */
        void setInfoTextSize(int fontSize){
            infotext_size = fontSize;
        }
        
        /**
         *  @return a vector of all the words in the map
         */
        vector<String> getWords(){
            return words;
        }
        
    private:
        AudealizeAudioProcessor& processor; // the main plugin audio processor
        
        json json_dict; // the original dictionary of descriptors and their associated languages, agreement values, settings
        
        json word_dict; // keys: the descriptors being plotted. values: their indices in vectors words, points, params, colours
        
        json languages; // keys: the languages of the descriptors. values: bools for whether or not a language will be plotted
                
        Point<float> hover_position, circle_position; // positions of the hover and selection circles
        
        vector<String> words; // the descriptors to be plotted on the map
        
        vector<Point<float>> points; // the points at which the descriptors will be plotted
        
        vector<Point<float>> excluded_points; // the points corresponding to descriptors in the that will not be plotted
        
        vector<vector<float>> params; // the settings associated with the descriptors being plotted
        
        vector<int> font_sizes; // the font sizes of the descriptors being plotted
        
        vector<int> nums; // the number of occurrences of the descriptors
        
        vector<Colour> colors; // the colors of the descriptors being plotted
        
        float min_variance, max_variance, variance_thresh;
        
        int center_index; // index of the descriptor currently selected in the map
        
        int word_count; // total number of words in the map
        
        int base_font_size = 12; // smallest font size of descriptors on the map
        
        int infotext_size; // font size for the info text displayed at the bottom of the map
        
        bool init_map; // true if the map is still in its initial state (has not yet been clicked yet)
        
        bool has_been_hovered; // true if the map has been moused over
        
        bool isdirty; // true if component needs to be redrawn
        
        bool has_searchbar; // true if a searchbar has been attached
        
        NormalisableRange<int> alpha_range; // for converting between alpha values in range [0,1] (float) and [0,255] (int)
        
        //=====================================================================
        // Constants
        
        const int pad = 2; // amount of padding between mapped descriptors
        const int unhighlighted_alpha_value = 0.8f * 255; // alpha value of unhighlighted descriptors
        const int hover_alpha_value = 0.15f * 255; // alpha value of descriptors within hover radius but not selected
        
        //=====================================================================
        
        
        //=====================================================================
        // Private helper functions
        
        /**
         *  fills vectors words, points, excluded_points, params, font_sizes, colors based on selected languages
         */
        void loadPoints();
        
        /**
         *  Checks if Point<float> point will overlap any point in vector plotted
         *
         *  @param point   a point to be plotted
         *  @param plotted a vector of Point<float>s that have already been plotted
         *  @param dist    the distance threshold for what will be considered a collision
         *
         *  @return true if there is a collision
         */
        bool check_for_collision(Point<float> point, vector<Point<float>> plotted, float dist); // checks for collision between
        
        /**
         *  Checks if a point is within a given radius of another point
         *
         *  @param point       the point that will be checked to see if it is within the radius
         *  @param centerpoint the centerpoint of the radius
         *  @param radius      the radius
         *
         *  @return true if point is within radius
         */
        bool inRadius(Point<float> point , Point<float> centerpoint, float radius);
        
        /**
         *  Plots a word on the map
         *
         *  @param word      the word to be plotted
         *  @param color     the color of the word
         *  @param font_size the font size of the word
         *  @param point     the point at which the word will be plotted
         *  @param g         a JUCE::Graphics object
         */
        void plot_word(String word, Colour color, int font_size, Point<float> point, Graphics& g);
        
        /**
         *  Finds the index of the descriptor in the map that is closest to a given point
         *
         *  @param point
         *
         *  @return the index of the descriptor in the words, params, points, colors vectors
         */
        int find_closest_word_in_map(Point<float> point);
        
        /**
         *  Calculates the distance between two points
         *
         *  @param point1
         *  @param point2
         *
         *  @return the distance between the points
         */
        float calc_distance(Point<float> point1, Point<float> point2, Point<float> slack = Point<float>(1,1));
        
        /**
         *  Normalizes the x and y coordinates of points in vector WordMap::points
         */
        void normalizePoints();
        
        /**
         *  Selects a word in the map. Moves circle to word's position and sends the settings to the audio processor
         *
         *  @param word the word that has been selected
         */
        void wordSelected (String word);
        
        /**
         *  Set the component dirty if it needs to be redrawn
         *
         *  @param dirty 
         */
        void setDirty(bool dirty = true);
        
        /**
         *  Comparison functions used when normalizing a vector<Point<float>>
         *
         */
        static bool compareX(Point<float> p1, Point<float> p2);
        static bool compareY(Point<float> p1, Point<float> p2);
        
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WordMap)
    };
}
#endif
