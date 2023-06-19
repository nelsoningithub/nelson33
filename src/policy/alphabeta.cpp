#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <map>

#include "../config.hpp"
#include "../state/state.hpp"
#include "./alphabeta.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

Move Alphabeta::get_move(State *state, int depth) {
    
    /*if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    std::map<int, Move> next_move;
    State *next;
    int maxVal = -2e9;
    int curVal;
    for (auto &i : actions) {
        next = state->next_state(i);
        curVal = -1 * minimax(next, depth - 1);
        next_move.insert({curVal, i});
        maxVal = std::max(maxVal, curVal);
    }
    return next_move[maxVal];
    */
    
    if (!state->legal_actions.size())
        state->get_legal_actions();
    
    auto actions = state->legal_actions;
    Move bestMove = state->legal_actions[0];
    int bestValue = -2e9;   
    
    for (auto& action : actions) {
        State* nextState = state->next_state(action);
        int value = alphabeta(nextState, depth - 1, -2e9, 2e9, false);
        //delete nextState;

        if (value > bestValue) {
            bestValue = value;
            bestMove = action;
        }
    }
    return bestMove;
    //
}


int Alphabeta::alphabeta(State* state ,int depth ,int a ,int b, bool maximizingPlayer) {
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    if (depth <= 0 || actions.empty()) {
        return state->evaluate();
    }
    else if(maximizingPlayer){
        int value = -2e9;
        auto actions = state->legal_actions;
        for ( auto act : actions) {
            State *next_state = state->next_state(act);
            value = std::max(value, alphabeta(next_state, depth - 1, a, b, false) * -1);
            //delete next_state;
            a = std::max(a, value);
            if (a >= b )
                break;
        }
        return value;
    }
    else {
        int value = 2e9;
        auto actions = state->legal_actions;
        for ( auto act : actions) {
            State *next_state = state->next_state(act);
            value = std::min(value, alphabeta(next_state, depth - 1, a, b, true));
            //delete next_state;
            b = std::min(b, value);
            if (b <= a)
                break;
        }
        return value * -1;
    }
}

/*function alphabeta(node, depth, α, β, maximizingPlayer) is
    if depth == 0 or node is terminal then
        return the heuristic value of node
    if maximizingPlayer then
        value := −∞
        for each child of node do
            value := max(value, alphabeta(child, depth − 1, α, β, FALSE))
            α := max(α, value)
            if a >= β then
                break (* β cutoff *)
        return value
    else
        value := +∞
        for each child of node do
            value := min(value, alphabeta(child, depth − 1, α, β, TRUE))
            β := min(β, value)
            if B <= α then
                break (* α cutoff *)
        return value*/
