#ifndef flightpresets_h
#define flightpresets_h

#include <Arduino.h>
    flightpresets_h();
        unsigned int speed;
        
        double int fl;
        double int fr;
        double int bl;
        double int br;

        bool clockwise;
    
    void ff(){
        bl = br = speed;
        fl = fr = speed * 3/4;
    }                                  
    void bb(){
        fl = fr = speed;
        bl = br = speed * 3/4;
    }                 
    void ll(){
        fr = br = speed;
        bl = br = speed * 3/4;
    }                 
    void rr(){
        fl = bl = speed;
        fr = br = speed * 3/4;
    }

    void fl(){
        br = speed;
        fr = bl = speed * 3/4;
        fl = speed * 2/4;
    }
    void fr(){
        bl = speed;
        fl = br = speed * 3/4;
        fr = speed * 2/4;
    }
    void bl(){
        fr = speed;
        fl = br = speed * 3/4;
        bl = speed * 2/4;
    }
    void br(){
        fl = speed;
        fr = bl = speed * 3/4;
        br = speed * 2/4;
    }

    void uu(){
        fl = fr = bl = br = speed;
    }
    void dd(){
        fl = fr = bl = br = speed;
    }
    
    void uff(){
        bl = br = speed;
        fl = fr = speed * 3/4;
    }
    void ubb(){
        fl = fr = speed;
        bl = br = speed * 3/4;
    }
    void ull(){
        fr = br = speed;
        fl = bl = speed * 3/4;
    }
    void urr(){
        fl = bl = speed;
        fr = br = speed * 3/4;
    }

    void dff(){
        bl = br = speed * 2/4;
        fl = fr = speed * 1/4;
    }
    void dbb(){
        fl = fr = speed * 2/4;
        bl = br = speed * 1/4;
    }
    void dll(){
        fr = br = speed * 2/4;
        fl = bl = speed * 1/4;
    }
    void drr(){
        fl = bl = speed * 2/4;
        fr = br = speed * 1/4;
    }

    void ufl(){
        fr = bl = br = speed;
        fl = speed * 3/4;
    }
    void ufr(){
        fl = bl = br = speed;
        fr = speed * 3/4
    }
    void ubl(){
        fl = fr = br = speed;
        bl = speed * 3/4;
    }
    void ubr(){
        fl = fr = bl = speed;
        br = speed * 3/4;
    }

    void dfl(){
        fr = bl = br = speed * 2/4;
        fl = speed * 1/4;
    }
    void dfr(){
        fl = bl = br = speed * 2/4;
        fr = speed * 1/4
    }
    void dbl(){
        fl = fr = br = speed * 2/4;
        bl = speed * 1/4;
    }
    void dbr(){
        fl = fr = bl = speed * 2/4;
        br = speed * 1/4;
    }

#endif