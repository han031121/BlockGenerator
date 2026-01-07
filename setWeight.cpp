#include "blockGenerator.h"

bool blockData::checkCreatable(int r, int c, int h) {
    if(size_r >= max_r && (r > biggest_r || r < smallest_r))
        return false;
    if(size_c >= max_c && (c > biggest_c || c < smallest_c))
        return false;
    if(size_h >= max_h && h > biggest_h)
        return false;

    if(h > 1 && tempData[r][c][h-1] == false)
        return false;

    //TODO : uncountable block rule implement
    
        
    return true;
}

double blockData::setWeight(int r, int c, int h) {
    double mul = 1.0;
    double possibility = DEFAULT_WEIGHT;

    if(!checkCreatable(r,c,h))
        return 0.0;

    int dist = abs(r - MID) + abs(c - MID);
    mul *= exp(-DENSITY_COEFF * (double)dist * density_var);

    mul *= exp(-DEDUP_COEFF * (double)created_count[r][c][h] * dedup_var);

    possibility *= mul;
    //std::cout << "setWeight - position : " << r << " " << c << " " << h << "\n";
    //std::cout << "setWeight - possibility : " << possibility << "\n";
    return possibility;
}