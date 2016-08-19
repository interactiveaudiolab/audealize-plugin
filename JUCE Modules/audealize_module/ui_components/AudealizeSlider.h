//
//  AudealizeSlider.h
//
//  A slider class with settable text-to-value and value-to-text functions
//

#ifndef AudealizeSlider_h
#define AudealizeSlider_h

namespace Audealize {
    class AudealizeSlider : public Slider {
    public:
        AudealizeSlider() {            
            valueToTextFunction = NULL;
            
            textToValueFunction = [](String s) { return s.getFloatValue(); };

        }
        
        ~AudealizeSlider() {}
        
        String getTextFromValue(double value) override {
            if (valueToTextFunction == NULL){  // default behavior
                if (getNumDecimalPlacesToDisplay() > 0) {
                    return String (value, getNumDecimalPlacesToDisplay()) + getTextValueSuffix();
                }
                else {
                    return String (roundToInt (value)) + getTextValueSuffix();
                }
            }
            
            return valueToTextFunction (value) + getTextValueSuffix();
        }
        
        double getValueFromText(const juce::String &text) override {
            String t (text.trimStart());
            
            if (t.endsWith (getTextValueSuffix()))
                t = t.substring (0, t.length() - getTextValueSuffix().length());
                
            while (t.startsWithChar ('+'))
                t = t.substring (1).trimStart();
                    
            t = t.initialSectionContainingOnly ("0123456789.,-");

            return textToValueFunction (t);
        }
        
        void setValueToTextFunction (std::function<String (float)> f){
            valueToTextFunction = f;
        }
        
        void setTextToValueFunction (std::function<float (String)> f){
            textToValueFunction = f;
        }
        

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR( AudealizeSlider );
        
        std::function<String (float)> valueToTextFunction;
        std::function<float (String)> textToValueFunction;

    };
}

#endif /* AudealizeSlider_h */
