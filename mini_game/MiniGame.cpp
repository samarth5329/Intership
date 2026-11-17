#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

const int N = 3, ROWS = 10, COLS = 20;

void showBoard(const char b[N][N]) {
    cout << "\n";
    for (int r=0;r<N;++r) {
        cout << " ";
        for (int c=0;c<N;++c) { cout << b[r][c]; if(c<N-1) cout << " | "; }
        cout << "\n";
        if(r<N-1) cout << "---+---+---\n";
    }
}

bool winner(const char b[N][N], char p) {
    for(int i=0;i<N;++i) {
        if(b[i][0]==p && b[i][1]==p && b[i][2]==p) return true;
        if(b[0][i]==p && b[1][i]==p && b[2][i]==p) return true;
    }
    return (b[0][0]==p && b[1][1]==p && b[2][2]==p) ||
           (b[0][2]==p && b[1][1]==p && b[2][0]==p);
}

bool replay() {
    string s;
    cout << "\nPlay again? (y/n): ";
    getline(cin,s);
    return !s.empty() && (s[0]=='y' || s[0]=='Y');
}

void ticTacToe() {
    bool again=true;
    while(again) {
        char b[N][N]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
        char p='X'; int moves=0; bool done=false;
        cout << "\n=== TIC TAC TOE ===\nPlayer 1: X  Player 2: O\n";
        while(!done) {
            showBoard(b);
            cout << "Player " << p << ", choose cell (1-9): ";
            string s; getline(cin,s);
            if(s.size()!=1 || s[0]<'1' || s[0]>'9') {
                cout << "Enter a number from 1 to 9.\n"; continue;
            }
            int k=s[0]-'1', r=k/3, c=k%3;
            if(b[r][c]=='X' || b[r][c]=='O') {
                cout << "Cell occupied. Try again.\n"; continue;
            }
            b[r][c]=p; ++moves;
            if(winner(b,p)) { showBoard(b); cout << "Player " << p << " wins!\n"; done=true; }
            else if(moves==9) { showBoard(b); cout << "It's a draw!\n"; done=true; }
            else p=(p=='X')?'O':'X';
        }
        again=replay();
    }
}

struct Point { int r,c; };
bool equalPoint(Point a, Point b) { return a.r==b.r && a.c==b.c; }

void putFood(Point& food, const vector<Point>& snake) {
    bool used;
    do {
        used=false; food={rand()%ROWS,rand()%COLS};
        for(Point part:snake) if(equalPoint(part,food)) { used=true; break; }
    } while(used);
}

void showSnake(const vector<Point>& snake, Point food) {
    cout << "\n";
    for(int r=0;r<ROWS;++r) {
        cout << "+";
        for(int c=0;c<COLS;++c) cout << "--";
        cout << "+\n|";
        for(int c=0;c<COLS;++c) {
            Point q={r,c}; char ch=' ';
            if(equalPoint(q,food)) ch='*';
            for(size_t i=0;i<snake.size();++i)
                if(equalPoint(q,snake[i])) { ch=(i==0)?'O':'o'; break; }
            cout << " " << ch;
        }
        cout << " |\n";
    }
    cout << "+";
    for(int c=0;c<COLS;++c) cout << "--";
    cout << "+\nLength: " << snake.size() << "  Food: *  Head: O\n";
}

void snakeGame() {
    bool again=true;
    while(again) {
        vector<Point> snake={{ROWS/2,COLS/2},{ROWS/2,COLS/2-1},{ROWS/2,COLS/2-2}};
        Point food; putFood(food,snake);
        char dir='d'; bool over=false, won=false;
        cout << "\n=== SNAKE GAME ===\nUse W/A/S/D then Enter to move one cell.\nEat * and avoid walls and your body.\n";
        while(!over) {
            showSnake(snake,food);
            cout << "Move (W/A/S/D): ";
            string s; getline(cin,s);
            if(s.empty()) { cout << "Enter a direction.\n"; continue; }
            char next=static_cast<char>(tolower(static_cast<unsigned char>(s[0])));
            if(next!='w' && next!='a' && next!='s' && next!='d') {
                cout << "Use W, A, S, or D.\n"; continue;
            }
            bool reverse=(dir=='w'&&next=='s')||(dir=='s'&&next=='w')||
                         (dir=='a'&&next=='d')||(dir=='d'&&next=='a');
            if(reverse && snake.size()>1) { cout << "Cannot reverse directly.\n"; continue; }
            dir=next; Point head=snake[0];
            if(dir=='w') --head.r; else if(dir=='s') ++head.r;
            else if(dir=='a') --head.c; else ++head.c;
            if(head.r<0 || head.r>=ROWS || head.c<0 || head.c>=COLS) { over=true; break; }
            bool eating=equalPoint(head,food);
            size_t limit=eating?snake.size():snake.size()-1;
            for(size_t i=0;i<limit;++i) if(equalPoint(head,snake[i])) { over=true; break; }
            if(over) break;
            snake.insert(snake.begin(),head);
            if(eating) {
                if(snake.size()==static_cast<size_t>(ROWS*COLS)) { won=true; over=true; }
                else putFood(food,snake);
            } else snake.pop_back();
        }
        showSnake(snake,food);
        if(won) cout << "You filled the board. You win!\n";
        else cout << "Game over! Final length: " << snake.size() << "\n";
        again=replay();
    }
}

int menu() {
    string s; cout << "\nEnter choice: "; getline(cin,s);
    if(s.size()==1 && s[0]>='1' && s[0]<='3') return s[0]-'0';
    return -1;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    cout << "=====================================\n MINI GAME PROJECT\n=====================================\n";
    while(true) {
        cout << "\n1. Tic Tac Toe\n2. Snake Game\n3. Exit\n";
        switch(menu()) {
            case 1: ticTacToe(); break;
            case 2: snakeGame(); break;
            case 3: cout << "Thanks for playing!\n"; return 0;
            default: cout << "Invalid choice. Select 1, 2, or 3.\n";
        }
    }
}
