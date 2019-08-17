
#include <queue>
#include <iostream>
#include "ReadWriter.cpp"

//Можно добавлять любые методы для решения задачи.

//// to debug
//void showNeighbours(std::vector<Node*> neighbours)
//{
//    for (int i = 0; i < neighbours.size(); ++i)
//        std::cout << i << ") " << neighbours[i]->name << std::endl;
//}
//
//// to debug
//void showQueue(std::queue<Node*> queue)
//{
//    std::cout << "queue:: " << std::endl;
//    for (int i = 0; i < queue.size(); ++i)
//        std::cout << i << ") " << queue.front()->name << std::endl;
//}

/// sets all structures fields
/// for BFS algorithm
void setupDefault(std::vector<Node>& graph, std::queue<Node*>& queue, int start)
{
    // dont need to place visited = false
    // cause they are already setuped in file Node.h
    //    for (int i = 0; i < graph.size(); ++i)
    //    {
    //        graph[i].visited = false;
    //    }

    graph[start].visited = true;
    queue.push(&graph[start]);
}

/// quickSort implementation for std::vector<Node*> by names
/// called in "sortAlphabetic" function
void quickSort(std::vector<Node*>& neighbours, int left, int right)
{
    if (left >= right)
        return;

    Node* pivot = neighbours[(left + right) / 2];
    int l = left;
    int r = right;

    while (l <= r)
    {
        while (neighbours[l]->name > pivot->name)
            ++l;
        while (neighbours[r]->name < pivot->name)
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

/// Sorts vector<Node*> in reverse-alphabetic
/// done in such way for easier popping elements from std::vector
void sortReverseAlphabetic(std::vector<Node*> &neighbours)
{
    quickSort(neighbours, 0, neighbours.size()-1);
}

/// main BFS algorithm
void BFS(std::vector<Node>& graph, int start, std::vector<std::string>& result)
{
    // main queue - from which elements are taken
    std::queue<Node*> _queue = std::queue<Node*>();

    // vector of children that are placed on next level
    // --------------------------------------------------------------
    // for example we have 2 and 3 - nodes that are children of root
    // so we have to go through all children of 2 and all children of 3
    // place them alphabetically and then write down in queue
    std::vector<Node*> nxtLvlChildren = std::vector<Node*>();

    // setting all |V| to unvisited
    setupDefault(graph, _queue, start);

    while (!_queue.empty())
    {
        Node* tmp;

        // going through nxt lvl children
        while (!_queue.empty())
        {
            // taking the top node from queue and popping it
            tmp = _queue.front();
            _queue.pop();

            // going through all children of tmp Node
            for (int i = 0; i < tmp->neighbours.size(); ++i)
            {
                if (!tmp->neighbours[i]->visited)
                {
                    tmp->neighbours[i]->visited = true;
                    nxtLvlChildren.push_back(tmp->neighbours[i]);
                }
            }

            // storing tmp in result vector
            result.push_back(tmp->name);
        };

        // sorting next level children in reverse-alphabetic order
        sortReverseAlphabetic(nxtLvlChildren);

        // placing elements IN ALPHABETIC order to vector-nxtLvlChildren
        while (!nxtLvlChildren.empty())
        {
            Node* nxt = nxtLvlChildren.back();
            _queue.push(nxt);
            nxtLvlChildren.pop_back();
        }
    }
}

//Задача - реализовать данный метод, решение должно быть в переменной result
void solve(std::vector<Node>& graph, int start, std::vector<std::string>& result)
{
    BFS(graph, start, result);
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
