#include <iostream>
#include <cstring>
using namespace std;

struct Node
{
  int key;
  Node **forward;
  Node(int, int);
};

Node::Node(int key, int level)
{
  this->key = key;
  forward = new Node *[level + 1];
  memset(forward, 0, sizeof(Node *) * (level + 1));
};

class SkipList
{
  int maxLvl;
  float P;
  int level;
  Node *header;

public:
  SkipList(int, float);
  int randomLevel();
  Node *createNode(int, int);
  void insertElement(int);
  void deleteElement(int);
  void displayList();
};

SkipList::SkipList(int maxLvl, float P)
{
  this->maxLvl = maxLvl;
  this->P = P;
  level = 0;
  header = new Node(-1, maxLvl);
};

int SkipList::randomLevel()
{
  float r = (float)rand() / RAND_MAX;
  int lvl = 0;
  while (r < P && lvl < maxLvl)
  {
    lvl++;
    r = (float)rand() / RAND_MAX;
  }
  return lvl;
};

Node *SkipList::createNode(int key, int level)
{
  Node *n = new Node(key, level);
  return n;
};

void SkipList::insertElement(int key)
{
  Node *current = header;
  Node *update[maxLvl + 1];
  memset(update, 0, sizeof(Node *) * (maxLvl + 1));

  for (int i = level; i >= 0; i--)
  {
    while (current->forward[i] != NULL &&
           current->forward[i]->key < key)
      current = current->forward[i];
    update[i] = current;
  }

  current = current->forward[0];

  if (current == NULL || current->key != key)
  {
    int rlevel = randomLevel();

    if (rlevel > level)
    {
      for (int i = level + 1; i < rlevel + 1; i++)
        update[i] = header;

      level = rlevel;
    }

    Node *n = createNode(key, rlevel);

    for (int i = 0; i <= rlevel; i++)
    {
      n->forward[i] = update[i]->forward[i];
      update[i]->forward[i] = n;
    }
  }
};

void SkipList::deleteElement(int key)
{
  Node *current = header;

  Node *update[maxLvl + 1];
  memset(update, 0, sizeof(Node *) * (maxLvl + 1));

  for (int i = level; i >= 0; i--)
  {
    while (current->forward[i] != NULL &&
           current->forward[i]->key < key)
      current = current->forward[i];
    update[i] = current;
  }

  current = current->forward[0];

  if (current != NULL and current->key == key)
  {
    for (int i = 0; i <= level; i++)
    {
      if (update[i]->forward[i] != current)
        break;
      update[i]->forward[i] = current->forward[i];
    }

    while (level > 0 &&
           header->forward[level] == 0)
      level--;
  }
};

void SkipList::displayList()
{
  Node *node = header->forward[0];
  while (node != NULL)
  {
    cout << node->key << " ";
    node = node->forward[0];
  }
  cout << "\n";
};

int main()
{
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  SkipList skipList(30, 0.7);
  int num;
  while (cin >> num)
  {
    if (num > 0)
      skipList.insertElement(num);
    else if (num < 0)
      skipList.deleteElement(abs(num));
    else if (num == 0)
    {
      skipList.displayList();
      return 0;
    }
  }
}
