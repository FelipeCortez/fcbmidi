//
//  Footswitch.h
//  fcbmidi
//
//  Created by Felipe Cortez on 25/10/15.
//  Copyright (c) 2015 Felipe Cortez. All rights reserved.
//

#ifndef fcbmidi_Footswitch_h
#define fcbmidi_Footswitch_h

class Footswitch {
    public:
    bool state;
    bool invert;
    unsigned char behaviour;
    
    Footswitch() {
        state = false;
        invert = false;
        behaviour = App::LATCH;
    }
};

#endif
