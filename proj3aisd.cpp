#include <iostream>

using namespace std;

struct childChild {
    int key;
    childChild** children = nullptr;

    childChild(int key) : key(key) {}
};

struct rootChild {
    int key;
    childChild** children = nullptr;

    rootChild(int key) : key(key) {}
};

void childrenAllocate(childChild*& node, int k) {
    if (!node->children)
    {
        node->children = new childChild * [k];
        for (int i = 0; i < k; i++)
        {
            node->children[i] = nullptr;
        }
    }
}

void childrenAllocate(rootChild*& root, int n) {
    if (!root->children)
    {
        root->children = new childChild * [n];
        for (int i = 0; i < n; i++)
        {
            root->children[i] = nullptr;
        }
    }
}

bool hasChildren(childChild* node, int k) {
    if (!node || !node->children)
    {
        return false;
    }
    for (int i = 0; i < k; i++)
    {
        if (node->children[i])
        {
            return true;
        }
    }
    return false;
}

bool hasChildren(rootChild* node, int n) {
    if (!node || !node->children)
    {
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        if (node->children[i])
        {
            return true;
        }
    }
    return false;
}

void cleanupChild(childChild* node, int k) {
    if (!node)
    {
        return;
    }
    if (node->children)
    {
        for (int i = 0; i < k; i++)
        {
            cleanupChild(node->children[i], k);
        }
        delete[] node->children;
    }
    delete node;
}

void cleanup(rootChild* root, int n, int k) {
    if (!root)
    {
        return;
    }
    if (root->children)
    {
        for (int i = 0; i < n; i++)
        {
            cleanupChild(root->children[i], k);
        }
        delete[] root->children;
    }
    delete root;
}

void searchKey(rootChild* root, int key, int n, int k) {
    if (!root)
    {
        cout << key << " not exist" << endl;
        return;
    }

    if (root->key == key)
    {
        cout << key << " exist" << endl;
        return;
    }

    if (!root->children)
    {
        cout << key << " not exist" << endl;
        return;
    }

    int div = key / n;
    int index = key % n;

    childChild* current = root->children[index];
    if (!current)
    {
        cout << key << " not exist" << endl;
        return;
    }

    while (current)
    {
        if (current->key == key)
        {
            cout << key << " exist" << endl;
            return;
        }
        if (!current->children)
        {
            break;
        }
        int nextIndex = div % k;
        div = div / k;
        current = current->children[nextIndex];
    }

    cout << key << " not exist" << endl;
}

void printChildInorder(childChild* node, int k) {
    if (!node)
    {
        return;
    }
    cout << node->key << " ";
    if (node->children)
    {
        for (int i = 0; i < k; i++)
        {
            printChildInorder(node->children[i], k);
        }
    }
}

void printTrieInorder(rootChild* root, int n, int k) {
    if (!root)
    {
        return;
    }
    cout << root->key << " ";
    if (root->children)
    {
        for (int i = 0; i < n; i++)
        {
            printChildInorder(root->children[i], k);
        }
    }
    cout << endl;
}

void insertKey(rootChild*& root, int key, int n, int k) {
    if (!root)
    {
        root = new rootChild(key);
        return;
    }

    if (root->key == key)
    {
        cout << key << " exist" << endl;
        return;
    }

    childrenAllocate(root, n);
    int div = key / n;
    int index = key % n;

    if (!root->children[index])
    {
        root->children[index] = new childChild(key);
        return;
    }

    childChild* current = root->children[index];
    while (true)
    {
        if (current->key == key)
        {
            cout << key << " exist" << endl;
            return;
        }

        childrenAllocate(current, k);
        int nextIndex = div % k;
        div = div / k;

        if (!current->children[nextIndex])
        {
            current->children[nextIndex] = new childChild(key);
            return;
        }
        current = current->children[nextIndex];
    }
}

childChild* searchCandidateToDelete(childChild* node, int k) {
    if (!node || !node->children)
    {
        return nullptr;
    }
    for (int i = 0; i < k; ++i)
    {
        if (node->children[i])
        {
            if (!hasChildren(node->children[i], k))
            {
                childChild* toDelete = node->children[i];
                node->children[i] = nullptr;
                return toDelete;
            }
            else
            {
                childChild* candidate = searchCandidateToDelete(node->children[i], k);
                if (candidate) return candidate;
            }
        }
    }
    return nullptr;
}

void deleteKey(rootChild*& root, int key, int n, int k)
{
    if (!root)
    {
        cout << key << " not exist" << endl;
        return;
    }

    if (root->key == key)
    {
        if (!hasChildren(root, n))
        {
            cleanup(root, n, k);
            root = nullptr;
            return;
        }

        for (int i = 0; i < n; i++)
        {
            if (root->children[i] && !hasChildren(root->children[i], k))
            {
                root->key = root->children[i]->key;
                cleanupChild(root->children[i], k);
                root->children[i] = nullptr;
                return;
            }
        }

        for (int i = 0; i < n; i++)
        {
            if (root->children[i])
            {
                childChild* candidate = searchCandidateToDelete(root->children[i], k);
                if (candidate)
                {
                    root->key = candidate->key;
                    delete candidate;
                    return;
                }
            }
        }
        return;
    }

    if (!root->children)
    {
        cout << key << " not exist" << endl;
        return;
    }

    int div = key / n;
    int index = key % n;

    childChild** current = &root->children[index];
    while (*current)
    {
        if ((*current)->key == key)
        {
            if (!hasChildren(*current, k))
            {
                cleanupChild(*current, k);
                *current = nullptr;
                return;
            }
            else
            {
                childChild* candidate = searchCandidateToDelete(*current, k);
                if (candidate)
                {
                    (*current)->key = candidate->key;
                    delete candidate;
                    return;
                }
            }
        }

        if (!(*current)->children) break;
        int nextIndex = div % k;
        div = div / k;
        current = &(*current)->children[nextIndex];
    }

    cout << key << " not exist" << endl;
}

int main() {
    rootChild* root = nullptr;
    int numberOfTestCases, minVal, maxVal, n, k;
    cin >> numberOfTestCases;
    cin >> minVal >> maxVal;
    cin >> n >> k;

    for (int i = 0; i < numberOfTestCases; i++)
    {
        char instruction;
        int key;
        cin >> instruction;
        if (instruction != 'P')
        {
            cin >> key;
        }

        switch (instruction) {
        case 'I':
            insertKey(root, key, n, k);
            break;
        case 'L':
            searchKey(root, key, n, k);
            break;
        case 'P':
            printTrieInorder(root, n, k);
            break;
        case 'D':
            deleteKey(root, key, n, k);
            break;
        }
    }

    cleanup(root, n, k);
    return 0;
}