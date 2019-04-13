/**
 * @file chromosome.hpp
 * @author Haydn Jones, Benjamin Mastripolito
 * @brief Holds chromosome function defs and class
 * @date 2018-12-06
 */
#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include <stdlib.h>
#include <defs.hpp>
#include <vector>

class Chromosome {
    public:
    std::vector<float> input_adj;                 // Adjacency matrix describing input layer to first hidden layer
    std::vector<std::vector<float>> hiddenLayers; // Adjacency matrix describing the hidden layers
    std::vector<float> out_adj;                   // Adjacency matrix describing last hidden layer to the output nodes
    std::vector<float> input_tiles;               // Buffer for input to the network
    std::vector<float> node_outputs;              // Buffer for outputs of the network
    
    // Sizes are number of elements, not bytes
    size_t input_adj_size;
    size_t hidden_adj_size;
    size_t out_adj_size;

    int npl; // Nodes in each hidden layer
    int in_w; // Width of input rectangle around player
    int in_h; // Height of input rectangle around player
    int hlc;  // Number of hidden layers

    Chromosome(Params&);
    
    Chromosome(const char*);
    void generate(unsigned int);
    void print();
};

void write_out_chromosome(char *fname, Chromosome& chrom, unsigned int level_seed);
unsigned int extract_from_file(const char *fname, Chromosome *chrom);
unsigned int getStatsFromFile(const char *fname, Params& params);

/*

All matrices in the chromosome are flattened, 2D, row-major matrices.

INPUT ADJACENCY MATRIX
The input adjacency matrix is of size (NPL, IN_H * IN_W) describing the weights connecting the 
input nodes to the first hidden layer. The adjacency matrix is transposed to make it 
cache-friendly. Rather than each row describing the connections of a given input tile, it
describes the connections to a given node in the hidden layer.

HIDDEN ADJACENCY MATRIX
The next (HLC - 1) chunks will be adjacency matrices of size (NPL, NPL) describing weights from
the previous hidden layer to the current. Once again, this is logically transposed to be cache-friendly.
Each row represents a node and the columns are connections to it.

OUTPUT ADJACENCY MATRIX
The final chunk will be an adjacency matrix of size (NPL, BUTTON_COUNT) describing the weights
between the final hidden layer and the output layer.Same format as other adjacency matrices.
Note on adjacency matrices:

*/

#endif
