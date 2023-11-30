#ifndef DICTIONARY_HPP
#define DICTIONARY_HPP

#include <concepts>
#include <exception>
#include <utility>
#include <unordered_map>

/**
 * @brief Primary template handles types that have no nested ::type member.
 * This struct assumes that the type 'T' is not copyable by default (others are similar)
 */
template <typename T, typename = std::void_t<>>
struct is_copyable : std::false_type
{
};

template <typename T, typename = std::void_t<>>
struct is_equality_comparable : std::false_type
{
};

template <typename T, typename = std::void_t<>>
struct is_copy_constructible : std::false_type
{
};

template <typename T, typename = std::void_t<>>
struct is_hashable : std::false_type
{
};

/**
 * @brief Checker for type 'T' is copyable by attempting to assign const lvalue ref to 'T'
 * to lvalue ref to 'T' type. If this assignment is valid - it means that the 'T' type is copyable,
 * then specialization sets "is_copyable<T>" to "true".
 * "std::declval<T>()" creates rvalue ref to 'T' type.
 * "decltype(...)" determines the type of the expression.
 * "std::void_t" discards the types of its template args and produce 'void' as the result if expr is valid.
 */
template <typename T>
struct is_copyable<T, std::void_t<decltype(std::declval<T &>() = std::declval<T const &>())>> : std::true_type
{
};

template <typename T>
struct is_equality_comparable<T, std::void_t<decltype(std::declval<T>() == std::declval<T>())>> : std::true_type
{
};

template <typename T>
struct is_copy_constructible<T, std::void_t<decltype(T(std::declval<const T &>()))>> : std::true_type
{
};

template <typename T>
struct is_hashable<T, std::void_t<decltype(std::declval<std::hash<T>>()(std::declval<T>()))>> : std::true_type
{
};

/// @brief Creating more concise template to check the type of the value
template <typename T>
constexpr bool is_copyable_v = is_copyable<T>::value;

template <typename T>
constexpr bool is_equality_comparable_v = is_equality_comparable<T>::value;

template <typename T>
constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;

template <typename T>
constexpr bool is_hashable_v = is_hashable<T>::value;

/// @brief Interface of the dictionary
template <class Key, class Value>
class IDictionary
{
public:
    /* === Using assertions to check template types on corresponding with some requirements === */
    static_assert(is_copyable_v<Key>, "Key has to be copyable");
    static_assert(is_equality_comparable_v<Key>, "Key has to be equality comparable");
    static_assert(is_hashable_v<Key>, "Key has to be hashable");
    static_assert(is_copy_constructible_v<Value>, "Value has to be copy constructible");

    virtual ~IDictionary() = default;

    virtual Value const &get(Key const &key) const = 0;
    virtual void set(Key const &key, Value const &value) = 0;
    virtual bool is_set(Key const &key) const = 0;
};

/// @brief Interface that had to throw an exception if key is not found
template <class Key>
class IDictionaryKeyNotFoundException : public std::exception
{
public:
    /* === Using assertions to check template types on corresponding with some requirements === */
    static_assert(is_copyable_v<Key>, "Key has to be copyable");
    static_assert(is_equality_comparable_v<Key>, "Key has to be equality comparable");
    static_assert(is_hashable_v<Key>, "Key has to be hashable");

    virtual Key const &get_key() const noexcept = 0;
};

/// @brief Dictionary class that implemented with the STL dictionary container within (unordered)
template <class Key, class Value>
class Dictionary : IDictionary<Key, Value>
{
public:
    // Ctor
    explicit Dictionary() {}

    /**
     * @brief Getter for value
     * @tparam key key by which the value will be searched in the dictionary
     * @return Value by key
     */
    Value const &get(Key const &key) const override;

    /**
     * @brief Replaces one value in dictionary that is located by specified key with the new value
     * @tparam key where to search
     * @tparam value new value
     */
    void set(Key const &key, Value const &value) override;

    /**
     * @brief Checker for key: is this key already used in dictionary
     * @tparam key key to search
     * @return "true" if key is already in use of the dictionary, otherwise "false"
     */
    bool is_set(Key const &key) const override;

    // Dtor
    virtual ~Dictionary() {}

private:
    std::unordered_map<Key, Value> m_data; // Using STL dictionary container to store data
};

/// @brief Class that throws exception if some key (that can't be found) in the dictionary causes this exception
template <typename Key>
class DictionaryKeyNotFoundException : IDictionaryKeyNotFoundException<Key>
{
public:
    /// @brief Ctor with template arg of the key
    explicit DictionaryKeyNotFoundException(Key const &key) : m_key(key) {}

    /**
     * @brief Overrided version of method "std::exception::what()"
     * @return Description of the exception message. Why is occurs
     */
    const char *what() const noexcept override { return "The key can't be found in the dictionary\n"; }

    /**
     * @brief Accessor for the key
     * @return Key that causes throwing an exception
     */
    constexpr Key const &get_key() const noexcept override { return m_key; }

private:
    Key m_key; // Key of the dictionary
};

#include "dictionary_impl.hpp"

#endif // !DICTIONARY_HPP
