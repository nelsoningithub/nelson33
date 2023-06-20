#include <iostream>
#include <sstream>
#include <cstdint>
#include <cmath>

#include "./state.hpp"
#include "../config.hpp"


/**
 * @brief evaluate the state
 * 
 * @return int 
 */

int State::indanger(int i, int j) {
  //pawn
  const int px[] = {1,1,-1,-1};
  const int py[] = {-1,-1,1,1};
  //rook
  const int rx[] = {0,0,1,-1};
  const int ry[] = {1,-1,0,0};
  //knight
  const int kx[] = {1,2,2,1,-1,-2,-2,-1};
  const int ky[] = {-2,-1,1,2,2,1,-1,-1};
  //bishop
  const int bx[] = {1,1,-1,-1};
  const int by[] = {1,-1,1,-1};
  //queen
  const int qx[] = {1,1,1,0,-1,-1,-1,0};
  const int qy[] = {-1,0,1,1,1,0,-1,-1};
  for (int c = 0; c < 4; c++) {
    int tc = i + px[c];
    int tr = j + py[c];

    if(tc < 0 || tc > 5 || tr < 0 || tr > 4) continue;

    if(board.board[1-player][tc][tr] == 1)
      return 1;
  }
  for (int c = 0; c < 4; c++) {
    int tc = i + rx[c];
    int tr = j + ry[c];
    
    while (true) {
      if(tc < 0 || tc > 5 || tr < 0 || tr > 4) break;  
      if(board.board[player][tc][tr] != 0) break;
      if(board.board[1-player][tc][tr] == 2) return 1;
      tc += rx[c];
      tr += ry[c];
    }
  }
  for (int c = 0; c < 8; c++) {
    int tc = i + kx[c];
    int tr = j + ky[c];
    
    if(tc < 0 || tc > 5 || tr < 0 || tr > 4) continue;

    if(board.board[1-player][tc][tr] == 3){
      return 1;
    }
  }
  for (int c = 0; c < 4; c++) {
    int tc = i + bx[c];
    int tr = j + by[c];
    
    while (true) {
      if(tc < 0 || tc > 5 || tr < 0 || tr > 4) break;  
      if(board.board[player][tc][tr] != 0) break;
      if(board.board[1-player][tc][tr] == 4) return 1;
      tc += bx[c];
      tr += by[c];
    }
  }
  for (int c = 0; c < 8; c++) {
    int tc = i + qx[c];
    int tr = j + qy[c];
    
    while (true) {
      if(tc < 0 || tc > 5 || tr < 0 || tr > 4) break;  
      if(board.board[player][tc][tr] != 0) break;
      if(board.board[1-player][tc][tr] == 5) return 1;
      tc += qx[c];
      tr += qy[c];
    }
  }
  for (int c = 0; c < 8; c++) {
    int tc = i + qx[c];
    int tr = j + qy[c];

    if(tc < 0 || tc > 5 || tr < 0 || tr > 4) continue;

    if(board.board[1-player][tc][tr] == 6){
      return 1;
    }
  }
  return 0;
}

