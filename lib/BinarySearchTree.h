#include <functional>
#include <memory>

struct InOrder {};
struct PreOrder {};
struct PostOrder {};

template <typename T, typename Compare = std::less<T>, typename alloc = std::allocator<T>>
class BinarySearchTree {
public:
    BinarySearchTree() = default;
    BinarySearchTree(const BinarySearchTree& second) : root(second.root) {}
    ~BinarySearchTree() = default;

    BinarySearchTree& operator=(const BinarySearchTree& rhs) {
        if (this != rhs) {
            root = rhs.root;
        }

        return *this;
    } //DONE

    bool operator==(const BinarySearchTree& rhs) const {
        return root == rhs.root;
    }       //DONE

    bool operator!=(const BinarySearchTree& rhs) const {
        return root != rhs.root;
    }       //DONE

    struct Node {
        T value;
        Node* parent;
        Node* left = nullptr;
        Node* right = nullptr;

        Node(const T& value, Node* parent = nullptr)
            : value(value), parent(parent) {}
    };      //DONE

    std::allocator_traits<alloc>::template rebind_alloc<Node> node_allocator_;

    template<typename OrderTag>
    class iterator {
    public:
        explicit iterator(Node* curr)
            : curr(curr) {}

        T& operator*() { return curr->value; }
        T* operator->() { return &curr->value; }

        bool operator==(const iterator& other) const {
            return curr == other.curr;
        }
        bool operator!=(const iterator& other) const {
            return curr != other.curr;
        }

        iterator& operator++() {
            increment(OrderTag());
            return *this;
        }

        iterator& operator--() {
            decrement(OrderTag());
            return *this;
        }

