#pragma once

struct Animation
{
    // Index of row of the animation on the sprite sheet
    int index_row;
    int width;
    int height;
    int frames;
    int speed;

    Animation()
        : index_row(0), width(0), height(0), frames(0), speed(0) {}

    Animation(int _index, int _width, int _height, int _frames, int _speed)
        : index_row(_index), width(_width), height(_height), frames(_frames), speed(_speed)
    {
    }
};
