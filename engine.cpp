#include "engine.h"

int zeros(int a)
{
    int k = 0;
    for (; a > 0; k++)
        a /= 10;
    return k;
}
void merge(set<int> &a, set<int> &b)
{
    for (int i : b)
        a.insert(i);
}
void set_and(set<int> &a, set<int> &b)
{
    set <int> c(a);
    for (int i: c)
        if (b.find(i) == b.end())
            a.erase(i);
}
int set_minus(set<int> &a, set<int> &b)
{
    int res = 0;
    for(int i: b)
        if (a.find(i) != a.end())
            a.erase(i), res++;
    return res;
}
int contains(vector<int> &a, int b)
{
    for (int i: a)
        if (i == b) return 1;
    return 0;
}
sudoku_cl::sudoku_cl(int inputed_n, int dif)
{
    n = inputed_n;
    size = inputed_n*inputed_n;
    width = zeros(size);
    difficulty = dif;
    temp_board.reserve(size * size);
    filled_board.reserve(size * size);
    board.push_back(vector<int>());
    change.push_back(vector<int>());
    possible.push_back( vector< set<int> >());
    for(int i = 1; i <= size; i++)
    {
	    board.push_back(vector<int>());
	    change.push_back(vector<int>());
        possible.push_back( vector< set<int> >());
	    board[i].push_back(0), change[i].push_back(0), possible[i].push_back(set <int>());
	    for(int j = 1; j <= size; j++)
	    {
	        board[i].push_back(0), change[i].push_back(0), possible[i].push_back(set <int>());
            for(int c = 0; c <= size; c++)
                possible[i][j].insert(c);
	    }
    }
    gen_board();
}
sudoku_cl::~sudoku_cl()
{
    set_naked.clear();
    vector_i.clear();
    possible.clear();
    change.clear();
    temp_board.clear();
    board.clear();
    filled_board.clear();
}
void sudoku_cl::gen_board()
{
    random_device rd;
    mt19937 mersenne(rd());
    for(int i = 1; i <= size; i++)
    {
	    for (int j = 1; j <= size; j++)
	    {
	        board[i][j] = (((i-1)*n + (i-1)/n + (j-1)) % size + 1);
	    }
    }
    for(int i = 0; i < 1000; i++)
    {
        /*int action = rand() % 5;
        if (action == 0) transpose();
        if (action == 1) swap_columns_area();
        if (action == 2) swap_columns_small();
        if (action == 3) swap_rows_area();
        if (action == 4) swap_rows_small();*/
        swap_columns_small();
        swap_rows_small();
        swap_columns_small();
        swap_rows_small();
        swap_columns_small();
        swap_rows_small();
        swap_columns_small();
        swap_rows_small();
        swap_columns_small();
        swap_rows_small();
        swap_columns_small();
        swap_rows_small();
        swap_columns_small();
        swap_rows_small();
        swap_columns_small();
        swap_rows_small();
        swap_columns_small();
        swap_rows_small();
        swap_columns_area();
        swap_columns_small();
        swap_rows_small();
        swap_rows_area();
        swap_columns_small();
        swap_rows_small();
        swap_columns_area();
        swap_columns_small();
        swap_rows_small();
        swap_rows_area();
        swap_columns_small();
        swap_rows_small();
        swap_columns_area();
        swap_columns_small();
        swap_rows_small();
        swap_rows_area();
        swap_columns_small();
        swap_rows_small();
        transpose();
    }
    filled_board.assign(board.begin(), board.end());
    int i = size*size;
    int number_of_hints;
    switch (difficulty)
    {
    case 1:
        number_of_hints = i * (n*10 + 13) / 100;
        break;
    case 2:
        number_of_hints = i * (n*10 + 7) / 100;
        break;
    case 3:
        number_of_hints = i * (n*10 + 1) / 100;
        break;
    default:
        break;
    }
    int k;
    for(k = 0; k < 100 && i >= number_of_hints;)
    {
        int q = mersenne() % size + 1;
        int field = mersenne() % size + 1;
        int r = (q - 1) / n * n + (field - 1) / n + 1, c = (q - 1) % n * n + (field - 1) % n + 1;
        if (board[r][c])
        {
            int temp = board[r][c];
            board[r][c] = 0, change[r][c] = 1, i--;
            if (!solve()) 
            {
                board[r][c] = temp;
                change[r][c] = 0;
                i++;
                k++;
            }
        }
        else k++;
    }
}
void sudoku_cl::transpose()
{
    vector< vector<int> > b;
    b.push_back(vector<int>());
    for(int i = 1; i<=size; i++)
    {
        b.push_back(vector<int>());
        b[i].push_back(0);
        for(int j = 1; j<=size; j++)
            b[i].push_back(board[j][i]);
    }
    for(int i = 1; i<=size; i++)
        for(int j = 1; j<=size; j++)
            board[i][j] = b[i][j];
}
void sudoku_cl::swap_rows_small()
{
    random_device rd;
    mt19937 mersenne(rd());
    int r = mersenne() % n + 1;
    int r1 = mersenne() % n + 1;
    int t = mersenne() % n;
    while (r == r1)  r1 = mersenne() % n + 1;
    r = r + t * n;
    r1 = r1 + t * n;
    for (int i = 1; i <= size; i++)
    {
        int a = board[r][i];
        board[r][i] = board[r1][i];
        board[r1][i] = a;
    }
}
void sudoku_cl::swap_columns_small()
{
    random_device rd;
    mt19937 mersenne(rd());
    int r = mersenne() % n + 1;
    int r1 = mersenne() % n + 1;
    int t = mersenne() % n;
    while (r == r1)  r1 = mersenne() % n + 1;
    r = r + t * n;
    r1 = r1 + t * n;
    for (int j = 1; j <= size; j++)
    {
        int a = board[j][r];
        board[j][r] = board[j][r1];
        board[j][r1] = a;
    }
}
void sudoku_cl::swap_rows_area()
{
    random_device rd;
    mt19937 mersenne(rd());
    int r = mersenne() % n;
    int r1 = mersenne() % n;
    while (r == r1)  r1 = mersenne() % n;
    r1 = r1 * n + 1;
    r = r * n + 1;
    for (int k = 0; k < n; k++)
    {
        for (int j = 1; j <= size; j++)
        {
            int a = board[r + k][j];
            board[r + k][j] = board[r1 + k][j];
            board[r1 + k][j] = a;
        }
    }
}
void sudoku_cl::swap_columns_area()
{
    random_device rd;
    mt19937 mersenne(rd());
    int r = mersenne() % n;
    int r1 = mersenne() % n;
    while (r == r1)  r1 = mersenne() % n;
    r1 = r1 * n + 1;
    r = r * n + 1;
    for (int k = 0; k < n; k++)
    {
	    for (int i = 1; i <= size; i++)
	    {
	        int a = board[i][r + k];
	        board[i][r + k] = board[i][r1 + k];
	        board[i][r1 + k] = a;
	    }
    }
}

