struct Dice
{
    int top, bottom, front, back, left, right;
    Dice(): top(1), bottom(6), front(2), back(5), left(3), right(4) {}
    Dice(int top, int bottom, int front, int back, int left, int right) : top(top), bottom(bottom), front(front), back(back), left(left), right(right) {}
    void rotate_right()
    {
        std::tie(top, right, bottom, left) = std::make_tuple(left, top, right, bottom);
    }
    void rotate_front()
    {
        std::tie(top, back, bottom, front) = std::make_tuple(front, top, back, bottom);
    }

    int encode()
    {
        int cur = 1;
        int ret = 0;
        std::vector<int> v = {top, bottom, front, back, left, right};
        for (int i = 0; i < (int)v.size(); ++i)
        {
            ret += (v[i] - 1) * cur;
            cur *= 6;
        }
        return ret;
    }
};

Dice decode(int X)
{
    int top = X % 6 + 1;
    X /= 6;
    int bottom = X % 6 + 1;
    X /= 6;
    int front = X % 6 + 1;
    X /= 6;
    int back = X % 6 + 1;
    X /= 6;
    int left = X % 6 + 1;
    X /= 6;
    int right = X % 6 + 1;
    X /= 6;
    return Dice(top, bottom, front, back, left, right);
}