        void increment(InOrder) {
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                }
            } else {
                while (curr->parent && curr == curr->parent->right) {
                    curr = curr->parent;
                }
            }
        }

        void increment(PreOrder) {
            if (curr->left) {
                curr = curr->left;
            } else if (curr->right) {
                curr = curr->right;
            } else {
                while (curr->parent && (curr->parent->right == curr || curr->parent->right == nullptr)) {
                    curr = curr->parent;
                }
                if (curr->right) {
                    curr = curr->right;
                } else {
                    curr = nullptr;
                }
            }
        }

        void increment(PostOrder) {
            if (curr->left) {
                curr = curr->left;
                while (curr->right) {
                    curr = curr->right;
                }
            } else {
                while (curr->parent && curr == curr->parent->left) {
                    curr = curr->parent;
                }
            }
        }

        void decrement(InOrder) {
            if (curr->left) {
                curr = curr->left;
                while (curr->right) {
                    curr = curr->right;
                }
            } else {
                while (curr->parent && curr == curr->parent->left) {
                    curr = curr->parent;
                }
            }
        }

        void decrement(PreOrder) {
            if (curr->right) {
                curr = curr->right;
            } else if (curr->left) {
                curr = curr->left;
            } else {
                while (curr->parent && (curr->parent->left == curr || curr->parent->left == nullptr)) {
                    curr = curr->parent;
                }
                if (curr->left) {
                    curr = curr->left;
                } else {
                    curr = nullptr;
                }
            }
        }

        void decrement(PostOrder) {
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                }
            } else {
                while (curr->parent && curr == curr->parent->right) {
                    curr = curr->parent;
                }
            }
        }

    private:
        Node* curr;
    };                            //DONE

    template<typename OrderTag>
    class const_iterator {
    public:
        explicit const_iterator(const Node* node)
            : curr(node) {}

        const T& operator*() const { return curr->value; }
        const T* operator->() const { return &(curr->value); }

        bool operator==(const const_iterator& other) const {
            return curr == other.curr;
        }
        bool operator!=(const const_iterator& other) const {
            return curr != other.curr;
        }

        const_iterator& operator++() {
            increment(OrderTag());
            return *this;
        }

        const_iterator& operator--() {
            decrement(OrderTag());
            return *this;
        }

        void increment(InOrder) {
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                }
            } else {
                while (curr->parent && curr == curr->parent->right) {
                    curr = curr->parent;
                }
            }
        }

        void increment(PreOrder) {
            if (curr->left) {
                curr = curr->left;
            } else if (curr->right) {
                curr = curr->right;
            } else {
                while (curr->parent && (curr->parent->right == curr || curr->parent->right == nullptr)) {
                    curr = curr->parent;
                }
                if (curr->right) {
                    curr = curr->right;
                } else {
                    curr = nullptr;
                }
            }
        }

        void increment(PostOrder) {
            if (curr->left) {
                curr = curr->left;
                while (curr->right) {
                    curr = curr->right;
                }
            } else {
                while (curr->parent && curr == curr->parent->left) {
                    curr = curr->parent;
                }
            }
        }

        void decrement(InOrder) {
            if (curr->left) {
                curr = curr->left;
                while (curr->right) {
                    curr = curr->right;
                }
            } else {
                while (curr->parent && curr == curr->parent->left) {
                    curr = curr->parent;
                }
            }
        }

        void decrement(PreOrder) {
            if (curr->right) {
                curr = curr->right;
            } else if (curr->left) {
                curr = curr->left;
            } else {
                while (curr->parent && (curr->parent->left == curr || curr->parent->left == nullptr)) {
                    curr = curr->parent;
                }
                if (curr->left) {
                    curr = curr->left;
                } else {
                    curr = nullptr;
                }
            }
        }

        void decrement(PostOrder) {
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                }
            } else {
                while (curr->parent && curr == curr->parent->right) {
                    curr = curr->parent;
                }
            }
        }

    private:
        const Node* curr;
    };                      //DONE

    template<typename OrderTag>
    class reverse_iterator {
    public:
        explicit reverse_iterator(Node* curr)
                : curr(curr) {}

        T& operator*() { return curr->value; }
        T* operator->() { return &curr->value; }

        bool operator==(const reverse_iterator& other) const {
            return curr == other.curr;
        }
        bool operator!=(const reverse_iterator& other) const {
            return curr != other.curr;
        }

        reverse_iterator& operator++() {
            increment(OrderTag());
            return *this;
        }

        reverse_iterator& operator--() {
            decrement(OrderTag());
            return *this;
        }

        void increment(InOrder) {
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                }
            } else {
                while (curr->parent && curr == curr->parent->right) {
                    curr = curr->parent;
                }
            }
        }

        void increment(PreOrder) {
            if (curr->left) {
                curr = curr->left;
            } else if (curr->right) {
                curr = curr->right;
            } else {
                while (curr->parent && (curr->parent->right == curr || curr->parent->right == nullptr)) {
                    curr = curr->parent;
                }
                if (curr->right) {
                    curr = curr->right;
                } else {
                    curr = nullptr;
                }
            }
        }

        void increment(PostOrder) {
            if (curr->left) {
                curr = curr->left;
                while (curr->right) {
                    curr = curr->right;
                }
            } else {
                while (curr->parent && curr == curr->parent->left) {
                    curr = curr->parent;
                }
            }
        }

        void decrement(InOrder) {
            if (curr->left) {
                curr = curr->left;
                while (curr->right) {
                    curr = curr->right;
                }
            } else {
                while (curr->parent && curr == curr->parent->left) {
                    curr = curr->parent;
                }
            }
        }

        void decrement(PreOrder) {
            if (curr->right) {
                curr = curr->right;
            } else if (curr->left) {
                curr = curr->left;
            } else {
                while (curr->parent && (curr->parent->left == curr || curr->parent->left == nullptr)) {
                    curr = curr->parent;
                }
                if (curr->left) {
                    curr = curr->left;
                } else {
                    curr = nullptr;
                }
            }
        }

        void decrement(PostOrder) {
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                }
            } else {
                while (curr->parent && curr == curr->parent->right) {
                    curr = curr->parent;
                }
            }
        }

    private:
        Node* curr;
    };                    //DONE

    template<typename OrderTag>
    class const_reverse_iterator {
    public:
        explicit const_reverse_iterator(const Node* node)
                : curr(node) {}

        const T& operator*() const { return curr->value; }
        const T* operator->() const { return &(curr->value); }

        bool operator==(const const_reverse_iterator& other) const {
            return curr == other.curr;
        }
        bool operator!=(const const_reverse_iterator& other) const {
            return curr != other.curr;
        }

        const_reverse_iterator& operator++() {
            increment(OrderTag());
            return *this;
        }

        const_reverse_iterator& operator--() {
            decrement(OrderTag());
            return *this;
        }

        void increment(InOrder) {
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                }
            } else {
                while (curr->parent && curr == curr->parent->right) {
                    curr = curr->parent;
                }
            }
        }

        void increment(PreOrder) {
            if (curr->left) {
                curr = curr->left;
            } else if (curr->right) {
                curr = curr->right;
            } else {
                while (curr->parent && (curr->parent->right == curr || curr->parent->right == nullptr)) {
                    curr = curr->parent;
                }
                if (curr->right) {
                    curr = curr->right;
                } else {
                    curr = nullptr;
                }
            }
        }

        void increment(PostOrder) {
            if (curr->left) {
                curr = curr->left;
                while (curr->right) {
                    curr = curr->right;
                }
            } else {
                while (curr->parent && curr == curr->parent->left) {
                    curr = curr->parent;
                }
            }
        }

        void decrement(InOrder) {
            if (curr->left) {
                curr = curr->left;
                while (curr->right) {
                    curr = curr->right;
                }
            } else {
                while (curr->parent && curr == curr->parent->left) {
                    curr = curr->parent;
                }
            }
        }

        void decrement(PreOrder) {
            if (curr->right) {
                curr = curr->right;
            } else if (curr->left) {
                curr = curr->left;
            } else {
                while (curr->parent && (curr->parent->left == curr || curr->parent->left == nullptr)) {
                    curr = curr->parent;
                }
                if (curr->left) {
                    curr = curr->left;
                } else {
                    curr = nullptr;
                }
            }
        }

        void decrement(PostOrder) {
            if (curr->right) {
                curr = curr->right;
                while (curr->left) {
                    curr = curr->left;
                }
            } else {
                while (curr->parent && curr == curr->parent->right) {
                    curr = curr->parent;
                }
            }
        }

    private:
        const Node* curr;
    };              //DONE

