#include "Iterator.cpp"
#include "ReverseIterator.cpp"

namespace BinarySearchTree {
    struct PreorderTraversalTag {};
    struct InorderTraversalTag {};
    struct PostorderTraversalTag {};

    template<typename T, class Allocator = std::allocator<T>, typename LessCompare = std::less<T>, typename GreaterCompare = std::greater<T>>
    class BinarySearchTree {
    private:
        struct Node {
            std::allocator<T> node_allocator = Allocator();
            Node* left_son, * right_son, * parent;
            T* key;

            Node() : key(nullptr), left_son(nullptr), right_son(nullptr), parent(nullptr) {};

            explicit Node(const T& x) : left_son(nullptr), right_son(nullptr), parent(nullptr) {
                key = node_allocator.allocate(1);
                node_allocator.construct(key, x);
            };

            Node(const Node& other) {
                if (&other == this || &other == nullptr)
                    return;
                left_son = other.left_son;
                right_son = other.right_son;
                parent = other.parent;
                key = node_allocator.allocate(1);
                node_allocator.construct(key, *other.key);
            }

            Node& operator=(const Node& other) {
                Node temp(other);
                left_son = temp.left_son;
                right_son = temp.right_son;
                parent = temp.parent;
                key = node_allocator.allocate(1);
                node_allocator.construct(key, *other.key);
                return *this;
            }
        };

        std::allocator<Node> vertex_allocator = Allocator();
        std::allocator<myVector<T>> traversal_allocator = Allocator();
        LessCompare less_cmp = LessCompare{};
        GreaterCompare greater_cmp = GreaterCompare{};
        int size_ = 0;
        Node* root = nullptr;
        myVector<T>* preorder, * inorder, * postorder;
    public:
        explicit BinarySearchTree() {
            preorder = traversal_allocator.allocate(1);
            inorder = traversal_allocator.allocate(1);
            postorder = traversal_allocator.allocate(1);
        }

        ~BinarySearchTree() {
            traversal_allocator.deallocate(preorder, 1);
            traversal_allocator.deallocate(inorder, 1);
            traversal_allocator.deallocate(postorder, 1);
        }

        BinarySearchTree(const BinarySearchTree& other) {
            if (&other == this || &other == nullptr)
                return;
            vertex_allocator = other.vertex_allocator;
            traversal_allocator = other.traversal_allocator;
            less_cmp = other.less_cmp;
            greater_cmp = other.greater_cmp;
            size_ = other.size_;
            preorder = traversal_allocator.allocate(1);
            for (int i = 0; i < size_; ++i)
                preorder->push_back(other.preorder->getValue(i));
            inorder = traversal_allocator.allocate(1);
            for (int i = 0; i < size_; ++i)
                inorder->push_back(other.inorder->getValue(i));
            postorder = traversal_allocator.allocate(1);
            for (int i = 0; i < size_; ++i)
                postorder->push_back(other.postorder->getValue(i));
            root = nullptr;
            for (int i = 0; i < size_; ++i)
                insert(preorder->getValue(i), true);
        }

        BinarySearchTree& operator=(const BinarySearchTree& other) {
            BinarySearchTree temp(other);
            vertex_allocator = temp.vertex_allocator;
            traversal_allocator = temp.traversal_allocator;
            less_cmp = temp.less_cmp;
            greater_cmp = temp.greater_cmp;
            size_ = temp.size_;
            preorder = traversal_allocator.allocate(1);
            for (int i = 0; i < size_; ++i)
                preorder->push_back(other.preorder->getValue(i));
            inorder = traversal_allocator.allocate(1);
            for (int i = 0; i < size_; ++i)
                inorder->push_back(other.inorder->getValue(i));
            postorder = traversal_allocator.allocate(1);
            for (int i = 0; i < size_; ++i)
                postorder->push_back(other.postorder->getValue(i));
            root = nullptr;
            for (int i = 0; i < size_; ++i)
                insert(preorder->getValue(i), true);
            return *this;
        }

        [[nodiscard]] bool empty() const {
            return size_ == 0;
        }

