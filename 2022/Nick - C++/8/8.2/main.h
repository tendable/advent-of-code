#pragma once
#include <string>
#include <vector>

typedef int (*ViewingDistanceFunction) (int y, int x, std::vector< std::vector<int> > grid);

int scoreForTree(int y, int x, std::vector< std::vector<int> > grid);
int topViewingDistance(int y, int x, std::vector< std::vector<int> > grid);
int rightViewingDistance(int y, int x, std::vector< std::vector<int> > grid);
int bottomViewingDistance(int y, int x, std::vector< std::vector<int> > grid);
int leftViewingDistance(int y, int x, std::vector< std::vector<int> > grid);
