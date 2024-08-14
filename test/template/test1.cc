#include <iostream>
#include <algorithm>

template <typename Container, typename T, typename Finder = std::find<typename Container::const_iterator, T>>
typename Container::size_type findInContainer(const Container&amp; c, const T&amp; value) {
    auto it=Finder(std::begin(c), std::end(c), value);
    return it &#61;&#61; std::end(c) ? Container::npos : std::distance(std::begin(c), it);
}

int main() {

    return 0;
}
