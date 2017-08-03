//
// Created by william on 23/02/17.
//

#ifndef NETVIZGL_DRAGNODE_H
#define NETVIZGL_DRAGNODE_H

#include <algorithm>
#include <iostream>
#include "Command.h"
#include "glwindow.h"

class DragVertex : public Command {
 private:
  GLWindow *window;
 public:
  DragVertex(GLWindow *window) : window(window) {}

  void execute() override {
    if (window->getSelectedNode()) {
      window->getSelectedNode()->posX -= window->getMouseDiffX() * .145 * window->getTranslateZ();
      window->getSelectedNode()->posY += window->getMouseDiffY() * .145 * window->getTranslateZ();
    }
  }
};

#endif //NETVIZGL_DRAGNODE_H