int State::evaluate(){
      /*int value_self = 0;
      int value_oppo = 0;

      
      //pawn
      const int px[] = {1,1,-1,-1};
      const int py[] = {-1,-1,1,1};
      //rook
      const int rx[] = {0,0,1,-1};
      const int ry[] = {1,-1,0,0};
      //knight
      const int kx[] = {1,2,2,1,-1,-2,-2,-1};
      const int ky[] = {-2,-1,1,2,2,1,-1,-1};
      //bishop
      const int bx[] = {1,1,-1,-1};
      const int by[] = {1,-1,1,-1};
      //queen
      const int qx[] = {1,1,1,0,-1,-1,-1,0};
      const int qy[] = {-1,0,1,1,1,0,-1,-1};
      const int piece_scores[] = {0, 20, 60, 70, 80, 200, 1000000000};
      int now_piece = 0;

      for (int i = 0; i < BOARD_H; i++) {
        for (int j = 0; j < BOARD_W; j++) {
          //now_piece = board.board[player][i][j];
          //value_self += piece_scores[now_piece];

          //pawn
          if(now_piece == 1) {
            if(indanger(i,j)) 
              value_self -= piece_scores[now_piece];
            for (int c = 0; c < 4; c++) {
              int tc = i + px[c];
              int tr = j + py[c];

              if(tc < 0 || tc > 5 || tr < 0 || tr > 4) continue;
              if(board.board[player][tc][tr] == 1) {
                value_self += 50;
              }
            }
          }
          //rook
          if(now_piece == 2) {
            if(indanger(i,j)) 
              value_self -= piece_scores[now_piece];
            for (int c = 0; c < 4; c++) {
              int tc = i + rx[c];
              int tr = j + ry[c];

              while (true) {
                if(tc < 0 || tc > 5 || tr < 0 || tr > 4) break;  
                if(board.board[player][tc][tr] != 0){
                  if(indanger(tc,tr)) {
                    value_self += 50;
                    break;
                  }
                }
                tc += rx[c];
                tr += ry[c];
                }
            }
          }
          //knight
          if(now_piece == 3) {
            if(indanger(i,j)) 
              value_self -= piece_scores[now_piece];
            for (int c = 0; c < 8; c++) {
              int tc = i + kx[c];
              int tr = j + ky[c];

              if(tc < 0 || tc > 5 || tr < 0 || tr > 4) continue;
              if(board.board[player][tc][tr] != 0) {
                if(indanger(tc,tr)) {
                  value_self += 50;
                }
              }
            }
          }
          //bishop
          if(now_piece == 4) {
            if(indanger(i,j)) 
              value_self -= piece_scores[now_piece];
            for (int c = 0; c < 4; c++) {
                int tc = i + bx[c];
                int tr = j + by[c];

                while (true) {
                  if(tc < 0 || tc > 5 || tr < 0 || tr > 4) break;  
                  if(board.board[player][tc][tr] != 0){
                    if(indanger(tc,tr)) {
                      value_self += 50;
                      break;
                    }
                  }
                  tc += bx[c];
                  tr += by[c];
                }
            }
          }
            //queen
            if(now_piece == 5) {
              if(indanger(i,j)) 
                value_self -= piece_scores[now_piece];
              for (int c = 0; c < 8; c++) {
                int tc = i + qx[c];
                int tr = j + qy[c];

                while (true) {
                  if(tc < 0 || tc > 5 || tr < 0 || tr > 4) break;  
                  if(board.board[player][tc][tr] != 0){
                    if(indanger(tc,tr)) {
                      value_self += 50;
                      break;
                    }
                  }
                  tc += qx[c];
                  tr += qy[c];
                }
              }
            }
            if(now_piece == 6) {
              if(indanger(i,j)) 
                value_self -= piece_scores[now_piece];
            }
            
            now_piece = board.board[1-player][i][j];
            value_oppo += piece_scores[now_piece];
          }
        }
    
      return value_self - value_oppo;
      */
      int value_self = 0;
      int value_oppo = 0;

      //pawn
      const int px[] = {1,1,-1,-1};
      const int py[] = {-1,-1,1,1};
      //auto self_board_self = this->board.board[player];
      //auto self_board_opponent = this->board.board[1-player];
      const int piece_scores[] = {0, 1, 3, 3, 3, 9, 1000000000};
      const int piece_scores[] = {0, 5, 7, 7, 7, 13, 1000000000};
    
      for (int i = 0; i < BOARD_H; i++) {
        for (int j = 0; j < BOARD_W; j++) {
          int now_piece = board.board[player][i][j];
          value_self += piece_scores[now_piece];

          if(now_piece == 1) {
            for (int c = 0; c < 4; c++) {
              int tc = i + px[c];
              int tr = j + py[c];

              if(tc < 0 || tc > 5 || tr < 0 || tr > 4) continue;
              if(board.board[player][tc][tr]) {
                value_self += 2;
              }
            }
          }

          now_piece = board.board[1-player][i][j];
          value_oppo += piece_scores[now_piece];
        }
      }
    
      return value_self - value_oppo;
}
//


