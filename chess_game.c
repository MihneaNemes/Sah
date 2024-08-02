#include <stdio.h>
#include <stdlib.h>
// - king is 10
// - queen is 9
// - rook is 5
// - knight is 2
// - bishop is 3
// - pawn is 1
// - empty space is 0
// - black pieces are with minus

int sah_mat = 0;
int cont = 0;
char wk[2] = {'4','7'};
char bk[2] = {'4','0'};

int board[8][8] = {
        {-5,-2,-3,-9,-10,-3,-2,-5},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {5,2,3,9,10,3,2,5}
    };
void afisare_tabla() {
    printf("    _______________________________________________\n");
    for(int i = 0; i < 8; i++) {
        printf("%d",8 - i);
        for(int j = 0; j < 8; j++) {
            printf("  |");
            printf("%3d", board[i][j]);
        }
        printf("  |");
        printf("\n");
        printf("   |_____|_____|_____|_____|_____|_____|_____|_____|\n");
        
    }
    printf("\n");
    printf(" ");
    for(int i = 0; i < 8; i++) {
        printf("%6c",'A' + i);
    }
    printf("\n");
}

int check_if_outside(int x1, int x2, int y1, int y2) {
    if((x2 < 0 || x2 > 7) || (y2 < 0) || (y2 > 7)) {
        return 0;
    }

    return 1;
}

int chcek_friendly_piece(int x1, int x2, int y1, int y2) {
    if(board[y2][x2] > 0 && board[y1][x1] > 0) {
        return 0;
    } 

    if(board[y2][x2] < 0 && board[y1][x1] < 0) {
        return 0;
    }

    return 1;
}

int check_king(int x1, int x2, int y1, int y2) {
    if(abs(x1-x2) <= 1 && abs(y1-y2) <= 1) {
        return 1;
    }

    return 0;
}

int check_bishop(int x1, int x2, int y1, int y2) {
    if(x1 > x2 && y1 > y2) {
        for(int i = 1; i < abs(x1 - x2); i++) {
            if(board[y1-i][x1-i] != 0) {
                return 0;
            }
        }
    }
    if(x1 > x2 && y2 > y1) {
        for(int i = 1; i < abs(x1 - x2); i++) {
            if(board[y1+i][x1-i] != 0) {
                return 0;
            }
        }
    }
    if(x1 < x2 && y2 > y1) {
        for(int i = 1; i < abs(x1 - x2); i++) {
            if(board[y1+i][x1+i] != 0) {
                return 0;
            }
        }
    }
    if(x1 < x2 && y2 < y1) {
        for(int i = 1; i < abs(x1 - x2); i++) {
            if(board[y1-i][x1+i] != 0) {
                return 0;
            }
        }
    }

    if(abs(x1-x2) == abs(y1-y2)) {
        return 1;
    }

    return 0;
}

int check_rook(int x1, int x2, int y1, int y2) {
    if(x1 != x2) {
        if(x1 > x2) {
            for(int i = 1; i < (x1-x2); i++) {
                if(board[y1][x1-i] != 0) {
                    return 0;
                }
            }
        }
        if(x1 < x2) {
            for(int i = 1; i < (x2-x1); i++) {
                if(board[y1][x1+i] != 0) {
                    return 0;
                }
            }
        }
    }

    if(y1 != y2) {
        if(y1 > y2) {
            for(int i = 1; i < (y1-y2); i++) {
                if(board[y1-i][x1] != 0) {
                    return 0;
                }
            }
        }
        if(y1 < y2) {
            for(int i = 1; i < (y2-y1); i++) {
                if(board[y1+i][x1] != 0) {
                    return 0;
                }
            }
        }
    }
    
    if((x1 == x2) || (y1 == y2)) {
        return 1;
    }

    return 0;
}

int check_queen(int x1, int x2, int y1, int y2) {
    if((check_bishop(x1,x2,y1,y2) == 1) || (check_rook(x1,x2,y1,y2) == 1)) {
        return 1;
    }

    return 0;
}

