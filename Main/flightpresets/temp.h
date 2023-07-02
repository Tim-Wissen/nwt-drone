#ifndef flightpresets_h
#define flightpresets_h

#include <Arduino.h>
    public:
    
    flightpresets_h();

    flightpresets_h::flightpresets_h(){
        int fl;
        int fr;
        int bl;
        int br;
    }
    
    void ff(){}                 //forward                 
    void bb(){}                 //backwards
    void ll(){}                 //left
    void rr(){}                 //right

    void fl(){}                 //forward-left
    void fr(){}                 //forward-right
    void bl(){}                 //backwards-left
    void br(){}                 //backwards-right

    void uu(){}                 //up
    void dd(){}                 //down
    
    void uff(){}                    //up-forward
    void ubb(){}                    //up-backwards
    void ull(){}                    //up-left
    void urr(){}                    //up-right

    void dff(){}                    //down-forward
    void dbb(){}                    //down-backwards
    void dll(){}                    //down-left
    void drr(){}                    //down-right
    
    void ufl(){}                    //up-forward-left
    void ufr(){}                    //up-forward-right
    void ubl(){}                    //up-backwards-left
    void ubr(){}                    //up-backwards-right

    void dfl(){}                    //down-forward-left
    void dfr(){}                    //down-forward-right
    void dbl(){}                    //down-backwards-left
    void dbr(){}                    //down-backwards-right

#endif