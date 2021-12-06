#ifndef VIEW_H
#define VIEW_H
class View
{
protected:
    void (*mouse_animation)(int x, int y);
    void (*zoom_wheel)(int button, int state, int x, int y);
    void (*mouse_move)(int x, int y);
};
#endif