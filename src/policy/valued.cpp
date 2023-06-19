#include <cstdlib>
#include <iostream>

#include "../state/state.hpp"
#include "./valued.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Valued::get_move(State *state, int depth){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  if (state->legal_actions.empty()) {
    // 处理没有合法动作的情况
    // 可以返回一个默认的动作或者抛出异常
    // 这里简单地返回一个空动作
    return Move();
  }

  int maxval = -1e9;
  auto actions = state->legal_actions;
  Move wantedaction;
  for (auto &act : actions) {
    //int val = state->next_state(act)->evaluate();
    State *next_state = state->next_state(act);  // 获取下一个状态
    int val = next_state->evaluate();  // 获取下一个状态的评估值
    delete next_state;
    if(val > maxval) {
        maxval = val;
        std::cout << maxval << std::endl;
        wantedaction = act;
    }
  }
  return wantedaction;
}