#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <random>
#include <cmath>

#define MAX_SIZE 21
#define MID 10
#define DEFAULT_WEIGHT 1.0
#define DENSITY_COEFF 0.02
#define DEDUP_COEFF 0.02

typedef std::tuple<int,int,int> Tuple;
typedef std::pair<std::pair<int,int>, int> Block; //{position, height}
typedef std::vector<Block> BlockList;

using std::get;

class blockData {
    private:
        std::pair<int,int> block_count_pair; //max : max_r * max_c * max_h
        int block_count; //current block_count : randomly decided in block_count_pair
        int max_r, max_c; //max : MAX_SIZE / 2
        int max_h; //max : MAX_SIZE - 1
        double density_var = 0;
        double dedup_var = 0;

        int biggest_r = 0, biggest_c = 0, biggest_h = 0;
        int smallest_r = MAX_SIZE, smallest_c = MAX_SIZE;
        int size_r = 0, size_c = 0, size_h = 0;
        
        bool tempData[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {0};
        int created_count[MAX_SIZE][MAX_SIZE][MAX_SIZE] = {0};
        BlockList data = {};

        bool checkCreatable(int r, int c, int h); //check invisibility and max size limit
        double setWeight(int r, int c, int h); //calculate weight of specific position

        void init(); //initialize data
        void convertBlockData(); //create blockData based on tempData
        void measureSize(Tuple t); //measure current size

    public:
        blockData(int _bc1, int _bc2, int _max_r, int _max_c, int _max_h, double _den, double _dedup)
            : max_r(_max_r), max_c(_max_c), max_h(_max_h), density_var(_den), dedup_var(_dedup) {
                block_count_pair = {std::min(_bc1, _bc2), std::max(_bc1, _bc2)};
                
                if(std::max(_bc1, _bc2) > max_r * max_c * max_h || std::min(_bc1, _bc2) < 1)
                    throw std::length_error("invalid block_count");
                if (_max_r > MAX_SIZE/2 || _max_c > MAX_SIZE/2 || _max_h > MAX_SIZE-1 ||
                    _max_r < 1 || _max_c < 1 || _max_h < 1)
                    throw std::length_error("invalid max size");
            }

        void generateBlock(); //make new Block data
        
        const BlockList& getData() const { return data; } //get current Block data

        void printData();
        void printStatus();
};