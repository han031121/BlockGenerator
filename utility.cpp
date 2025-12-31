#include "blockGenerator.h"

void blockData::printData() {
    int tmp[MAX_SIZE][MAX_SIZE] = {0};

    for(Block b : data)
        tmp[b.first.first][b.first.second] = b.second;

    std::cout << "current block_count : " << block_count << "\n";

    for(int i = MID - max_r; i <= MID + max_r; i++) {
        for(int j = MID - max_c; j <= MID + max_c; j++)
            std::cout << tmp[i][j] << " ";
        std::cout << "\n";
    }
}