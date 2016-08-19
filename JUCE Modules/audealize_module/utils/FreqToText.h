//
//  FreqToText.h
//
//  A function for nicely formatting frequency values for display
//  ex: freqToText(7531)  => "7.53 kHz"
//      freqToText(13463) => "13.4 kHz"

#ifndef FreqToText_h
#define FreqToText_h

static String freqToText(float freq){
    std::stringstream ss;
    ss << (int)freq;
    std::string val = ss.str();
    std::string out;
    if(freq>=1000 && freq < 10000){
        out = val.substr(0,1) + "." + val.substr(1,2) + " kHz";
    }
    else if(freq>=10000){
        out = val.substr(0,2) + "." + val.substr(2,1) + " kHz";
    }
    else{
        out = val + " Hz";
    }
    
    return String ( out );
}

#endif /* FreqToText_h */