int check_knight(int x1, int x2, int y1, int y2) {
    if(((abs(x1-x2) == 1) && abs(y1-y2) == 2) || ((abs(x1-x2) == 2) && (abs(y1-y2) == 1))) {
        return 1;
    }

    return 0;
}

int check_pawn(int x1, int x2, int y1, int y2) {
    if((board[y2][x2] != 0) && (((abs(y1-y2) == 1) && (x1 == x2)) || ((abs(y1-y2) == 2) && (x1 == x2)))) {
        return 0;
    }

    if(board[y1][x1] > 0) {
        if((board[y1-1][x1] != 0) || (y1 < y2)) {
            return 0;
        }   
    }
    if(board[y1][x1] < 0) {
        if((board[y1+1][x1] != 0) || (y1 > y2)) {
            return 0;
        }   
    }
    
    if((abs(x1 - x2) == 1) && (abs(y1 - y2) == 1) && (board[y2][x2] != 0) && chcek_friendly_piece(x1,x2,y1,y2)) {
        return 1;
    }

    if(((abs(y1-y2) == 1) && (x1 == x2))) {
        return 1;
    }

    if((y1 == 1 || y1 == 6) && ((abs(y1-y2) == 2) && (x1 == x2))) {
        return 1;
    }
    
    return 0;
}


int check_wsah_by_bishop(int x1, int x2, int y1, int y2) {
    int p = 0;
    if(x1 > x2 && y1 > y2) {
        
        for(int i = 1; i <= abs(x1 - x2); i++) {
            if(board[y1-i][x1-i] != 0) {
                p++;
            }
            if(board[y1-i][x1-i] == 10) {
                return 1;
            }
            if(p > 0) {
                break;
            }
        }
    }
    
    p = 0;
    if(x1 > x2 && y2 > y1) {
        
        for(int i = 1; i < abs(x1 - x2); i++) {
            if(board[y1+i][x1-i] != 0) {
                p++;
            }
            if(board[y1+i][x1-i] == 10) {
                return 1;
            }
            if(p > 0) {
                break;
            }
        }
    }

    p = 0;
    if(x2 > x1 && y2 < y1) {
        
        for(int i = 1; i < abs(x1 - x2); i++) {
            if(board[y1-i][x1+i] != 0) {
                p++;
            }
            if(board[y1-i][x1+i] == 10) {
                return 1;
            }
            if(p > 0) {
                break;
            }
        }
    }

    p = 0;
    if(x2 > x1 && y2 > y1) {
        for(int i = 1; i <= abs(x1 - x2); i++) {
            if(board[y1+i][x1+i] != 0) {
                p++;
            }
            if(board[y1+i][x1+i] == 10) {
                return 1;
            }
            if(p > 0) {
                break;
            }
        }
    }

    return 0;
}
int check_wsah_by_rook(int x1, int x2, int y1, int y2) {
    if(x1 != x2) {
        int p = 0;
        if(x1 > x2) {
            for(int i = 1; i <= abs(x1-x2); i++) {
                if(board[y1][x1-i] != 0) {
                    p++;
                }
                if(board[y1][x1-i] == 10) {
                    return 1;
                }
                if(p > 0) {
                    break;
                }
            }
        }

        p = 0;
        if(x1 < x2) {
            for(int i = 1; i <= abs(x2-x1); i++) {
                if(board[y1][x1+i] != 0) {
                    p++;
                }
                if(board[y1][x1+i] == 10) {
                    return 1;
                }
                if(p > 0) {
                    break;
                }
            }
        }
    }

    if(y1 != y2) {
        int p = 0;
        if(y1 > y2) {
            for(int i = 1; i <= abs(y1-y2); i++) {
                if(board[y1-i][x1] != 0) {
                    p++;
                }
                if(board[y1-i][x1] == 10) {
                    return 1;
                }
                if(p > 0) {
                    break;
                }
            }
        }

        p = 0;
        if(y1 < y2) {
            for(int i = 1; i <= abs(y2-y1); i++) {
                if(board[y1+i][x1] != 0) {
                    p++;
                }
                if(board[y1+i][x1] == 10) {
                    return 1;
                }
                if(p > 0) {
                    break;
                }
            }
        }
    }
    return 0;
}
int check_wsah_by_queen(int x1, int x2, int y1, int y2) {
    if(check_wsah_by_bishop(x1,x2,y1,y2) || check_wsah_by_rook(x1,x2,y1,y2)) {
        return 1;
    }
    return 0;
}
int check_wsah_by_pawn(int x1, int x2, int y1, int y2) {
    if((board[y1-1][x1+1] == 10) || (board[y1-1][x1-1] == 10)) {
        return 1;
    }
    return 0;
}
int check_wsah_by_knight(int x1, int x2, int y1, int y2) {
    if(board[y1-2][x1+1] == 10)  {
        return 1;
    }
    if(board[y1-1][x1+2] == 10)  {
        return 1;
    }
    if(board[y1+1][x1+2] == 10)  {
        return 1;
    }
    if(board[y1+2][x1+1] == 10)  {
        return 1;
    }
    if(board[y1+2][x1-1] == 10)  {
        return 1;
    }
    if(board[y1+1][x1-2] == 10)  {
        return 1;
    }
    if(board[y1-1][x1-2] == 10)  {
        return 1;
    }
    if(board[y1-2][x1-1] == 10)  {
        return 1;
    }
    return 0;
}

