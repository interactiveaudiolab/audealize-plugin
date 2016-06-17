/*
 A selection of functions ported to c++ from primefactors.js by Alexei Kourbatov, www.JavaScripter.net
 */

#ifndef PrimeFactors_h
#define PrimeFactors_h

static float leastFactor(int n){
    if (n == NAN) return NAN;
    if (n == 0) return 0;
    if (n % 1 || n * n < 2) return 1;
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    if (n % 5 == 0) return 5;
    if (n % 7 == 0) return 7;
    float m = sqrt(n);
    for (int i = 11; i <= m; i += 210) {
        if (n%i && n%(i+2) && n%(i+6) && n%(i+8)&& n%(i+12)&& n%(i+18)&& n%(i+20)&& n%(i+26)
            && n%(i+30) && n%(i+32) && n%(i+36) && n%(i+42) && n%(i+48) && n%(i+50) && n%(i+56)
            && n%(i+60) && n%(i+62) && n%(i+68) && n%(i+72) && n%(i+78) && n%(i+86)
            && n%(i+90) && n%(i+92) && n%(i+96) && n%(i+98) && n%(i+102)&& n%(i+110)&& n%(i+116)
            && n%(i+120)&& n%(i+126)&& n%(i+128)&& n%(i+132)&& n%(i+138)&& n%(i+140)&& n%(i+146)
            && n%(i+152)&& n%(i+156)&& n%(i+158)&& n%(i+162)&& n%(i+168)&& n%(i+170)&& n%(i+176)
            && n%(i+180)&& n%(i+182)&& n%(i+186)&& n%(i+188)&& n%(i+198)&& n%(i+200)
            ) continue;
        for (int j=0;j<210;j+=2) {if (n%(i+j)==0) return i+j; }
    }
    return n;
}

static bool isPrime(int n){
    if (n % 1 != 0 || n < 2)
        return false;
    if (n == leastFactor(n))
        return true;
    return false;
}

static float prevPrime(int n){
    if (n < 2) return 2;
    n = floorf(n);
    
    for (int i = n + n % 2 - 1; i > 0; i -=2){
        if (isPrime(i))
            return i;
    }
    return NAN;
}

#endif /* PrimeFactors_h */
