#pragma once

#pragma pack(push, 1)
class opponent
{
private:
    char sign_;
public:
    explicit opponent(const char sign)
        : sign_(sign)
    {
    }

    char get_sign();
    int choose_cell ();
};
#pragma pack(pop)
