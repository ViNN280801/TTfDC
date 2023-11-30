#include <iostream>
#include <memory>
#include <concepts>

/**
 * @brief Concept that checks if variable has output operator
 * @tparam a variable to check
 * @param os output stream
 */
template <typename T>
concept Printable = requires(T a, std::ostream &os) {
    {
        os << a
    } -> std::same_as<std::ostream &>;
};

/**
 * @brief Doubly linked list with single function of adding element into the beginning
 * @tparam T type of the data
 */
template <typename T>
class List
{
    // Checking concepts which are applies to 'T' type
    static_assert(std::is_copy_assignable_v<T> && std::is_move_assignable_v<T> &&
                  std::equality_comparable<T> && std::swappable<T>);

public:
    /// @brief Ctor
    explicit List() : m_root(nullptr) {}

    /**
     * @brief Adds element to the beginning of the list.
     * @tparam value value to add.
     */
    void push_front(T const &value)
    {
        auto node{std::make_unique<Node>(value)};
        node->m_next = std::move(m_root);
        m_root = std::move(node);
    }

    /**
     * @brief Adds element to the beginning of the list (move version).
     * @tparam value value to add.
     */
    void push_front(T &&value)
    {
        auto node{std::make_unique<Node>(std::move(value))};
        node->m_next = std::move(m_root);
        m_root = std::move(node);
    }

    /// @brief Prints all data from the list into the terminal
    void print() const
    {
        static_assert(Printable<T>, "Type 'T' has to be printable");

        for (auto node{m_root.get()}; node != nullptr; node = node->m_next.get())
            std::cout << node->m_data << ' ';
        std::endl(std::cout);
    }

private:
    /// @brief Describes each node in the list
    struct Node
    {
        /// @brief Ctor
        explicit Node() : m_data(0), m_next(nullptr) {}

        /// @brief Copy ctor
        explicit Node(T const &data) : m_data(data), m_next(nullptr) {}

        /// @brief Move ctor
        explicit Node(T &&data) : m_data(std::move(data)), m_next(nullptr) {}

        T m_data;                     // Data in the node
        std::unique_ptr<Node> m_next; // Ptr to the next node
    };
    std::unique_ptr<Node> m_root; // Ptr to the head element
};

int main()
{
    List<int> l;
    l.push_front(10);
    l.push_front(-134);
    l.push_front(3);

    l.print();

    return EXIT_SUCCESS;
}