//    методы узлов
    Node* allocatenode(const T& value) {
        Node* node = node_allocator_.allocate(1);
        return node;
    }         //DONE

    void deallocatenode(Node* node) {
        if (node) {
            node_allocator_.destroy(node);
            node_allocator_.deallocate(node, 1);
        }
    }           //DONE

//    методы работы с элементами
    bool exists(T value) {
        Node* curr = root;

        while (curr) {
            if (value > curr->value) {
                curr = curr->right;
            } else if (value < curr->value) {
                curr = curr->left;
            } else {
                return true;
            }
        }

        return false;
    }                       //DONE

    Node* findmin() {
        Node* curr = root;
        while (curr->left != nullptr) {
            curr = curr->left;
        }

        return curr;
    }                            //DONE

    Node* insert(const T& value) const noexcept {
        Node* curr = root;
        Node* parent = nullptr;
        Node* newNode = allocatenode(value);

        while (curr) {
            parent = curr;
            if (value > curr->value) {
                curr = curr->right;
            } else if (value < curr->value) {
                curr = curr->left;
            }
        }

        curr = newNode;
        curr->parent = parent;
        return curr;
    }       //DONE

    Node* findmax() {
        Node* curr = root;
        while (curr->rightr != nullptr) {
            curr = curr->right;
        }

        return curr;
    }                            //DONE

    bool empty() const noexcept {
        return (root != nullptr);
    }                //DONE

    Node* prev(const T& value) const {
        Node* curr = root;
        Node* ans = nullptr;
        while (curr != nullptr) {
            if (curr->value < value) {
                ans = curr;
                curr = curr->right;
            } else {
                curr = curr->left;
            }
        }

        return ans;
    }           //DONE

    Node* next(const T& value) const {
        Node* curr = root;
        Node* ans = nullptr;
        while (curr != nullptr) {
            if (curr->value > value) {
                ans = curr;
                curr = curr->left;
            } else {
                curr = curr->right;
            }
        }

        return ans;
    }           //DONE

    size_t countNodes(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return 1 + countNodes(node->left) + countNodes(node->right);
    }                       //DONE

    size_t size() const noexcept {
        return countNodes(root);
    }                        //DONE

    size_t max_size() const noexcept {
        std::allocator_traits<alloc>::max_size(node_allocator_);
    }                    //DONE

