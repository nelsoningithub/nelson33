#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cmath>
#include <algorithm>

#include "../config.hpp"
#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Minimax::get_move(State *state, int depth) {
    if (!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    Move bestMove;
    int bestValue = -1e9;   
    for (auto& action : actions) {
        State* nextState = state->next_state(action);
        int value = minimax(nextState, depth - 1, true) * -1;
//        delete nextState;

        if (value > bestValue) {
            bestValue = value;
            bestMove = action;
        }
    }
    return bestMove;
}
    


    
    /*if(!state->legal_actions.size())
        state->get_legal_actions();
    if(state_player_start == 100) {
        state_player_start = state->player;
    }
  
    auto actions = state->legal_actions;
    Move wantedaction;

    if(state_player_start == state->player)
        int val = Minimax::minimax(state, depth - 1, 1); // 获取下一个状态的评估值 
    else if(state_player_start != state->player)
        int val = Minimax::minimax(state, depth - 1, 0);// 获取下一个状态的评估值
    
    for (auto &act : actions) {
        //int val = state->next_state(act)->evaluate();
        State *next_state = state->next_state(act);  // 获取下一个状态
        if(state_player_start == state->player) {
            int val = Minimax::minimax(state, depth - 1, 1); // 获取下一个状态的评估值 
            int next_state_value = Minimax::minimax(next_state, depth - 2, 0);
            if(val == next_state_value) {
               wantedaction = act;
            } 
        }
        else if(state_player_start != state->player){
            int val = Minimax::minimax(state, depth - 1, 0);// 获取下一个状态的评估值
            int next_state_value = Minimax::minimax(next_state, depth - 2, 1);
            if(val == next_state_value) {
                wantedaction = act;
            } 
        }
        delete next_state;
    }

    return wantedaction;
    */


int Minimax::minimax(State* state ,int depth, bool maximizingPlayer) {
    if (!state->legal_actions.size())
        state->get_legal_actions();
    if(depth == 0) {
        return state->evaluate();
    }
    else if(maximizingPlayer) {
        int value = -1e9;
        auto actions = state->legal_actions;
        for ( auto act : actions) {
            State *next_state = state->next_state(act);
            value = std::max(value, minimax(next_state, depth-1, true) * -1);
//            delete next_state;
        }
        return value;
    }
    /*else if(maximizingPlayer) {
        int value = -1e9;
        auto actions = state->legal_actions;
        for ( auto act : actions) {
            State *next_state = state->next_state(act);
            value = std::max(value, minimax(next_state, depth-1, false));
            delete next_state;
        }
        return value;
    }
    else {
        int value = 1e9;
        auto actions = state->legal_actions;
        for ( auto act : actions) {
            State *next_state = state->next_state(act);
            value = std::min(value, minimax(next_state, depth-1, true));
            delete next_state;
        }
        return value;
    }*/
}


/*Move Minimax::get_move(State *state, int depth){
    if(!state->legal_actions.size())
        state->get_legal_actions();
  
    auto actions = state->legal_actions;
    Move wantedaction;
    int maxval = -1e9;
    int minval = 1e9;

    for (auto &act : actions) {
        //int val = state->next_state(act)->evaluate();
        State *next_state = state->next_state(act);  // 获取下一个状态
        int val = Minimax::minimax(state, depth - 1, state->player == 0 ? 1 : 0);  // 获取下一个状态的评估值
        delete next_state;
        
        if(!state->player) {
            if(val > maxval) {
                maxval = val;
                wantedaction = act;
            }
        }
        else {
            if(val < minval) {
                minval = val;
                wantedaction = act;
            }
        }
    }

    return wantedaction;

}

int Minimax::minimax(State* state ,int depth, bool maximizingPlayer) {
    if(depth == 0 || state->legal_actions.size()) {
        return state->evaluate();
    }
    else if(maximizingPlayer) {
        int value = -1e9;
        auto actions = state->legal_actions;
        for ( auto act : actions) {
            State *next_state = state->next_state(act);
            value = std::max(value, minimax(next_state, depth-1, false));
            delete next_state;
        }
        return value;
    }
    else {
        int value = 1e9;
        auto actions = state->legal_actions;
        for ( auto act : actions) {
            State *next_state = state->next_state(act);
            value = std::min(value, minimax(next_state, depth-1, true));
            delete next_state;
        }
        return value;
    }
}*/

//sudocode
/*function minimax(node, depth, maximizingPlayer) is
    if depth = 0 or node is a terminal node then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, minimax(child, depth − 1, FALSE))
        return value
    else (* minimizing player *)
        value := +∞
        for each child of node do
            value := min(value, minimax(child, depth − 1, TRUE))
        return value
        */