#pragma once

#pragma pack(push, 1)
class player
{
private:
    char sign_;
public:
    explicit player(char sign)
        : sign_(sign)
    {
    }
    char get_sign();
    int get_pos();
};
#pragma pack(pop)
