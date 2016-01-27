//
//  node.h
//  
//
//  Created by Ah on 7/19/15.
//
//

#ifndef _node_h
#define _node_h
extern const short pieceWeight[48];
class mov
{
public:
    enum
    {
        EMPTY = 0,
        OCCUPIED = 1
    };
    short from;
    short to;
    short capture;
    mov(short startPos, short endPos, short capture)
    :capture(capture), from(startPos), to(endPos){}
    bool operator> (const mov& mv) const
    {
        if(pieceWeight[this->capture]>pieceWeight[mv.capture])
            return true;
        return false;
    }

};

#endif