int check_if_wk_in_sah() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] == -1) {
                if(check_wsah_by_pawn(j,wk[0]-'0',i,wk[1]-'0')) {
                    return 1;
                }
            }

            if(board[i][j] == -2) {
                if(check_wsah_by_knight(j,wk[0]-'0',i,wk[1]-'0')) {
                    return 1;
                }
            }

            if(board[i][j] == -3) {
                if(check_wsah_by_bishop(j,wk[0]-'0',i,wk[1]-'0')) {
                    return 1;
                }
            }

            if(board[i][j] == -5) {
                if(check_wsah_by_rook(j,wk[0]-'0',i,wk[1]-'0')) {
                    return 1;
                }
            }

            if(board[i][j] == -9) {
                if(check_wsah_by_queen(j,wk[0]-'0',i,wk[1]-'0')) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int check_bsah_by_bishop(int x1, int x2, int y1, int y2) {
    int p = 0;
    if(x1 > x2 && y1 > y2) {
        
        for(int i = 1; i <= abs(x1 - x2); i++) {
            if(board[y1-i][x1-i] != 0) {
                p++;
            }
            if(board[y1-i][x1-i] == -10) {
                return 1;
            }
            if(p > 0) {
                break;
            }
        }
    }
    
    p = 0;
    if(x1 > x2 && y2 > y1) {
        
        for(int i = 1; i < abs(x1 - x2); i++) {
            if(board[y1+i][x1-i] != 0) {
                p++;
            }
            if(board[y1+i][x1-i] == -10) {
                return 1;
            }
            if(p > 0) {
                break;
            }
        }
    }

    p = 0;
    if(x2 > x1 && y2 < y1) {
        
        for(int i = 1; i < abs(x1 - x2); i++) {
            if(board[y1-i][x1+i] != 0) {
                p++;
            }
            if(board[y1-i][x1+i] == -10) {
                return 1;
            }
            if(p > 0) {
                break;
            }
        }
    }

    p = 0;
    if(x2 > x1 && y2 > y1) {
        for(int i = 1; i <= abs(x1 - x2); i++) {
            if(board[y1+i][x1+i] != 0) {
                p++;
            }
            if(board[y1+i][x1+i] == -10) {
                return 1;
            }
            if(p > 0) {
                break;
            }
        }
    }

    return 0;
}
int check_bsah_by_rook(int x1, int x2, int y1, int y2) {
    if(x1 != x2) {
        int p = 0;
        if(x1 > x2) {
            for(int i = 1; i <= abs(x1-x2); i++) {
                if(board[y1][x1-i] != 0) {
                    p++;
                }
                if(board[y1][x1-i] == -10) {
                    return 1;
                }
                if(p > 0) {
                    break;
                }
            }
        }

        p = 0;
        if(x1 < x2) {
            for(int i = 1; i <= abs(x2-x1); i++) {
                if(board[y1][x1+i] != 0) {
                    p++;
                }
                if(board[y1][x1+i] == -10) {
                    return 1;
                }
                if(p > 0) {
                    break;
                }
            }
        }
    }

    if(y1 != y2) {
        int p = 0;
        if(y1 > y2) {
            for(int i = 1; i <= abs(y1-y2); i++) {
                if(board[y1-i][x1] != 0) {
                    p++;
                }
                if(board[y1-i][x1] == -10) {
                    return 1;
                }
                if(p > 0) {
                    break;
                }
            }
        }

        p = 0;
        if(y1 < y2) {
            for(int i = 1; i <= abs(y2-y1); i++) {
                if(board[y1+i][x1] != 0) {
                    p++;
                }
                if(board[y1+i][x1] == -10) {
                    return 1;
                }
                if(p > 0) {
                    break;
                }
            }
        }
    }
    return 0;
}
int check_bsah_by_queen(int x1, int x2, int y1, int y2) {
    if(check_bsah_by_bishop(x1,x2,y1,y2) || check_bsah_by_rook(x1,x2,y1,y2)) {
        return 1;
    }
    return 0;
}
int check_bsah_by_pawn(int x1, int x2, int y1, int y2) {
    if((board[y1+1][x1+1] == -10) || (board[y1+1][x1-1] == -10)) {
        return 1;
    }
    return 0;
}
int check_bsah_by_knight(int x1, int x2, int y1, int y2) {
    if(board[y1-2][x1+1] == 10)  {
        return 1;
    }
    if(board[y1-1][x1+2] == 10)  {
        return 1;
    }
    if(board[y1+1][x1+2] == 10)  {
        return 1;
    }
    if(board[y1+2][x1+1] == 10)  {
        return 1;
    }
    if(board[y1+2][x1-1] == 10)  {
        return 1;
    }
    if(board[y1+1][x1-2] == 10)  {
        return 1;
    }
    if(board[y1-1][x1-2] == 10)  {
        return 1;
    }
    if(board[y1-2][x1-1] == 10)  {
        return 1;
    }
    return 0;
}

int check_if_bk_in_sah() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] == 1) {
                if(check_bsah_by_pawn(j,bk[0]-'0',i,bk[1]-'0')) {
                    return 1;
                }
            }

            if(board[i][j] == 2) {
                if(check_bsah_by_knight(j,bk[0]-'0',i,bk[1]-'0')) {
                    return 1;
                }
            }

            if(board[i][j] == 3) {
                if(check_bsah_by_bishop(j,bk[0]-'0',i,bk[1]-'0')) {
                    return 1;
                }
            }

            if(board[i][j] == 5) {
                if(check_bsah_by_rook(j,bk[0]-'0',i,bk[1]-'0')) {
                    return 1;
                }
            }

            if(board[i][j] == 9) {
                if(check_bsah_by_queen(j,bk[0]-'0',i,bk[1]-'0')) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

float wmobility() {
    float wmob = 0;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if(board[i][j] == 1)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_pawn(j,x,i,y))
                            wmob += 0.1;
                    }
                }
            if(board[i][j] == 2)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_knight(j,x,i,y))
                            wmob += 0.1;
                    }
                }
            if(board[i][j] == 3)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_bishop(j,x,i,y))
                            wmob += 0.1;
                    }
                }
            if(board[i][j] == 5)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_rook(j,x,i,y))
                            wmob += 0.1;
                    }
                }
            if(board[i][j] == 9)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_queen(j,x,i,y))
                            wmob += 0.1;
                    }
                }
            if(board[i][j] == 10) 
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_king(j,x,i,y))
                            wmob += 0.1;
                    }
                }
        }
    }
    return wmob;
}