int sudoku_cl::solve()
{
    for(int r = 1; r <= size; r++)
    {
        for(int c = 1; c <= size; c++)
        {
            for(int i = 1; i <= size; i++)
            {
                possible[r][c].insert(i);
            }
        }
    }
    for(int r = 1; r <= size; r++)
    {
        for(int c = 1; c <= size; c++)
        {
            if (board[r][c])
            {
                remove_possibilities(r, c, board);
            }
        }
    }
    int changed = 1;
    temp_board.assign(board.begin(), board.end());
    while (changed && (temp_board != filled_board))
    {
        changed = 0;
        changed |= last_hero_place();
        if (difficulty >= 2 && (temp_board != filled_board))
        {
            changed |= naked();
        }

        if (difficulty >= 3 && (temp_board != filled_board))
        {
            changed |= hidden_pairs();        
        }
    }
    if (temp_board == filled_board)
        return 1;
    else
        return 0;
}
int sudoku_cl::last_hero_place()
{
    char was_changed_at_all = 0;
    char was_changed = 1;
    while (was_changed)
    {
        was_changed = 0;
        //The only possible number in the field
        for(int r = 1; r <= size; r++)
        {
            for(int c = 1; c <= size; c++)
            {
                if (possible[r][c].size() == 1)
                {
                    temp_board[r][c] = * possible[r][c].begin();
                    remove_possibilities(r, c, temp_board);
                    was_changed |= 1;
                    was_changed_at_all |= 1;
                }
            }
        }
        //The only possible place in a row
        for(int c = 1; c <= size; c++)
        {
            for(int i = 1; i <= size; i++)
            {
                int k = 0;
                int only_i = 0;
                int pos_r, pos_c;
                for(int r = 1; r <= size; r++)
                {
                    if (temp_board[r][c] == i)
                    {
                        k = -1;
                        break;
                    }
                    if (possible[r][c].find(i) != possible[r][c].end())
                    {
                        k++;
                        if (k == 1)
                        {
                            int only_i = i;
                            pos_r = r, pos_c = c;
                        }
                        else 
                        {
                            k = -1;
                            break;
                        }
                    }
                }
                if (k == 1)
                {
                    temp_board[pos_r][pos_c] = only_i;
                    remove_possibilities(pos_r, pos_c, temp_board);
                    was_changed |= 1;
                    was_changed_at_all |= 1;
                }

            }
        }
        //The only possible in the column
        for(int r = 1; r <= size; r++)
        {
            for(int i = 1; i <= size; i++)
            {
                int k = 0;
                int only_i = 0;
                int pos_r = 0, pos_c = 0;
                for(int c = 1; c <= size; c++)
                {
                    if (temp_board[r][c] == i)
                    {
                        k = -1;
                        break;
                    }
                    if (possible[r][c].find(i) != possible[r][c].end())
                    {
                        k++;
                        if (k == 1)
                        {
                            only_i = i;
                            pos_r = r, pos_c = c;
                        }
                        else 
                        {
                            k = -1;
                            break;
                        }
                    }
                }
                if (k == 1)
                {
                    temp_board[pos_r][pos_c] = only_i;
                    remove_possibilities(pos_r, pos_c, temp_board);
                    was_changed |= 1;
                    was_changed_at_all |= 1;
                }

            }
        }
        //The only possible place in square
        for(int q = 1; q <= size; q++)
        {
            for(int i = 1; i <= size; i++)
            {
                int k = 0;
                int only_i = 0;
                int pos_r = 0, pos_c = 0;
                for(int r = 1; r <= n; r++)
                {
                    for(int c = 1; c <= n; c++)
                    {
                        if (temp_board[r][c] == i)
                        {
                            k = -1;
                            break;
                        }
                        if (possible[r][c].find(i) != possible[r][c].end())
                        {
                            k++;
                            if (k == 1)
                            {
                                only_i = i;
                                pos_r = r, pos_c = c;
                            }
                            else 
                            {
                                k = -1;
                                break;
                            }
                        }
                    }
                }
                if (k == 1)
                {
                    temp_board[pos_r][pos_c] = only_i;
                    remove_possibilities(pos_r, pos_c, temp_board);
                    was_changed = 1;
                    was_changed_at_all = 1;
                }

            }
        }
    }
    return was_changed_at_all;
}
int sudoku_cl::naked()
{
    char was_changed_at_all = 0;
    char was_changed = 1;
    char c;
    while (was_changed)
    {
        was_changed = 0;
        for (int type = 2; type <= max(n/2, 4); type++)
        {
            for(int q = 1; q <= size; q++)
            {
                for(int i = 1; i <= size - (type - 1); i++)
                {
                    was_changed |= q_naked(q, type, i);
                    was_changed |= r_naked(q, type, i);
                    was_changed |= c_naked(q, type, i);
                }
            }
        }
        was_changed_at_all |= was_changed;
    }
    return was_changed_at_all;
}
int sudoku_cl::hidden_pairs()
{
    char was_changed_at_all = 0;
    char was_changed = 1;
    while (was_changed)
    {
        was_changed = 0;
        for(int q = 1; q <= size; q++)
        {
            was_changed |= q_hidden(q);
            was_changed |= r_hidden(q);
            was_changed |= c_hidden(q);
        }
        was_changed_at_all |= was_changed;
    }
    return was_changed_at_all;
}
int sudoku_cl::q_naked(int q, int type, int i)
{
    char res = 0;
    int r = (q - 1) / n * n + (i - 1) / n + 1, c = (q - 1) % n * n + (i - 1) % n + 1;
    set<int> set_before;
    merge(set_before, set_naked);
    if (temp_board[r][c])
    {
        return 0;
    }
    else
    {
        vector_i.push_back(i);
        merge(set_naked, possible[r][c]);
    }
    
    int k = vector_i.size(), i_there = i;
    if (set_naked.size() > type)
    {
        set_and(set_naked, set_before);
        vector_i.pop_back();
        return 0;
    }
    else if (set_naked.size() == type && type == k)
    {
        for(int i_change = 1; i_change <= size; i_change++)
        {
            res = 0;
            if (!contains(vector_i, i_change))
            {
                int r_change = (q - 1) / n * n + (i_change - 1) / n + 1, c_change = (q - 1) % n * n + (i_change - 1) % n + 1;
                if (set_minus(possible[r_change][c_change], set_naked)) res = 1;
            }
        }
        vector_i.pop_back();
        set_and(set_naked, set_before);
        return res;
    }
    else if (type == k)
    {
        set_and(set_naked, set_before);
        vector_i.pop_back();
        return 0;
    }
    for(i++; i <= size - (type - k); i++)
    {
        if (q_naked(q, type, i))
        {
            vector_i.pop_back();
            set_and(set_naked, set_before);
            return 1;
        }
    }
    vector_i.pop_back();
    set_and(set_naked, set_before);
    return 0;
}
int sudoku_cl::r_naked(int r, int type, int c)
{
    int res = 0;
    set<int> set_before;
    merge(set_before, set_naked);
    if (temp_board[r][c])
    {
        return 0;
    }
    else
    {
        vector_i.push_back(c);
        merge(set_naked, possible[r][c]);
    }
    int k = vector_i.size(), c_there = c;
    if (set_naked.size() > type)
    {
        set_and(set_naked, set_before);
        vector_i.pop_back();
        return 0;
    }
    else if (set_naked.size() == type && type == k)
    {
        res = 0;
        for(int c_change = 1; c_change <= size; c_change++)
        {
            if (!contains(vector_i, c_change))
            {
                if (set_minus(possible[r][c_change], set_naked)) res = 1;
            }
        }
        vector_i.pop_back();
        set_and(set_naked, set_before);
        return res;
    }
    else if (type == k)
    {
        vector_i.pop_back();
        set_and(set_naked, set_before);
        return 0;
    }
    for(c++; c <= size - (type - k); c++)
    {
        if (r_naked(r, type, c))
        {
            vector_i.pop_back();
            set_and(set_naked, set_before);
            return 1;
        }
    }
    vector_i.pop_back();
    set_and(set_naked, set_before);
    return 0;
}
int sudoku_cl::c_naked(int c, int type, int r)
{
    int res;
    set<int> set_before;
    merge(set_before, set_naked);
    if (temp_board[r][c])
    {
        return 0;
    }
    else
    {
        vector_i.push_back(r);
        merge(set_naked, possible[r][c]);
    }
    int k = vector_i.size(), r_there = r;
    if (set_naked.size() > type)
    {
        set_and(set_naked, set_before);
        vector_i.pop_back();
        return 0;
    }
    else if (set_naked.size() == type && type == k)
    {
        for(int r_change = 1; r_change <= size; r_change++)
        {
            res = 0;
            if (!contains(vector_i, r_change))
            {
                if (set_minus(possible[r_change][c], set_naked)) res = 1;
            }
        }
        vector_i.pop_back();
        set_and(set_naked, set_before);
        return res;
    }
    else if (type == k)
    {
        vector_i.pop_back();
        set_and(set_naked, set_before);
        return 0;
    }
    for(r++; r <= size - (type - k); r++)
    {
        if (c_naked(c, type, r))
        {
            vector_i.pop_back();
            set_and(set_naked, set_before);
            return 1;
        }
    }
    vector_i.pop_back();
    set_and(set_naked, set_before);
    return 0;
}
int sudoku_cl::q_hidden(int q)
{
    int res = 0;
    vector<set<int> > number_possibilities;
    set<int> clear_set;
    for (int i = 0; i <= size ; i++)
    {
        number_possibilities.push_back(clear_set);
    }
    for (int i = 1; i <= size ; i++)
    {
        int r = (q - 1) / n * n + (i - 1) / n + 1, c = (q - 1) % n * n + (i - 1) % n + 1;
        if (!temp_board[r][c])
        {
            for (int number : possible[r][c])
            {
                number_possibilities[number].insert(i);
            }
        }
    }
    for(int number1 = 1; number1 <= size-1; number1++)
    {
        if (number_possibilities[number1].size())
        {
            set<int> set_n1;
            merge(set_n1, number_possibilities[number1]);
            for(int number2 = number1+1; number2 <= size; number2++)
            {
                if (number_possibilities[number2].size())
                {
                    merge(number_possibilities[number1], number_possibilities[number2]);
                    if (number_possibilities[number1].size() == 2)
                    {
                        for(int i1: number_possibilities[number1])
                        {
                            int r = (q - 1) / n * n + (i1 - 1) / n + 1, c = (q - 1) % n * n + (i1 - 1) % n + 1;
                            set<int> cop(possible[r][c]);
                            for(int number: cop)
                            {
                                if (number != number1 && number != number2)
                                {
                                    possible[r][c].erase(number);
                                    res |= 1;
                                }
                            }
                            cop.clear();
                            if (res)
                                goto exit;

                        }
                    }
                    if (n > 2)
                    {
                        set<int> set_n1n2;
                        merge(set_n1n2, number_possibilities[number1]);
                        for(int number3 = number2 + 1; number3 <= size; number3++)
                        {
                            if (number_possibilities[number3].size())
                            {
                                merge(number_possibilities[number1], number_possibilities[number3]);
                                if (number_possibilities[number1].size() == 3)
                                {
                                    for(int i2: number_possibilities[number1])
                                    {
                                        int r = (q - 1) / n * n + (i2 - 1) / n + 1, c = (q - 1) % n * n + (i2 - 1) % n + 1;
                                        set<int> cop(possible[r][c]);
                                        for(int number: cop)
                                        {
                                            if (number != number1 && number != number2 && number != number3)
                                            {
                                                possible[r][c].erase(number);
                                                res |= 1;
                                            }
                                        }
                                        cop.clear();
                                        if (res)
                                            goto exit;
                                    }
                                }
                                set<int> set_n1n2n3;
                                merge(set_n1n2n3, number_possibilities[number1]);
                                for (int number4 = number3 + 1; number4 <= size; number4++)
                                {
                                    if (number_possibilities[number4].size())
                                    {
                                        merge(number_possibilities[number1], number_possibilities[number4]);
                                        if (number_possibilities[number1].size() == 4)
                                        {
                                            for (int i3 : number_possibilities[number1])
                                            {
                                                int r = (q - 1) / n * n + (i3 - 1) / n + 1, c = (q - 1) % n * n + (i3 - 1) % n + 1;
                                                set<int> cop(possible[r][c]);
                                                for (int number : cop)
                                                {
                                                    if (number != number1 && number != number2 && number != number3 && number != number4)
                                                    {
                                                        possible[r][c].erase(number);
                                                        res |= 1;
                                                    }
                                                }
                                                cop.clear();
                                                if (res)
                                                    goto exit;
                                            }
                                        }
                                        merge(number_possibilities[number1], set_n1n2n3);
                                    }
                                }
                                if (set_n1n2n3.size())
                                {
                                    set_n1n2n3.clear();
                                }
                                merge(number_possibilities[number1], set_n1n2);
                            }
                        }
                        if (set_n1n2.size())
                        {
                            set_n1n2.clear();
                        }
                    }
                    merge(number_possibilities[number1], set_n1);
                }
            }
            if (set_n1.size())
            {
                set_n1.clear();
            }
        }
    }
    exit:
    return res;
}
int sudoku_cl::r_hidden(int r)
{
    int res = 0;
    vector<set<int> > number_possibilities;
    set<int> clear_set; 
    for (int i = 0; i <= size ; i++)
    {
        number_possibilities.push_back(clear_set);
    }
    for (int c = 1; c <= size ; c++)
    {
        if (!temp_board[r][c])
        {
            for (int number : possible[r][c])
            {
                number_possibilities[number].insert(c);
            }
        }
    }
    for(int number1 = 1; number1 <= size-1; number1++)
    {
        set<int> set_n1;
        merge(set_n1, number_possibilities[number1]);
        for(int number2 = number1+1; number2 <= size; number2++)
        {
            if (number_possibilities[number2].size())
            {
                merge(number_possibilities[number1], number_possibilities[number2]);
                if (number_possibilities[number1].size() == 2)
                {
                    for (int c1 : number_possibilities[number1])
                    {
                        set<int> cop(possible[r][c1]);
                        for (int number : cop)
                        {
                            if (number != number1 && number != number2)
                            {
                                possible[r][c1].erase(number);
                                res |= 1;
                            }
                        }
                        cop.clear();
                        if (res)
                            goto exit;
                    }
                }
                if (n > 2)
                {
                    set<int> set_n1n2;
                    merge(set_n1n2, number_possibilities[number1]);
                    for (int number3 = number2 + 1; number3 <= size; number3++)
                    {
                        if (number_possibilities[number3].size())
                        {
                            merge(number_possibilities[number1], number_possibilities[number3]);
                            if (number_possibilities[number1].size() == 3)
                            {
                                for (int c2 : number_possibilities[number1])
                                {
                                    set<int> cop(possible[r][c2]);
                                    for (int number : cop)
                                    {
                                        if (number != number1 && number != number2 && number != number3)
                                        {
                                            possible[r][c2].erase(number);
                                            res |= 1;
                                        }
                                    }
                                    cop.clear();
                                    if (res)
                                        goto exit;
                                }
                            }
                            set<int> set_n1n2n3;
                            merge(set_n1n2n3, number_possibilities[number1]);
                            for (int number4 = number3 + 1; number4 <= size; number4++)
                            {
                                if (number_possibilities[number4].size())
                                {
                                    merge(number_possibilities[number1], number_possibilities[number4]);
                                    if (number_possibilities[number1].size() == 4)
                                    {
                                        for (int c3 : number_possibilities[number1])
                                        {
                                            set<int> cop(possible[r][c3]);
                                            for (int number : cop)
                                            {
                                                if (number != number1 && number != number2 && number != number3 && number != number4)
                                                {
                                                    possible[r][c3].erase(number);
                                                    res |= 1;
                                                }
                                            }
                                            cop.clear();
                                            if (res)
                                                goto exit;
                                        }
                                    }
                                    merge(number_possibilities[number1], set_n1n2n3);
                                }
                            }
                            if (set_n1n2n3.size())
                            {
                                set_n1n2n3.clear();
                            }
                            merge(number_possibilities[number1], set_n1n2);
                        }
                    }
                    if (set_n1n2.size())
                    {
                        set_n1n2.clear();
                    }
                }
                merge(number_possibilities[number1], set_n1);
            }
        }
        if (set_n1.size())
        {
            set_n1.clear();
        }
    }
    exit:
    for (int i = 1; i <= size; i++)
    {
        if (number_possibilities[i].size())
        {
            number_possibilities[i].clear();
        }
    }
    number_possibilities.clear();
    return res;
}
int sudoku_cl::c_hidden(int c)
{
    int res = 0;
    vector<set<int> > number_possibilities;
    set<int> clear_set; 
    for (int i = 0; i <= size ; i++)
    {
        number_possibilities.push_back(clear_set);
    }
    for (int r = 1; r <= size ; r++)
    {
        if (!temp_board[r][c])
        {
            for (int number : possible[r][c])
            {
                number_possibilities[number].insert(r);
            }
        }
    }
    for(int number1 = 1; number1 <= size-1; number1++)
    {
       set<int> set_n1;
        merge(set_n1, number_possibilities[number1]);
        for(int number2 = number1+1; number2 <= size; number2++)
        {
            merge(number_possibilities[number1], number_possibilities[number2]);
            if (number_possibilities[number1].size() == 2)
            {
                for(int r1: number_possibilities[number1])
                {
                    set<int> cop(possible[r1][c]);
                    for(int number: cop)
                    {
                        if (number != number1 && number != number2)
                        {
                            possible[r1][c].erase(number);
                            res |= 1;
                        }
                    }
                    cop.clear();
                }
            }
            if (n > 2)
            {
                set<int> set_n1n2;
                merge(set_n1n2, number_possibilities[number1]);
                for(int number3 = number2 + 1; number3 <= size; number3++)
                {
                    merge(number_possibilities[number1], number_possibilities[number3]);
                    if (number_possibilities[number1].size() == 3)
                    {
                        for(int r2: number_possibilities[number1])
                        {
                            set<int> cop(possible[r2][c]);
                            for(int number: cop)
                            {
                                if (number != number1 && number != number2 && number != number3)
                                {
                                    possible[r2][c].erase(number);
                                    res |= 1;
                                }
                            }
                            cop.clear();
                        }
                    }
                    set<int> set_n1n2n3;
                    merge(set_n1n2n3, number_possibilities[number1]);
                    for (int number4 = number3 + 1; number4 <= size; number4++)
                    {
                        merge(number_possibilities[number1], number_possibilities[number4]);
                        if (number_possibilities[number1].size() == 4)
                        {
                            for (int r3 : number_possibilities[number1])
                            {
                                set<int> cop(possible[r3][c]);
                                for (int number : cop)
                                {
                                    if (number != number1 && number != number2 && number != number3 && number != number4)
                                    {
                                        possible[r3][c].erase(number);
                                        res |= 1;
                                    }
                                }
                                cop.clear();
                            }
                        }
                        merge(number_possibilities[number1], set_n1n2n3);
                    }
                    if (set_n1n2n3.size())
                    {
                        set_n1n2n3.clear();
                    }
                    merge(number_possibilities[number1], set_n1n2);
                }
                if (set_n1n2.size())
                {
                    set_n1n2.clear();
                }
            }
            merge(number_possibilities[number1], set_n1);
        }
        if (set_n1.size())
        {
            set_n1.clear();
        }
    }
    for (int i = 1; i <= size; i++)
    {
        if (number_possibilities[i].size())
        {
            number_possibilities[i].clear();
        }
    }
    number_possibilities.clear();
    return res;
}
void sudoku_cl::remove_possibilities(int r, int c, vector < vector <int> > cur_board)
{
    int q = ((r - 1) / n) * n + ((c - 1) / n) + 1;
    for(int temp = 1; temp <= size; temp++)
    {
        possible[temp][c].erase(cur_board[r][c]);
        possible[r][temp].erase(cur_board[r][c]);
        possible[(q - 1) / n * n + (temp - 1) / n + 1][(q - 1) % n * n + (temp - 1) % n + 1].erase(cur_board[r][c]);
        possible[r][c].erase(temp);
    }
}
bool sudoku_cl::is_solved()
{
    if (board == filled_board)
        return 1;
    else return 0;
}
/*int main()
{
    int difficulty;
    while (difficulty < 1 || difficulty > 3)
    {
        cout<<"Enter difficulty(1-3):\n> ";
        cin>>difficulty;
    }
    int n = 0;
    while (n < 2)
    {
        cout<<"Enter size of small square:\n> ";
        cin>>n;
    }
    sudoku_cl * sudoku = new sudoku_cl(n, difficulty);
    while (!sudoku->solved)
        sudoku->fill_the_board();
    
}*/