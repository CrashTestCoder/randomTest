#include<iostream>
#include<vector>

template<typename T, typename U> constexpr bool const HasSameRank = T::rank == U::rank;
template<typename T, typename U> concept isSame = requires T==U;

template<typename grid_space> requires
    //requires () { grid_space::space_type; } &&
    requires () { grid_space::rank; }
class point
{
public:
    static int const rank = grid_space::rank;
    typename grid_space::space_type pnt[grid_space::rank];
    template<typename... dims> requires HasSameRank<point, grid_space>
    constexpr point(dims... dim) :
        pnt {(dim , ...)}
    {
    }
    constexpr int get_idx() const
    {
        int idx = 0;
        for(auto const& dim : pnt)
            idx *= dim;
        return idx;
    }
    constexpr std::vector<point> get_surrounding()
    {

    }
};

template<typename block_type, int... dims>
class Grid
{
    block_type grid_space[(dims * ...)];
public:
    using space_type = block_type;
    constexpr static int const dimentions[sizeof...(dims)] = {(dims , ...)};
    constexpr static int const rank = sizeof...(dims);
    constexpr Grid(block_type const& default_value)
    {
        for(auto& point : grid_space)
            point = default_value;        
    }
    template<typename T> requires 
    constexpr space_type& get(point<Grid<space_type,dims...>> coordinates)
    {
        return grid_space[coordinates.get_idx()];
    }
};


int main()
{
    Grid<int, 4, 4> grid(1);
    std::cout << grid.get({2,2}) << '\n';
}