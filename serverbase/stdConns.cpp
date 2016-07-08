/**
 * @file stdConns.cpp
 * @brief Standard connection types (flow,int,float)
 *
 */

#include "stdConns.h"

FlowCon *tFlow;
FloatCon *tFloat;
IntCon *tInt;

void regStdCons(){
    tFloat = new FloatCon();
    tFlow = new FlowCon();
    tInt = new IntCon();
}
