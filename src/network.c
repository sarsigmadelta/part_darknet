#include "network.h"

network make_network(int n){
    network net = {0};
    net.layers = (layer*)calloc(n, sizeof(layer));
    net.n = n;
    return net;
}

void forward_network(network *netp){
    network net = *netp;
    int n = net.n;
    int i;
    for(i=0; i<n; ++i){
        layer l = net.layers[i];
        l.forward_cpu(l, net);
        net.input = l.output;
    }
}

void backward_network(network *netp){
    network* net = netp;
    int n = net->n;
    int i;
    for(i=n-1; i>0; --i){
        layer l = net->layers[i];
        layer prev = net->layers[i-1];
        net->input = prev.output;
        net->delta = prev.delta;
        l.backward_cpu(l, *net);
    }
}