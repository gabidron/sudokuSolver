#include <iostream>
#include <fstream>
#include <cstdlib>
#define N 10
using namespace std;
ifstream fin("sudoku.in");

class Sudoku
{
public:

    short int game[N][N];
    short int noOfEmptyPos = 0;
    struct
    {
        int x,y;
    } emptyPos[91];
    Sudoku()
    {

        for(int i = 1; i <N; ++i)
        {
            for(int j =1; j<N; ++j)
            {
                game[i][j] = 0;
            }
        }

    }
    bool safeMove(int n, Sudoku s)
    {
        //lineCheck
        for(int i = 1; i <= 9; i++)
            if(s.game[s.emptyPos[n].x][s.emptyPos[n].y] ==  s.game[s.emptyPos[n].x][i] && i != s.emptyPos[n].y)
                return false;
        //columnCheck
        for(int i=1; i<=9; i++)
            if(s.game[s.emptyPos[n].x][s.emptyPos[n].y] ==  s.game[i][s.emptyPos[n].y] && i != s.emptyPos[n].x)
                return false;
        //3*3 matrix position
        int x = s.emptyPos[n].x;
        int y = s.emptyPos[n].y;
        //x -> line && y -> colomn
        if(x<=3)
            x=1;
        else if(x<=6)
            x=4;
        else
            x=7;
        if(y<=3)
            y=1;
        else if(y<=6)
            y=4;
        else
            y=7;

        //3*3 matrix check
        for(int i=x; i<=x+2; i++)
            for(int j=y; j<=y+2; j++)
                if(s.game[i][j] == s.game[s.emptyPos[n].x][s.emptyPos[n].y] && (i!=s.emptyPos[n].x || j!=s.emptyPos[n].y))
                    return false;
        return true;

    }
    void solve(int n, Sudoku s)
    {
        //cout << s << '\n';
        if(n == s.noOfEmptyPos)
        {
            cout << s;
            exit(0);
        }
        else
        {
            for (int i = 1; i<= 9; ++i)
            {
                s.game[s.emptyPos[n].x][s.emptyPos[n].y] = i;

                if(s.safeMove(n, s))
                    solve(n+1, s);
                s.game[s.emptyPos[n].x][s.emptyPos[n].y] = 0;
            }
        }
    }
    friend ostream &operator<<( ostream &output, const Sudoku &S )
    {
        for(int i = 1; i <N; ++i)
        {
            for(int j =1; j<N; ++j)
            {
                output << S.game[i][j] << ' ';

            }
            output << '\n';
        }

        return output;
    }

    friend istream &operator>>( istream  &input, Sudoku &S )
    {
        for(int i = 1; i <N; ++i)
        {
            for(int j =1; j<N; ++j)
            {
                input >> S.game[i][j];
                if(S.game[i][j] == 0)
                {
                    S.emptyPos[S.noOfEmptyPos].x = i;
                    S.emptyPos[S.noOfEmptyPos].y = j;
                    S.noOfEmptyPos++;
                }
            }
        }

        return input;
    }
};
Sudoku sudoku;
int main()
{

    fin >> sudoku;
    sudoku.solve(0, sudoku);
    return 0;
}
