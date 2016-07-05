//
//  CParamSmooth.h
//
//  Based on CParamSmooth by alexirae@gmail.com from the musicdsp.org archives
//

#ifndef CParamSmooth_h
#define CParamSmooth_h


#define c_twoPi 6.283185307179586476925286766559f

class CParamSmooth
{
public:
    CParamSmooth(){
        init(5.0, 44100);
    }
    
    CParamSmooth(float smoothingTimeInMs, float sampleRate){
        init(smoothingTimeInMs, sampleRate);
    }

    ~CParamSmooth(){};

    void init(float smoothingTimeInMs, float sampleRate){
        a = exp(-c_twoPi / (smoothingTimeInMs * 0.001f * sampleRate));
        b = 1.0f - a;
        z = 0.0f;
        dirty = false;
    }
    
    double process(float in){
        z = (in * b) + (z * a);
        
        float diff = fabs(z - in);
        if (diff < in * .0001)
            dirty = false;
        else
            dirty = true;
        
        return z;
    }
    
    bool isDirty(){
        return dirty;
    }

private:
    float a, b, z;
    bool dirty;
};

#endif /* CParamSmooth_hpp */