/*int State::evaluate(){
    int value_white = 0;
    int value_black = 0;

    auto self_board_white = this->board.board[0];
    const int piece_scores_white[] = {0, 1, 5, 3, 3, 9, 1000000000};
 
    for (int i = 0; i < BOARD_H; i++) {
      for (int j = 0; j < BOARD_W; j++) {
        int now_piece = self_board_white[i][j];
        value_white += piece_scores_white[now_piece];
      }
    }

    const int piece_scores_black[] = {0, -1, -5, -3, -3, -9, -1000000000};
    auto self_board_black = this->board.board[1];

    for (int i = 0; i < BOARD_H; i++) {
      for (int j = 0; j < BOARD_W; j++) {
        int now_piece = self_board_black[i][j];
        value_black += piece_scores_black[now_piece];

      }
    }
    return value_white + value_black;
}*/


/**
 * @brief return next state after the move
 * 
 * @param move 
 * @return State* 
 */
State* State::next_state(Move move){
  Board next = this->board;
  Point from = move.first, to = move.second;
  
  int8_t moved = next.board[this->player][from.first][from.second];
  //promotion for pawn
  if(moved == 1 && (to.first==BOARD_H-1 || to.first==0)){
    moved = 5;
  }
  if(next.board[1-this->player][to.first][to.second]){
    next.board[1-this->player][to.first][to.second] = 0;
  }
  
  next.board[this->player][from.first][from.second] = 0;
  next.board[this->player][to.first][to.second] = moved;
  
  State* next_state = new State(next, 1-this->player);
  
  if(this->game_state != WIN)
    next_state->get_legal_actions();
  return next_state;
}