//    методы контейнера
    alloc get_allocator() const noexcept {
        return node_allocator_;
    }                //DONE

    template<typename OrderTag>
    const_iterator<OrderTag> begin() const {
        if constexpr (std::is_same_v<OrderTag, InOrder>) {
            Node* n = root;
            while (n && n->left) {
                n = n->left;
            }

            return const_iterator<OrderTag>(n);
        } else if constexpr (std::is_same_v<OrderTag, PreOrder>) {
            return const_iterator<OrderTag>(root);
        } else if constexpr (std::is_same_v<OrderTag, PostOrder>) {
            Node* n = root;
            while (n && n->right) {
                n = n->right;
            }

            return const_iterator<OrderTag>(n);
        }
    }              //DONE

    template<typename OrderTag>
    const_iterator<InOrder> cbegin() const {
        if constexpr (std::is_same_v<OrderTag, InOrder>) {
            Node* n = root;
            while (n && n->left) {
                n = n->left;
            }

            return const_iterator<OrderTag>(n);
        } else if constexpr (std::is_same_v<OrderTag, PreOrder>) {
            return const_iterator<OrderTag>(root);
        } else if constexpr (std::is_same_v<OrderTag, PostOrder>) {
            Node* n = root;
            while (n && n->right) {
                n = n->right;
            }

            return const_iterator<OrderTag>(n);
        }
    }              //DONE

    template<typename OrderTag>
    iterator<OrderTag> end() const {
        return nullptr;
    }                      //DONE

    template<typename OrderTag>
    const_iterator<OrderTag> cend() const {
        return nullptr;
    }               //DONE

    template<typename OrderTag>
    reverse_iterator<OrderTag> rbegin() const {
        Node* n = root;
        while (n && n->right) {
            n = n->right;
        }

        return const_iterator<OrderTag>(n);
    }           //DONE

    template<typename OrderTag>
    const_reverse_iterator<OrderTag> crbegin() const {
        Node* n = root;
        while (n && n->right) {
            n = n->right;
        }

        return const_iterator<OrderTag>(n);
    }    //DONE

    template<typename OrderTag>
    reverse_iterator<OrderTag> rend() const {
        return nullptr;
    }             //DONE

    template<typename OrderTag>
    const_reverse_iterator<OrderTag> crend() const {
        return nullptr;
    }      //DONE

    void clear(Node* node) noexcept {
        if (node) {
            clear(node->left);
            clear(node->right);
            deallocatenode(node);
        }
    }                     //DONE

    void clear() noexcept {
        clear(root);
        root = nullptr;
    }                               //DONE

    size_t erase(const T& value) {
        Node* current = root;
        Node* parent = nullptr;
        size_t erased = 0;

        while (current != nullptr) {
            if (value == current->value) {
                break;
            }
            parent = current;
            if (Compare()(value, current->value)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            return 0; // Узел с таким значением не найден
        }

        // Удаляемый узел имеет двух детей
        if (current->left != nullptr && current->right != nullptr) {
            Node* successor = current->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }

            current->value = successor->value;
            current = successor;
        }

        // Удаляемый узел имеет максимум одного ребенка
        Node* replacement = (current->left != nullptr) ? current->left : current->right;

        if (replacement != nullptr) {
            // Удаляемый узел не является корнем
            if (parent != nullptr) {
                if (parent->left == current) {
                    parent->left = replacement;
                } else {
                    parent->right = replacement;
                }
            } else {
                root = replacement; // Удаляемый узел является корнем
            }
            replacement->parent = parent;
            deallocatenode(current);
            erased = 1;
        } else if (parent == nullptr) {
            // Удаляемый узел - это корень, но у него нет детей
            deallocatenode(current);
            root = nullptr;
            erased = 1;
        } else {
            // Удаляемый узел не является корнем и не имеет детей
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            deallocatenode(current);
            erased = 1;
        }

        return erased;
    }                        //DONE

    const_iterator<InOrder> extract(const_iterator<InOrder> position) const noexcept {
        Node* current = root;
        Node* parent = nullptr;

        while (current != nullptr) {
            if (position.curr == current->value) {
                break;
            }
            parent = current;
            if (Compare()(position.curr, current->value)) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            return const_iterator<InOrder>(findmax()); // Узел с таким значением не найден
        }

        // Удаляемый узел имеет двух детей
        if (current->left != nullptr && current->right != nullptr) {
            Node* successor = current->right;
            while (successor->left != nullptr) {
                successor = successor->left;
            }

            current->value = successor->value;
            current = successor;
        }

        // Удаляемый узел имеет максимум одного ребенка
        Node* replacement = (current->left != nullptr) ? current->left : current->right;

        if (replacement != nullptr) {
            // Удаляемый узел не является корнем
            if (parent != nullptr) {
                if (parent->left == current) {
                    parent->left = std::move(replacement);
                } else {
                    parent->right = std::move(replacement);
                }
            } else {
                root = replacement; // Удаляемый узел является корнем
            }
            replacement->parent = parent;
            deallocatenode(current);
        } else if (parent == nullptr) {
            // Удаляемый узел - это корень, но у него нет детей
            root = nullptr;
        } else {
            // Удаляемый узел не является корнем и не имеет детей
            if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
        }

        return ++position;
    }

    void in_order_traversal(Node* node) noexcept {
        if (node) {
            in_order_traversal(node->left);
            insert(node->value);
            in_order_traversal(node->right);
        }
    }        //DONE

    void merge(BinarySearchTree& source) noexcept {
        in_order_traversal(source.root);
    }       //DONE

    size_t count(const T& value) const noexcept {
        Node* curr = root;

        while (curr) {
            if (value > curr->value) {
                curr = curr->right;
            } else if (value < curr->value) {
                curr = curr->left;
            } else {
                return 1;
            }
        }

        return 0;
    }         //DONE

    const_iterator<InOrder> find(const T& value) const noexcept {
        Node* curr = root;

        while (curr) {
            if (value > curr->value) {
                curr = curr->right;
            } else if (value < curr->value) {
                curr = curr->left;
            } else {
                return const_iterator<InOrder>(curr);
            }
        }

        return const_iterator<InOrder>(nullptr);
    }       //DONE

    bool contains(const T& value) const noexcept {
        Node* curr = root;

        while (curr) {
            if (value > curr->value) {
                curr = curr->right;
            } else if (value < curr->value) {
                curr = curr->left;
            } else {
                return true;
            }
        }

        return false;
    }        //DONE

    std::pair<iterator<InOrder>, iterator<InOrder>> equal_range(const T& value) noexcept {
        iterator<InOrder> found = find(value);
        if (found == end()) {
            return std::make_pair(end(), end());
        } else {
            return std::make_pair(found, std::next(found));
        }
    }
                                                              //DONE
private:
    Node* root;
};
