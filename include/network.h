#ifndef NETWORK_H
#define NETWORK_H

#include "darknet.h"

network make_network(int n);

void forward_network(network *netp);
void backward_network(network *netp);
void update_network(network *netp);

#endif