//
//  AudealizeSlider.h
//
//  A slider class with settable text-to-value and value-to-text functions
//

#ifndef AudealizeSlider_h
#define AudealizeSlider_h

namespace Audealize
{
    class AudealizeSlider : public Slider {
    public:
        AudealizeSlider()
        {
            valueToTextFunction = NULL;
            
            textToValueFunction = [](String s) { return s.getFloatValue(); };
        }
        
        ~AudealizeSlider() {}
        
        /**
         *  Returns a String representation of the slider's value. Used when displaying value in a textbox
         *  Inherited from juce::Slider
         *
         *  @param value a double
         *
         *  @return a String reprsentation of the value
         */
        String getTextFromValue(double value) override
        {
            if (valueToTextFunction == NULL)  // if no custom function defined, use default behavior from juce::Slider
            {
                if (getNumDecimalPlacesToDisplay() > 0)
                {
                    return String (value, getNumDecimalPlacesToDisplay()) + getTextValueSuffix();
                }
                else
                {
                    return String (roundToInt (value)) + getTextValueSuffix();
                }
                
            }
            
            return valueToTextFunction (value) + getTextValueSuffix();
        }
        
        /**
         *  Parses a string containing the value of a slider and returns a double representation of that value
         *  Used when setting slider value through a text box.
         *  Inherited from juce::Slider
         *
         *  @param text THe String to be parsed
         *
         *  @return The value as a double
         */
        double getValueFromText(const juce::String &text) override
        {
            String t (text.trimStart()); // remove whitespace at beginning of string
            
            if (t.endsWith (getTextValueSuffix())) // remove suffix if present (usually a unit label)
                t = t.substring (0, t.length() - getTextValueSuffix().length());
                
            while (t.startsWithChar ('+')) // disregard '+' at beginning of string
                t = t.substring (1).trimStart();
                    
            t = t.initialSectionContainingOnly ("0123456789.,-");

            return textToValueFunction (t);
        }
        
        /**
         *  Set a custom value to text function for the slider
         *
         *  @param f  a std::function<String (float)>
         */
        void setValueToTextFunction (std::function<String (float)> f)
        {
            valueToTextFunction = f;
        }
        
        /**
         *  Set a custom text to value function for the slider
         *
         *  @param f  a std::function<float (String)>
         */
        void setTextToValueFunction (std::function<float (String)> f)
        {
            textToValueFunction = f;
        }
        

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( AudealizeSlider );
        
        std::function<String (float)> valueToTextFunction;
        std::function<float (String)> textToValueFunction;

    };
}

#endif /* AudealizeSlider_h */
