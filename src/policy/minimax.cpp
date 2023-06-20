#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cmath>
#include <algorithm>
#include <map>

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
        int value = minimax(nextState, depth - 1) * -1;
        //delete nextState;

        if (value > bestValue) {
            bestValue = value;
            bestMove = action;
        }
    }
    return bestMove;
}


int Minimax::minimax(State* state ,int depth) {
    /*if(!state->legal_actions.size())
        state->get_legal_actions();

    auto actions = state->legal_actions;  
    if (depth <= 0 || actions.empty()) {
        return state->evaluate();
    }
    State *next;
    int retVal = -2e9;
    for (auto &i : actions) {
        next = state->next_state(i);
        retVal = std::max(retVal, -1 * minimax(next, depth - 1));
    }
    return retVal;
    */
    if(!state->legal_actions.size())
        state->get_legal_actions();
    auto actions = state->legal_actions;
    if (depth <= 0 || actions.empty()) {
        return state->evaluate();
    }
    else {
        int value = -2e9;
        auto actions = state->legal_actions;
        for ( auto act : actions) {
            State *next_state = state->next_state(act);
            value = std::max(value, minimax(next_state, depth-1) * -1);
            //delete next_state;
        }
        return value;
    }
}

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