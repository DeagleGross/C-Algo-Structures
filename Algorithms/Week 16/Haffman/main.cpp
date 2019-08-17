#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <queue>

using namespace std;

class Node
{
private:
    int id = -1;
    int p;
    bool code;
    Node* left;
    Node* right;

private:
    void connectNode(Node* node, bool left)
    {
        if (left) {
            this->left = node;
            this->left->code = false;
        } else {
            this->right = node;
            this->right->code = true;
        }
    }

public:
    int getID() { return id; }
    int getP() const { return p; }
    string getCode() { return (code) ? "1" : "0" ; }
    bool hasChildren() { return !(left == nullptr && right == nullptr); }
    Node* getLeft() { return left; }
    Node* getRight() { return right; }

    // for debug
    void toString(){
        cout << "Node: p = " << p;
    }

public:
    Node(int p, int id)
    {
        this->id = id;
        this->p = p;
        left = nullptr;
        right = nullptr;
    }

    Node(int p, Node* left, Node* right)
    {
        this->p = p;
        connectNode(left, true);
        connectNode(right, false);
    }
};

class Compare
{
public:
    bool operator() (const Node* lhs, const Node* rhs)
    {
        return lhs->getP() > rhs->getP();
    }
};

class Huffman
{
private:
    int N = 0;
    vector<Node*> nodes = vector<Node*>();
    vector<string> codes = vector<string>();

    /// for debug
private:
    void popLast(){
        nodes.erase(nodes.begin() + N-- - 1);
    }

    void insertAt(Node* node){
        bool inserted = false;

        for (int i = N-1; i >= 0; --i)
        {
            if (nodes[i]->getP() >= node->getP())
            {
                nodes.insert(nodes.begin() + i + 1, node);
                inserted = true;
                break;
            }
        }

        if (!inserted)
            nodes.insert(nodes.begin(), node);

        ++N;
    }

private:
    void buildTree()
    {
        while (nodes.size() != 1)
        {
            // taking nodes with minimum P-values
            // r.p < l.p -> writing 0 to 'r' and 1 to 'l'

            // element less
            Node* l = nodes.back();
            popLast();

            // element more
            Node* r = nodes.back();
            popLast();

            Node* node = new Node(l->getP() + r->getP(), l, r);
            insertAt(node);
        }
    }

    void goToBot(Node* node, string code, bool addRoot = false)
    {
        if (!addRoot)
            code += node->getCode();

        // debug
        // node->toString(); cout << "; code = '" << code << "';" << endl;

        if (node->hasChildren()) {
            // left (less)
            goToBot(node->getLeft(), code);
            // right (greater)
            goToBot(node->getRight(), code);
        } else {
            codes[node->getID()] = code;
        }
    }

    void formCodes()
    {
        Node* root = nodes.back();
        string code = "";
        goToBot(root, code, true);
    }

public:
    /// main method
    void build()
    {
        buildTree();
        formCodes();
    }

    void addChance (int chance)
    {
        Node* tmp = new Node(chance, N);
        nodes.push_back(tmp);
        ++N;
        codes.push_back("");
    }
    string get (int i) { return codes[i]; }
};


int main() {

    int n;
    Huffman * huff = new Huffman();
    fstream fin;
    fin.open("input.txt",ios::in);
    if(fin.is_open()) {
        fin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            fin >> x;
            huff->addChance (x);
        }

        fin.close();

        huff->build();

        fstream fout;
        fout.open("output.txt",ios::out);
        for (int i = 0; i < n; i++){
            fout << huff->get(i) << (i==n-1?"":" ");
        }
        fout.close();
        delete huff;

    }

    return 0;

}