        void insert(const T& key, bool constructor_flag = false) {
            Node* temp = vertex_allocator.allocate(1);
            vertex_allocator.construct(temp, Node(key));
            if (root == nullptr) {
                root = temp;
            } else {
                Node* cur = root;
                Node* prev;
                while (cur != nullptr) {
                    prev = cur;
                    if (greater_cmp(*temp->key, *cur->key))
                        cur = cur->right_son;
                    else if (less_cmp(*temp->key, *cur->key))
                        cur = cur->left_son;
                    else
                        return;
                }
                if (greater_cmp(*prev->key, key)) {
                    prev->left_son = temp;
                    temp->parent = prev;
                } else if (less_cmp(*prev->key, key)) {
                    prev->right_son = temp;
                    temp->parent = prev;
                }
            }
            if (constructor_flag)
                return;
            size_++;
            preorder->clear();
            preorderTraversal(root);
            inorder->clear();
            inorderTraversal(root);
            postorder->clear();
            postorderTraversal(root);
        };

        Node* find(Node* cur, const T& val) const {
            if (cur == nullptr || *cur->key == val)
                return cur;
            if (less_cmp(val, *cur->key))
                return find(cur->left_son, val);
            else
                return find(cur->right_son, val);
        };

        bool contains(const T& val) const {
            return find(root, val) != nullptr;
        };

        int32_t count(const T& val) {
            return static_cast<int32_t>(contains(val) == true);
        }

        Node* next(const T& val) const {
            Node* cur = root;
            Node* successor = nullptr;
            while (cur != nullptr) {
                if (greater_cmp(*cur->key, val)) {
                    successor = cur;
                    cur = cur->left_son;
                } else {
                    cur = cur->right_son;
                }
            }
            return successor;
        };

        Node* prev(const T& val) const {
            Node* cur = root;
            Node* successor = nullptr;
            while (cur != nullptr) {
                if (less_cmp(*cur->key, val)) {
                    successor = cur;
                    cur = cur->right_son;
                } else {
                    cur = cur->left_son;
                }
            }
            return successor;
        }

        Node* minimum(const T& val) const {
            return minimum(find(root, val));
        }

        Node* minimum(Node* x) const {
            if (x->left_son == nullptr)
                return x;
            return minimum(x->left_son);
        }

        Node* maximum(const T& val) const {
            return maximum(find(root, val));
        }

        Node* maximum(Node* x) const {
            if (x->right_son == nullptr)
                return x;
            return maximum(x->right_son);
        }

        void erase(const T& val) {
            erase(find(root, val));
        }

        void erase(Node* v) {
            if (!v)
                return;
            Node* p = v->parent;
            if (v->left_son == nullptr && v->right_son == nullptr) {
                if (v == root) {
                    root->node_allocator.deallocate(root->key, 1);
                    vertex_allocator.destroy(root);
                    vertex_allocator.deallocate(root, 1);
                    root = nullptr;
                } else {
                    if (p->left_son == v) {
                        p->left_son->node_allocator.deallocate(p->left_son->key, 1);
                        vertex_allocator.destroy(p->left_son);
                        vertex_allocator.deallocate(p->left_son, 1);
                        p->left_son = nullptr;
                    } else {
                        p->right_son->node_allocator.deallocate(p->right_son->key, 1);
                        vertex_allocator.destroy(p->right_son);
                        vertex_allocator.deallocate(p->right_son, 1);
                        p->right_son = nullptr;
                    }
                }
                --size_;
                preorder->clear();
                preorderTraversal(root);
                inorder->clear();
                inorderTraversal(root);
                postorder->clear();
                postorderTraversal(root);
            } else if (v->left_son == nullptr || v->right_son == nullptr) {
                Node* son;
                if (v->left_son == nullptr)
                    son = v->right_son;
                else
                    son = v->left_son;
                if (v == root) {
                    root = son;
                } else if (v->parent->left_son == v)
                    v->parent->left_son = son;
                else
                    v->parent->right_son = son;
                --size_;
                preorder->clear();
                preorderTraversal(root);
                inorder->clear();
                inorderTraversal(root);
                postorder->clear();
                postorderTraversal(root);
            } else {
                Node* successor = next(*v->key);
                *v->key = *successor->key;
                erase(successor);
            }
        }

        T extract(const T& val) {
            Node* temp = find(root, val);
            if (!temp) return;
            T ans = *temp->key;
            erase(temp);
            return ans;
        }

        void destroyTree(Node* cur) {
            if (cur != nullptr) {
                destroyTree(cur->left_son);
                destroyTree(cur->right_son);
                erase(cur);
            }
        }

