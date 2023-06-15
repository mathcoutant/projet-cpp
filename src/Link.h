#pragma once

class Link
{
public:
    /*
    0 = player
    1 = enemy
    2 = tomb
    */
    int type;
    void* pointer;

    Link(int t, void* p);
};