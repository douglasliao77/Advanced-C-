#include <cassert>
#include <string>
#include <vector>
#include <unordered_map>

template <typename Key, typename Value>
class Sparse_Map
{
public:

    class Iterator
    {
        public: 
            using value_type = std::pair<Key, Value>;
            using reference = std::pair<Key const&, Value&>;
            using iterator_category = std::bidirectional_iterator_tag;
            
            // Pre-increment
            Iterator& operator++()
            {
                iter = iter + 1;
                return *this;
            } 

            // Post-increment
            Iterator operator++(int) 
            {
                Iterator tmp { *this };
                ++(*this);
                return tmp;
            }

            // Pre-decrement
            Iterator& operator--() 
            {
                iter = iter - 1;
                return *this;
            } 

            // Post-decrement
            Iterator operator--(int) 
            {
                Iterator tmp { *this };
                --(*this);
                return tmp;
            }

            reference operator*()
            {
                auto&& pair = *iter;
                return { pair.first, pair.second };
            }

            bool operator==(Iterator const& other) const
            {
                return iter == other.iter;
            }

            bool operator!=(Iterator const& other) const
            {
                return !(iter == other.iter);
            }


        private: 
            friend Sparse_Map<Key, Value>;

            Iterator(typename std::vector<std::pair<Key, Value>>::iterator iter)
                : iter { iter }
            {
            }

            typename std::vector<std::pair<Key,Value>>::iterator iter;
    };
    
    void insert(Key const& key, Value const& value)
    {
        table[key] = data.size();
        data.push_back({ key, value });
    }

    void erase(Key const& key)
    {
        std::size_t index { table[key] };
        std::swap(data[index], data.back());
        data.pop_back();

        table[data[index].first] = index;
        
        for (auto it = table.begin(); it != table.end();) 
        {
            if (it->first == key)
            {
                it = table.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }

    Value& at(Key const& key)
    {
        return data[table[key]].second;
    }

    std::size_t size() const
    {
        return data.size();
    }

    Iterator begin()
    {
        return { data.begin() };
    }

    Iterator end()
    {
        return { data.end() };
    }
    
private:
    std::vector<std::pair<Key, Value>> data { };
    std::unordered_map<Key, std::size_t> table { };
};

int main()
{
    Sparse_Map<std::string, int> map { };
    
    map.insert("def", 2);
    map.insert("abc", 1);
    map.insert("ghi", 3);

    assert( map.at("abc") == 1 );
    assert( map.at("def") == 2 );
    assert( map.at("ghi") == 3 );

    map.erase("def");
    assert( map.size() == 2 );

    map.insert("jkl", 4);

    assert( map.at("abc") == 1 );
    assert( map.at("ghi") == 3 );
    assert( map.at("jkl") == 4 );

    assert( map.size() == 3 );
        
    // looping should work once the iterators have been created
    // note that it should be possible to modify value, but not key
    for (auto&& [key, value] : map)
        ++value;

    // make sure that modifying value in the previous loop worked
    assert( map.at("abc") == 2 );
    assert( map.at("ghi") == 4 );
    assert( map.at("jkl") == 5 );
    
    auto it = map.begin();

    // test that all increments and decrements exist and work
    
    assert( it++ == map.begin() );
    assert( --it == map.begin() );

    it = map.end();
    assert( it-- == map.end() );
    assert( ++it == map.end() );

    --(--(--it));
    assert( it == map.begin() );

    ++(++(++it));
    assert( it == map.end() );

}