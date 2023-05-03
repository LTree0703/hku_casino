#include<iostream>
#include<algorithm>
#include<string>
using namespace std;




int get_pattern_rank(int suit[7], int rank[7]);
void compare(int suitH[7], int rankH[7],int suitC[7], int rankC[7]);
string current_rank = "A", highest_rank = "B";





int main(){
    int suitC[7],rankC[7],suitH[7],rankH[7];
    
    for (int i = 0; i < 7; i++){
        cout << "the current suit & rank: " << endl ; 
        cin >> suitC[i] >> rankC[i];
        cout << "the higest suit & rank: " << endl;
        cin >> suitH[i] >> rankH[i];
        }
    int current,high;
    current  = get_pattern_rank(suitC,rankC);
    high = get_pattern_rank(suitH,rankH);



    
    if (current > high){
        cout << current << "wins" << endl;}
    else if (current < high){
        cout << high << "wins" << endl;
    }
    
    else if (current == high){
        compare(suitC,rankC,suitH,rankH);
        cout << highest_rank << " Wins !"<< endl;

    
    return 0;
}}

int get_pattern_rank(int suit[7], int rank[7]){
    /*check rank,straight 
    2=2,3=3,...,J=11,Q=12,K=13,A=14;*/

    sort(rank, rank + 7);

    int str_rank = 0;
    for (int a = 6; a >3;a--){
        if (rank[a] - 1 == rank[a - 1] && rank[a] - 2 == rank[a - 2] && rank[a] - 3 == rank[a - 3]  && rank[a] - 4 == rank[a - 4] ){
            str_rank = 1;
            break;
        }
        if (rank[0] == 2 && rank[1] == 3 && rank[2] == 4 && rank[3] == 5 && rank[6] == 14){
            str_rank = 1;
            break;
        }
    }  

    // check suit, flush
    int S = 0,H = 0,D = 0,C = 0,str_suit = 0;    
    for (int c = 0; c < 7; c ++)
    {
        if (suit[c] == 0)
        {
            S++;
        }
        else if (suit[c] == 1)
        {
            H++;
        }
        else if (suit[c] == 2)
        {
            D++;
        }
        else if (suit[c] == 3)
        {
            C++;
        }
    }

    if (S >= 5 || H >= 5 || D >= 5 || C >= 5) 
    {
        str_suit = 1;
    }   

    // check the three of a kind,two pair,one pair, fullhouse 

    int three_of_a_kind = 0, two_pairs = 0, one_pairs = 0,  Four_of_a_kind = 0;
    for (int d = 0; d < 7; d++) 
    {
        int count_pattern = 1;
        for (int e = d + 1; e < 7; e++) 
        {
            if (rank[d] == rank[e] && d != e && (rank[d] != -1 || rank[e] != -1)) 
            {
                count_pattern++;
                rank[e] = -1;
            } 
        }
        if (count_pattern == 2) 
        {   
            
            one_pairs++;
        }
        else if (count_pattern == 3 ) 
        {   
            three_of_a_kind++;
        }  
        else if (count_pattern == 4) 
        {
            Four_of_a_kind++;
        }
    }  
    if (str_suit == 1 && str_rank == 1)
    {
        cout << "Straight Flush !";
        return 8;        
    }
    if (str_suit == 1 && str_rank == 1)
    {
        cout << "Straight Flush !";
        return 8;        
    }
    else if (Four_of_a_kind >= 1)
    {
        cout << "Four of a Kind !";
        return 7; }

    else if ((one_pairs > 0 && three_of_a_kind > 0) || three_of_a_kind == 2)
    {
        cout << "Full House !";
        return 6;
    }
    else if (str_suit == 1 && str_rank != 1)
    {
        cout << "Flush !";
        return 5;
    }
    else if (str_suit != 1 && str_rank == 1)
    {
        cout << "Straight !";
        return 4;
    }
    else if (three_of_a_kind == 1 && one_pairs == 0)
    {
        cout << "Three of a Kind !";
        return 3;
    }    
    else if (one_pairs >= 2 && three_of_a_kind == 0)
    {
        cout << "Two Pairs !";
        return 2;
    } 
    else if (one_pairs == 1 && three_of_a_kind == 0)
    {
        cout << "One Pairs !";
        return 1;
    }    
    else 
    {
        cout << "No Special Pattern !";
        return 0;
    }
}