float bmobility () {
    float bmob = 0;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if(board[i][j] == 1)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_pawn(j,x,i,y))
                            bmob += 0.1;
                    }
                }
            if(board[i][j] == 2)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_knight(j,x,i,y))
                            bmob += 0.1;
                    }
                }
            if(board[i][j] == 3)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_bishop(j,x,i,y))
                            bmob += 0.1;
                    }
                }
            if(board[i][j] == 5)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_rook(j,x,i,y))
                            bmob += 0.1;
                    }
                }
            if(board[i][j] == 9)
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_queen(j,x,i,y))
                            bmob += 0.1;
                    }
                }
            if(board[i][j] == 10) 
                for(int y = 0; y<8; y++) {
                    for(int x = 0; x<8; x++) {
                        if(check_king(j,x,i,y))
                            bmob += 0.1;
                    }
                }
        }
    }
    return bmob;
}

float wscore() {
    float ws = 0;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if(board[i][j] == 1) {
                ws++;
                int nr1 = 0;
                for(int i1 = 0; i1<8; i1++) {
                    if(board[i1][j+1] == 1 && board[i1][j-1] == 1) {
                        nr1 = 1;
                    }
                }
                if(nr1 == 0) {
                    ws -= 0.5;
                }

                if(board[i+1][j] == 1)
                    ws -= 0.5;

                if(board[i+1][j] == -1)
                    ws -= 0.5;
            }
            if(board[i][j] == 2)
                ws += 3;
            if(board[i][j] == 3)
                ws += 3;
            if(board[i][j] == 5)
                ws += 5;
            if(board[i][j] == 9)
                ws += 9;
            if(board[i][j] == 10) {
                ws += 200;
            }
        }
    }
    ws += wmobility();
    return ws;
}

