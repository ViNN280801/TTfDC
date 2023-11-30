#ifndef DICTIONARY_IMPL_HPP
#define DICTIONARY_IMPL_HPP

#include <iterator>

template <typename Key, typename Value>
Value const &Dictionary<Key, Value>::get(Key const &key) const
{
    // If there is no such key - throw the exception with the certain class
    if (not is_set(key))
        throw DictionaryKeyNotFoundException<Key>(key);

    // Otherwise, returning requested value
    return m_data.at(key);
}

template <typename Key, typename Value>
void Dictionary<Key, Value>::set(Key const &key, Value const &value) { m_data[key] = value; }

template <typename Key, typename Value>
bool Dictionary<Key, Value>::is_set(Key const &key) const { return m_data.find(key) != std::cend(m_data); }

#endif // !DICTIONARY_IMPL_HPP