void compare(int suitH[7], int rankH[7],int suitC[7], int rankC[7]){
sort(rankC, rankC + 7);
sort(rankH, rankH + 7);
int type ;
if (type == 0) {
    // no special
    int count0 = 0;
    for (int d = 6; d > -1; d--) {
        if (rankC[d] > rankH[d]) {
            highest_rank = current_rank;
            break;
        }
        else if (rankC[d] == rankH[d]) {
            count0++;
        }
    }
    if (count0 == 7) {
        cout << "Draw !" << endl;
    }
} 
else if (type == 1) {
    // one pair
    int str_cur, str_high;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (rankC[j] == rankC[i] && i != j) {
                str_cur = rankC[j];
            }
            if (rankH[j] == rankH[i] && i != j) {
                str_high = rankH[j];
            }
        }
    }
    if (str_cur > str_high) {
        highest_rank = current_rank;
    } else if (str_cur == str_high) {
        int count1 = 0;
        for (int z = 6; z > -1; z--) {
            if (rankC[z] > rankH[z]) {
                highest_rank = current_rank;
                break;
            } else if (rankC[z] == rankH[z]) {
                count1++;
            }
        }
        if (count1 == 7) {
            cout << "Draw !" << endl;
        }
    }
}
else if (type == 2) {
    // two pairs
    int high_pair_cur = 0, high_pair_high = 0, second_pair_cur = 0, second_pair_high = 0, fifth_card_cur = 0, fifth_card_high = 0;
    for (int k = 6; k >= 1; k--) {
        if (rankC[k] == rankC[k - 1]) {
            if (rankC[k] > high_pair_cur) {
                second_pair_cur = high_pair_cur;
                high_pair_cur = rankC[k];
            } else {
                second_pair_cur = rankC[k];
            }
        }
        if (rankH[k] == rankH[k - 1]) {
            if (rankH[k] > high_pair_high) {
                second_pair_high = high_pair_high;
                high_pair_high = rankH[k];
            } else {
                second_pair_high = rankH[k];
            }
        }
    }
    if (high_pair_cur > high_pair_high) {
        highest_rank = current_rank;
    } 
    else if (high_pair_cur == high_pair_high) {
        if (second_pair_cur > second_pair_high) {
            highest_rank = current_rank;
        } else if (second_pair_cur == second_pair_high) {
            for (int a = 6; a >= 0; a--) {
                if (rankC[a] != high_pair_cur && rankC[a] != second_pair_cur) {
                    fifth_card_cur = rankC[a];
                    break;
                }
            }
            for (int a = 6; a >= 0; a--) {
                if (rankH[a] != high_pair_high && rankH[a] != second_pair_high) {
                    fifth_card_high = rankH[a];
                    break;
                }
            }
            if (fifth_card_cur > fifth_card_high) {
                highest_rank = current_rank;
            } else if (fifth_card_cur == fifth_card_high) {
                cout << "Draw !" << endl;
            }
        }
    }
}


else if (type == 3) {
    // three of a kind
    int str_cur, str_high;
    for (int m = 6; m > 1; m--) {
        if (rankC[m] == rankC[m - 1] && rankC[m - 1] == rankC[m - 2]) {
            str_cur = rankC[m];
            break;
        }
    }
    for (int m = 6; m > 1; m--) {
        if (rankH[m] == rankH[m - 1] && rankH[m - 1] == rankH[m - 2]) {
            str_high = rankH[m];
            break;
        }
    }
    if (str_cur > str_high) {
        highest_rank = current_rank;
    }
    else if (str_cur < str_high) {
        highest_rank = highest_rank;
    }
    else { // compare remaining cards if three of a kind ranks are equal
        for (int a = 6; a >= 0; a--) {
            if (rankC[a] > rankH[a]) {
                highest_rank = current_rank;
                break;
            }
            else if (rankC[a] < rankH[a]) {
                highest_rank = highest_rank;
                break;
            }
            else if (a == 0) { // all cards are equal, it's a draw
                cout << "Draw!" << endl;
            }
        }
    }
}