static const int move_table_rook_bishop[8][7][2] = {
  {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7}},
  {{0, -1}, {0, -2}, {0, -3}, {0, -4}, {0, -5}, {0, -6}, {0, -7}},
  {{1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0}},
  {{-1, 0}, {-2, 0}, {-3, 0}, {-4, 0}, {-5, 0}, {-6, 0}, {-7, 0}},
  {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}, {6, 6}, {7, 7}},
  {{1, -1}, {2, -2}, {3, -3}, {4, -4}, {5, -5}, {6, -6}, {7, -7}},
  {{-1, 1}, {-2, 2}, {-3, 3}, {-4, 4}, {-5, 5}, {-6, 6}, {-7, 7}},
  {{-1, -1}, {-2, -2}, {-3, -3}, {-4, -4}, {-5, -5}, {-6, -6}, {-7, -7}},
};
static const int move_table_knight[8][2] = {
  {1, 2}, {1, -2},
  {-1, 2}, {-1, -2},
  {2, 1}, {2, -1},
  {-2, 1}, {-2, -1},
};
static const int move_table_king[8][2] = {
  {1, 0}, {0, 1}, {-1, 0}, {0, -1}, 
  {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
};


/**
 * @brief get all legal actions of now state
 * 
 */
void State::get_legal_actions(){
  // [Optional]
  // This method is not very efficient
  // You can redesign it
  this->game_state = NONE;
  std::vector<Move> all_actions;
  auto self_board = this->board.board[this->player];
  auto oppn_board = this->board.board[1 - this->player];
  
  int now_piece, oppn_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece=self_board[i][j])){
        // std::cout << this->player << "," << now_piece << ' ';
        switch (now_piece){
          case 1: //pawn
            if(this->player && i<BOARD_H-1){
              //black
              if(!oppn_board[i+1][j] && !self_board[i+1][j])
                all_actions.push_back(Move(Point(i, j), Point(i+1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i+1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i+1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i+1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }else if(!this->player && i>0){
              //white
              if(!oppn_board[i-1][j] && !self_board[i-1][j])
                all_actions.push_back(Move(Point(i, j), Point(i-1, j)));
              if(j<BOARD_W-1 && (oppn_piece=oppn_board[i-1][j+1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j+1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
              if(j>0 && (oppn_piece=oppn_board[i-1][j-1])>0){
                all_actions.push_back(Move(Point(i, j), Point(i-1, j-1)));
                if(oppn_piece==6){
                  this->game_state = WIN;
                  this->legal_actions = all_actions;
                  return;
                }
              }
            }
            break;
          
          case 2: //rook
          case 4: //bishop
          case 5: //queen
            int st, end;
            switch (now_piece){
              case 2: st=0; end=4; break; //rook
              case 4: st=4; end=8; break; //bishop
              case 5: st=0; end=8; break; //queen
              default: st=0; end=-1;
            }
            for(int part=st; part<end; part+=1){
              auto move_list = move_table_rook_bishop[part];
              for(int k=0; k<std::max(BOARD_H, BOARD_W); k+=1){
                int p[2] = {move_list[k][0] + i, move_list[k][1] + j};
                
                if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) break;
                now_piece = self_board[p[0]][p[1]];
                if(now_piece) break;
                
                all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
                
                oppn_piece = oppn_board[p[0]][p[1]];
                if(oppn_piece){
                  if(oppn_piece==6){
                    this->game_state = WIN;
                    this->legal_actions = all_actions;
                    return;
                  }else
                    break;
                };
              }
            }
            break;
          
          case 3: //knight
            for(auto move: move_table_knight){
              int x = move[0] + i;
              int y = move[1] + j;
              
              if(x>=BOARD_H || x<0 || y>=BOARD_W || y<0) continue;
              now_piece = self_board[x][y];
              if(now_piece) continue;
              all_actions.push_back(Move(Point(i, j), Point(x, y)));
              
              oppn_piece = oppn_board[x][y];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
          
          case 6: //king
            for(auto move: move_table_king){
              int p[2] = {move[0] + i, move[1] + j};
              
              if(p[0]>=BOARD_H || p[0]<0 || p[1]>=BOARD_W || p[1]<0) continue;
              now_piece = self_board[p[0]][p[1]];
              if(now_piece) continue;
              
              all_actions.push_back(Move(Point(i, j), Point(p[0], p[1])));
              
              oppn_piece = oppn_board[p[0]][p[1]];
              if(oppn_piece==6){
                this->game_state = WIN;
                this->legal_actions = all_actions;
                return;
              }
            }
            break;
        }
      }
    }
  }
  //std::cout << "\n";
  this->legal_actions = all_actions;
}


const char piece_table[2][7][5] = {
  {" ", "♙", "♖", "♘", "♗", "♕", "♔"},
  {" ", "♟", "♜", "♞", "♝", "♛", "♚"}
};
/**
 * @brief encode the output for command line output
 * 
 * @return std::string 
 */
std::string State::encode_output(){
  std::stringstream ss;
  int now_piece;
  for(int i=0; i<BOARD_H; i+=1){
    for(int j=0; j<BOARD_W; j+=1){
      if((now_piece = this->board.board[0][i][j])){
        ss << std::string(piece_table[0][now_piece]);
      }else if((now_piece = this->board.board[1][i][j])){
        ss << std::string(piece_table[1][now_piece]);
      }else{
        ss << " ";
      }
      ss << " ";
    }
    ss << "\n";
  }
  return ss.str();
}


/**
 * @brief encode the state to the format for player
 * 
 * @return std::string 
 */
std::string State::encode_state(){
  std::stringstream ss;
  ss << this->player;
  ss << "\n";
  for(int pl=0; pl<2; pl+=1){
    for(int i=0; i<BOARD_H; i+=1){
      for(int j=0; j<BOARD_W; j+=1){
        ss << int(this->board.board[pl][i][j]);
        ss << " ";
      }
      ss << "\n";
    }
    ss << "\n";
  }
  return ss.str();
}