        void clear() {
            destroyTree(root);
            size_ = 0;
            root = nullptr;
            preorder->clear();
            inorder->clear();
            postorder->clear();
        }

        myVector<T>* getPreorder() {
            return preorder;
        }

        myVector<T>* getInorder() {
            return inorder;
        }

        myVector<T>* getPostorder() {
            return postorder;
        }

        void preorderTraversal(Node* x) const {
            if (x != nullptr) {
                preorder->push_back(*x->key);
                preorderTraversal(x->left_son);
                preorderTraversal(x->right_son);
            }
        }

        void inorderTraversal(Node* x) const {
            if (x != nullptr) {
                inorderTraversal(x->left_son);
                inorder->push_back(*x->key);
                inorderTraversal(x->right_son);
            }
        }

        void postorderTraversal(Node* x) const {
            if (x != nullptr) {
                postorderTraversal(x->left_son);
                postorderTraversal(x->right_son);
                postorder->push_back(*x->key);
            }
        }

        Iterator<T> begin(struct PreorderTraversalTag) {
            return {preorder, 0};
        }

        Iterator<T> begin(struct InorderTraversalTag) {
            return {inorder, 0};
        }

        Iterator<T> begin(struct PostorderTraversalTag) {
            return {postorder, 0};
        }

        Iterator<T> end(struct PreorderTraversalTag) {
            return {preorder, size_};
        }

        Iterator<T> end(struct InorderTraversalTag) {
            return {inorder, size_};
        }

        Iterator<T> end(struct PostorderTraversalTag) {
            return {postorder, size_};
        }

        ReverseIterator<T> rbegin(struct PreorderTraversalTag) {
            return {preorder, size_ - 1};
        }

        ReverseIterator<T> rbegin(struct InorderTraversalTag) {
            return {inorder, size_ - 1};
        }

        ReverseIterator<T> rbegin(struct PostorderTraversalTag) {
            return {postorder, size_ - 1};
        }

        ReverseIterator<T> rend(struct PreorderTraversalTag) {
            return {preorder, -1};
        }

        ReverseIterator<T> rend(struct InorderTraversalTag) {
            return {inorder, -1};
        }

        ReverseIterator<T> rend(struct PostorderTraversalTag) {
            return {postorder, -1};
        }

        Iterator<T> cbegin(struct PreorderTraversalTag) {
            return {preorder, 0};
        }

        Iterator<T> cbegin(struct InorderTraversalTag) {
            return {inorder, 0};
        }

        Iterator<T> cbegin(struct PostorderTraversalTag) {
            return {postorder, 0};
        }

        Iterator<T> cend(struct PreorderTraversalTag) {
            return {preorder, size_};
        }

        Iterator<T> cend(struct InorderTraversalTag) {
            return {inorder, size_};
        }

        Iterator<T> cend(struct PostorderTraversalTag) {
            return {postorder, size_};
        }

        ReverseIterator<T> crbegin(struct PreorderTraversalTag) {
            return {preorder, size_ - 1};
        }

        ReverseIterator<T> crbegin(struct InorderTraversalTag) {
            return {inorder, size_ - 1};
        }

        ReverseIterator<T> crbegin(struct PostorderTraversalTag) {
            return {postorder, size_ - 1};
        }

        ReverseIterator<T> crend(struct PreorderTraversalTag) {
            return {preorder, -1};
        }

        ReverseIterator<T> crend(struct InorderTraversalTag) {
            return {inorder, -1};
        }

        ReverseIterator<T> crend(struct PostorderTraversalTag) {
            return {postorder, -1};
        }

        friend bool operator==(const BinarySearchTree& lhs, const BinarySearchTree& rhs) {
            return lhs.size_ == rhs.size_ && *lhs.preorder == *rhs.preorder
                   && *lhs.inorder == *rhs.inorder && *lhs.postorder == *rhs.postorder;
        }

        friend bool operator!=(const BinarySearchTree& lhs, const BinarySearchTree& rhs) {
            return !(lhs == rhs);
        }

        void swap(BinarySearchTree& other) {
            BinarySearchTree temp(other);
            other.clear();
            other = *this;
            this->clear();
            *this = temp;
        }
    };

    template<typename T, class Allocator = std::allocator<T>, typename LessCompare = std::less<T>, typename GreaterCompare = std::greater<T>>
    void swap(BinarySearchTree<T>& lhs, BinarySearchTree<T>& rhs) {
        lhs.swap(rhs);
    }
}