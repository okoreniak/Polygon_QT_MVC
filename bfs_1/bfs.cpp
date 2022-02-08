// bfs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//#include "pch.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

std::ifstream fin("a.txt");
std::ofstream fout("a.out");

int main()
{   
    //fout << "Hello World!\n"; 

    int n, m;
    int a, b;
    a = b = m = n = 0;
    fin >> n >> m;
    std::vector <int> samp;
    std::vector< std::vector<int> > conn(n + 1, samp);
    // load adjacency matrix
    for (int i = 0; i < m; ++i)
    {
        fin >> a >> b;
        conn[a].push_back(b);
        conn[b].push_back(a);
    }
    std::vector<bool> visited(n + 1);// 11]; // n+1
    for (int i = 0; i < n + 1; ++i)
    {
        visited[i] = false;
    }
    std::queue <int> level;
    level.push(1);
    visited[1] = true;
    int si = 0;
    int le = 0;
    while (!level.empty())
    {
        fout << "LEVEL :" << le << std::endl;
        si = level.size();
        while (si--)
        {
            int x = level.front();
            level.pop();
            fout << x << std::endl;
            for (int j = 0; j < conn[x].size(); ++j)
            {
                if (!visited[conn[x][j]])
                {
                    visited[conn[x][j]] = true;
                    level.push(conn[x][j]);
                }
            }
        }
        le++;
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
