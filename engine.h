#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <set>

using namespace std;

int zeros(int a);
void merge(set<int> &a, set<int> &b);
void set_and(set<int> &a, set<int> &b);
int set_minus(set<int> &a, set<int> &b);
int contains(vector<int> &a, int b);
class sudoku_cl
{
    private:
        int n;
        int difficulty;
        int number_of_hints;
        unsigned int size;
        int width;
        void swap_columns_small();
        void swap_rows_small();
        void swap_columns_area();
        void swap_rows_area();
        void transpose();
        int last_hero_place();
        vector<vector<set<int> > > possible;
        vector<vector<int> > filled_board;
        vector<vector<int> > temp_board;
        int naked();
        int hidden_pairs();
        void remove_possibilities(int r, int c, vector < vector <int> > cur_board);
        int q_naked(int q, int type, int i);
        int r_naked(int r, int type, int i);
        int c_naked(int c, int type, int i);
        int q_hidden(int q, int number);
        int r_hidden(int r, int number);
        int c_hidden(int c, int number);
        set <int> set_naked;
        set <int> set_possible;
        vector <int> vector_i;
    public:
        sudoku_cl(int inputed_n, int dif);
        ~sudoku_cl();
        bool is_solved();
        vector<vector<int> > change;
        vector<vector<int> > board;
        void gen_board();
        int solve();

};