#pragma once 

#include "gurobi_c++.h"

class CustomCallback : public GRBCallback {

protected:

    void callback();

};