else if (type == 4) {
    // straight
    int str_cur, str_high; // initialize to -1
    for (int i = 6; i >= 4; i--) {
        if (rankC[i] == rankC[i - 1] + 1 && rankC[i] == rankC[i - 2] + 2 &&
            rankC[i] == rankC[i - 3] + 3 && rankC[i] == rankC[i - 4] + 4) {
            str_cur = rankC[i];
            break;
        }
    }
    for (int i = 6; i >= 4; i--) {
        if (rankH[i] == rankH[i - 1] + 1 && rankH[i] == rankH[i - 2] + 2 &&
            rankH[i] == rankH[i - 3] + 3 && rankH[i] == rankH[i - 4] + 4) {
            str_high = rankH[i];
            break;
        }
    }
    if (str_cur > str_high) {
        highest_rank = current_rank;
    }
    else if (str_cur < str_high) {
        highest_rank = highest_rank;
    }
    else { // ranks are equal, it's a draw
        cout << "Draw!" << endl;
    }
}


else if (type == 5) {
    //Flush
    int str_cur,str_high;
    for (int x = 6; x >= 2; x--) {
        if (suitC[x] == suitC[x - 1] && suitC[x - 1] == suitC[x - 2] &&
            rankC[x] > rankH[x] && rankC[x - 1] > rankH[x - 1] && rankC[x - 2] > rankH[x - 2]) {
            str_cur = rankC[x];
            break;
        }
        else if (suitH[x] == suitH[x - 1] && suitH[x - 1] == suitH[x - 2] &&
                 rankH[x] > rankC[x] && rankH[x - 1] > rankC[x - 1] && rankH[x - 2] > rankC[x - 2]) {
            str_high = rankH[x];
            break;
        }
    }
    if (str_cur > str_high) {
        highest_rank = current_rank;
    }
    else if (str_cur < str_high) {
        highest_rank = highest_rank;
    }
    else { // no flush, it's a draw
        cout << "Draw!" << endl;
    }
}

else if (type == 6) {
    //FULL HOUSE
    int str_cur1 , str_high1 ;
    int str_cur2 , str_high2 ;
    for (int m = 6; m > 1; m--) {
        if (rankC[m] == rankC[m - 1] && rankC[m - 1] == rankC[m - 2]) {
            str_cur1 = rankC[m];
            break;
        }
    }
    for (int m = 6; m > 1; m--) {
        if (rankH[m] == rankH[m - 1] && rankH[m - 1] == rankH[m - 2]) {
            str_high1 = rankH[m];
            break;
        }
    }
    if (str_cur1 > str_high1) {
        highest_rank = current_rank;
    }
    else if (str_cur1 < str_high1) {
        highest_rank = highest_rank;
    }
    else { // compare remaining cards if three of a kind ranks are equal
        for (int i = 6; i > 0; i--) {
            if (rankC[i] == rankC[i - 1]) {
                str_cur2 = rankC[i];
                break;
            }
        }
        for (int i = 6; i > 0; i--) {
            if (rankH[i] == rankH[i - 1]) {
                str_high2 = rankH[i];
                break;
            }
        }
        if (str_cur2 > str_high2) {
            highest_rank = current_rank;
        }
        else if (str_cur2 < str_high2) {
            highest_rank = highest_rank;
        }
        else { // ranks are equal, it's a draw
            cout << "Draw!" << endl;
        }
    }
}

else if (type == 7) {
    //Four of a kind
    int str_cur = -1, str_high = -1;
    for (int e = 6; e >= 3; e--) {
        if (rankC[e] == rankC[e - 1] && rankC[e - 1] == rankC[e - 2] && rankC[e - 2] == rankC[e - 3]) {
            str_cur = rankC[e];
            break;
        }
    }
    for (int e = 6; e >= 3; e--) {
        if (rankH[e] == rankH[e - 1] && rankH[e - 1] == rankH[e - 2] && rankH[e - 2] == rankH[e - 3]) {
            str_high = rankH[e];
            break;
        }
    }
    if (str_cur > str_high) {
        highest_rank = current_rank;
    }
    else if (str_cur < str_high) {
        highest_rank = highest_rank;
    }
    else { // compare remaining cards if four of a kind ranks are equal
        for (int u = 6; u >= 0; u--) {
            if (rankC[u] > rankH[u]) {
                highest_rank = current_rank;
                break;
            }
            else if (rankC[u] < rankH[u]) {
                highest_rank = highest_rank;
                break;
            }
            else if (u == 0) { // all cards are equal, it's a draw
                cout << "Draw!" << endl;
            }
        }
    }
}
}
