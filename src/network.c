#include "network.h"

network make_network(int n){
    network net = {0};
    net.layers = (layer*)calloc(n, sizeof(layer));
    return net;
}