float bscore() {
    float bs = 0;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if(board[i][j] == -1) {
                bs++;
                int nr1 = 0;
                for(int i1 = 0; i1<8; i1++) {
                    if(board[i1][j+1] == -1 && board[i1][j-1] == -1) {
                        nr1 = 1;
                    }
                }
                if(nr1 == 0) {
                    bs -= 0.5;
                }

                if(board[i+1][j] == -1)
                    bs -= 0.5;

                if(board[i-1][j] == 1)
                    bs -= 0.5;
            }
            if(board[i][j] == -2)
                bs += 3;
            if(board[i][j] == -3)
                bs += 3;
            if(board[i][j] == -5)
                bs += 5;
            if(board[i][j] == -9)
                bs += 9;
            if(board[i][j] == -10) {
                bs += 200;
            }
        }
    }
    bs += bmobility();
    return bs;
}

void mutare_robot() {
    float smax = 0;
    int x1,x2,y1,y2;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if(board[i][j] == -1) {
                for(int k = 0; k<8; k++) {
                    for(int p = 0; p<8; p++) {
                        if(check_pawn(j,p,i,k)) {
                            if(smax < bscore()) {
                                smax = bscore();
                                x1 = j;
                                x2 = p;
                                y1 = i;
                                y2 = k;
                            }   
                        }
                    }
                }
            }
            if(board[i][j] == -2) {
                    for(int k = 0; k<8; k++) {
                    for(int p = 0; p<8; p++) {
                        if(check_knight(j,p,i,k)) {
                            if(smax < bscore()) {
                                smax = bscore();
                                x1 = j;
                                x2 = p;
                                y1 = i;
                                y2 = k;
                            }
                        }
                    }
                }
            }
            if(board[i][j] == -3) {
                    for(int k = 0; k<8; k++) {
                    for(int p = 0; p<8; p++) {
                        if(check_bishop(j,p,i,k)) {
                            if(smax < bscore()) {
                                smax = bscore();
                                x1 = j;
                                x2 = p;
                                y1 = i;
                                y2 = k;
                            }
                        }
                    }
                }
            }
            if(board[i][j] == -5) {
                    for(int k = 0; k<8; k++) {
                    for(int p = 0; p<8; p++) {
                        if(check_rook(j,p,i,k)) {
                            if(smax < bscore()) {
                                smax = bscore();
                                x1 = j;
                                x2 = p;
                                y1 = i;
                                y2 = k;
                            }
                        }
                    }
                }
            }
            if(board[i][j] == -9) {
                    for(int k = 0; k<8; k++) {
                    for(int p = 0; p<8; p++) {
                        if(check_queen(j,p,i,k)) {
                            if(smax < bscore()) {
                                smax = bscore();
                                x1 = j;
                                x2 = p;
                                y1 = i;
                                y2 = k;
                            }
                        }
                    }
                }
            }  
            if(board[i][j] == -10) {
                    for(int k = 0; k<8; k++) {
                    for(int p = 0; p<8; p++) {
                        if(check_king(j,p,i,k)) {
                            if(smax < bscore()) {
                                smax = bscore();
                                x1 = j;
                                x2 = p;
                                y1 = i;
                                y2 = k;
                            }
                        }
                    }
                }
            } 
        }
    }
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = 0;
}

