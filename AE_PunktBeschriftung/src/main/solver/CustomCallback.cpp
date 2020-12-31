
#include <iostream>
#include <solver/CustomCallback.hpp>

void CustomCallback::callback() {
    std::cout << "Callback of Type: " << where << std::endl;
    if (where == GRB_CB_MIPNODE) {
        std::cout << "Calling Callback" << std::endl;
    }
}
