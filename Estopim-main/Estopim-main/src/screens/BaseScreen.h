#pragma once

#include "../core/GameState.h"

class BaseScreen {

protected:

    bool needsRender = true;

public:

    virtual void onEnter() = 0;

    virtual void onExit() = 0;

    virtual void update() = 0;

    virtual void render() = 0;

    virtual GameState getState() = 0;

    bool shouldRender() {

        return needsRender;
    }

    void rendered() {

        needsRender = false;
    }

    virtual ~BaseScreen() {}
};