void mutare() {
    
    int piesa;
    char x1,x2,y1,y2;
    printf("piesa: ");
    scanf(" %d",&piesa);
    printf("poz initiala: ");
    scanf(" %c",&x1); scanf(" %c",&y1); 

    if(piesa == 1) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_pawn(x1-'a',j,8-(y1-'0'),i) && (board[i][j] <= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == 2) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_knight(x1-'a',j,8-(y1-'0'),i) && (board[i][j] <= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == 3) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_bishop(x1-'a',j,8-(y1-'0'),i) && (board[i][j] <= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == 5) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_rook(x1-'a',j,8-(y1-'0'),i) && (board[i][j] <= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == 9) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_queen(x1-'a',j,8-(y1-'0'),i) && (board[i][j] <= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == 10) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_king(x1-'a',j,8-(y1-'0'),i) && (board[i][j] <= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == -1) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_pawn(x1-'a',j,8-(y1-'0'),i) && (board[i][j] >= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == -2) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_knight(x1-'a',j,8-(y1-'0'),i) && (board[i][j] >= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == -3) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_bishop(x1-'a',j,8-(y1-'0'),i) && (board[i][j] >= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == -5) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_rook(x1-'a',j,8-(y1-'0'),i) && (board[i][j] >= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == -9) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_queen(x1-'a',j,8-(y1-'0'),i) && (board[i][j] >= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    if(piesa == -10) {
        int cont = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) { 
                if(check_king(x1-'a',j,8-(y1-'0'),i) && (board[i][j] >= 0)) {
                    printf("%c%c\n",'a'+j,'8'-i);
                    cont++;
                }
            }
        }
        if(cont == 0) {
            printf("piesa nu are mutari valabile");
        }
        printf("\n");
    }

    printf("poz finala: ");
    scanf(" %c ",&x2); scanf(" %c",&y2);
    
    if(check_if_outside(x1-'a',x2-'a',8-(y1-'0'),8-(y2-'0'))) {
        if(chcek_friendly_piece(x1-'a',x2-'a',8-(y1-'0'),8-(y2-'0'))) {
            if(abs(piesa) == 1) {
                if(check_pawn(x1-'a',x2-'a',8-(y1-'0'),8-(y2-'0')) && (board[8-(y1-'0')][x1-'a'] == 1 || board[8-(y1-'0')][x1-'a'] == -1)) {
                    board[8-(y2-'0')][x2-'a'] = board[8-(y1-'0')][x1-'a'];
                    board[8-(y1-'0')][x1-'a'] = 0;
                }
                else {
                    cont++;
                }
            }

            if(abs(piesa) == 2) {
                if(check_knight(x1-'a',x2-'a',8-(y1-'0'),8-(y2-'0')) && (board[8-(y1-'0')][x1-'a'] == 2 || board[8-(y1-'0')][x1-'a'] == -2)) {
                    board[8-(y2-'0')][x2-'a'] = board[8-(y1-'0')][x1-'a'];
                    board[8-(y1-'0')][x1-'a'] = 0;
                }   
                else {
                    cont++;
                }
            }
            
            if(abs(piesa) == 3) {
                if(check_bishop(x1-'a',x2-'a',8-(y1-'0'),8-(y2-'0')) && (board[8-(y1-'0')][x1-'a'] == 3 || board[8-(y1-'0')][x1-'a'] == -3)) {
                    board[8-(y2-'0')][x2-'a'] = board[8-(y1-'0')][x1-'a'];
                    board[8-(y1-'0')][x1-'a'] = 0;
                }
                else {
                    cont++;
                }
            }
            
            if(abs(piesa) == 5) {
                if(check_rook(x1-'a',x2-'a',8-(y1-'0'),8-(y2-'0')) && (board[8-(y1-'0')][x1-'a'] == 5 || board[8-(y1-'0')][x1-'a'] == -5)) {
                    board[8-(y2-'0')][x2-'a'] = board[8-(y1-'0')][x1-'a'];
                    board[8-(y1-'0')][x1-'a'] = 0;
                }
                else {
                    cont++;
                }
            }
            
            if(abs(piesa) == 9) {
                if(check_queen(x1-'a',x2-'a',8-(y1-'0'),8-(y2-'0')) && (board[8-(y1-'0')][x1-'a'] == 9 || board[8-(y1-'0')][x1-'a'] == -9)) {
                    board[8-(y2-'0')][x2-'a'] = board[8-(y1-'0')][x1-'a'];
                    board[8-(y1-'0')][x1-'a'] = 0;
                }
                else {
                    cont++;
                }
            }
            
            if(abs(piesa) == 10) {
                if(check_king(x1-'a',x2-'a',8-(y1-'0'),8-(y2-'0')) && (board[8-(y1-'0')][x1-'a'] == 10 || board[8-(y1-'0')][x1-'a'] == -10)) {
                    board[8-(y2-'0')][x2-'a'] = board[8-(y1-'0')][x1-'a'];
                    board[8-(y1-'0')][x1-'a'] = 0;
                }
                else {
                    cont++;
                }
            }
        }
        else {
            cont = 1;
        }
    }
    else {
        cont = 1;
    }
    
}

int main() {
    int menue;
    printf("press 1 for pvp\n");
    printf("press 2 for pvc\n");
    scanf("%d",&menue);

    if(menue == 1) {
        afisare_tabla();
        printf("\n");
        int white = 1;

        while(sah_mat != 1) {
            printf("white score is: %f                          black score is: %f \n",wscore(),bscore());
            if((white % 2) != 0){
                if(check_if_wk_in_sah()) {
                    printf("SAH!\n");
                
                }
                printf("white moves:");
            }
            else {
                if(check_if_bk_in_sah()) {
                    printf("SAH!\n");
                
                }
                printf("black moves:");
            }

            printf("\n");
            mutare();

            if(cont != 1) {
                white++;
            }
            else {
                printf("Nu e o mutare valida!");
            }
        
            printf("\n");
            afisare_tabla();

            cont = 0;
        }
    }

    if(menue == 2) {
        afisare_tabla();
        printf("\n");
        printf("white score is: %f                          black score is: %f \n",wscore(),bscore());

        while(sah_mat != 1) {
            mutare();
            afisare_tabla();
            printf("\n");
            mutare_robot();
            afisare_tabla();
        }
    }
    
    return 0;
}