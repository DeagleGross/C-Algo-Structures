#include <stack>
#include <iostream>
#include "ReadWriter.cpp"

//Можно добавлять любые методы для решения задачи.

// to debug
//void showNeighbours(std::vector<Node*> neighbours)
//{
//    for (int i = 0; i < neighbours.size(); ++i)
//        std::cout << i << ") " << neighbours[i]->name << std::endl;
//}

/// implementation of quicksort for std::vector<Node*> by Node.name
void quickSort(std::vector<Node*>& neighbours, int left, int right)
{
    if (left >= right)
        return;

    Node* pivot = neighbours[(left + right) / 2];
    int l = left;
    int r = right;

    while (l <= r)
    {
        while (neighbours[l]->name < pivot->name)
            ++l;
        while (neighbours[r]->name > pivot->name)
            --r;

        if (l <= r)
        {
            std::swap(neighbours[l], neighbours[r]);

            ++l;
            --r;
        }
    }

    if (left < r)
        quickSort(neighbours, left, r);
    if (l < right)
        quickSort(neighbours, l, right);
}

/// sorts alphabetically vector<Node*>
void sortAlphabetic(std::vector<Node*> &neighbours)
{
    quickSort(neighbours, 0, neighbours.size() - 1);
}

/// go through next element in stack
void goThrough(std::stack<Node*>& stack, std::vector<std::string>& result)
{
    // taking last node from stack and popping it away
    // and pushing its name to result vector
    Node* node = stack.top();
    stack.pop();
    result.push_back(node->name);

    // placing node as visited
    node->visited = true;

    // sorting node.neighbours
    sortAlphabetic(node->neighbours);

    // taking all neighbours
    // if not visited - pushing to stack and launching recursion
    for (Node* friends : node->neighbours)
    {
        if (!friends->visited)
        {
            stack.push(friends);
            goThrough(stack, result);
        }
    }
}

/// DFS algorithm to be used here
void DFS(std::vector<Node>& graph, int start, std::vector<std::string>& result)
{
    // making stack and placing start-element to it
    std::stack<Node*> stack = std::stack<Node*>();
    graph[start].visited = true;
    stack.push(&graph[start]);

    // when empty - no friends left :(
    while (!stack.empty())
        goThrough(stack, result);
}

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node>& graph, int start, std::vector<std::string>& result){
    DFS(graph, start, result);
}

int main() {
    std::vector<Node> graph;
    std::vector<std::string> result;
    int start;

    ReadWriter rw;
    rw.readGraph(graph, start);
    solve(graph, start, result);
    rw.writeAnswer(result);
    return 0;
}
