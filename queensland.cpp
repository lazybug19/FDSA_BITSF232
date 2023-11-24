#include <bits/stdc++.h>
using namespace std;

class FamilyNode
{
public:
  vector<FamilyNode *> children;
  string name;
  // declare other members as per question's requirement
  int age;
  double income;
  string occupation;
};

// Note:Input of nodes will be taken in order according to pre-order traversal of tree.
FamilyNode *buildTree()
{
  string name;
  cout << "Enter name of member: " << endl;
  cin >> name;
  // Take other parameters as inputs
  int age;
  cout << "Enter age of member: " << endl;
  cin >> age;
  double income;
  cout << "Enter income of member: " << endl;
  cin >> income;
  string occupation;
  cout << "Enter occupation of member: " << endl;
  cin >> occupation;
  // 2
  int numOfChildren;
  cout << "Enter number of children: " << endl;
  cin >> numOfChildren;

  cout << "::> Details: " << name << " " << age << " " << income << " " << occupation << " " << numOfChildren << endl;

  FamilyNode *node = new FamilyNode();
  // Initialize the node
  node->name = name;
  node->age = age;
  node->income = income;
  node->occupation = occupation;
  for (int i = 0; i < numOfChildren; i++)
  {
    // Build tree rooted at child i. Add this to children vector of current node.
    node->children.push_back(buildTree());
  }
  return node;
}

// This function checks if a node with given parameters exists or not
bool checkIfNodeExists(FamilyNode *node, string name, int age, float income, string occupation)
{
  // Complete the code
  bool res = false;
  if (node->name.compare(name) == 0 && node->age == age && node->income == income && node->occupation.compare(occupation) == 0)
    return true;
  else
  {
    for (int i = 0; i < node->children.size(); i++)
      res = res || checkIfNodeExists(node->children[i], name, age, income, occupation);
  }
  return res;
}

void removeNode(FamilyNode *node, FamilyNode *parent, string name, int age, float income, string occupation)
{
  if (node->name.compare(name) == 0 && node->age == age && node->income == income && node->occupation.compare(occupation) == 0) // Complete the condition to check if current node is required node
  {
    // Complete the code to remove current node from tree
    // Replace current node with children having highest income
    // Update the children vector of current node and parent accordingly
    FamilyNode *maxNode = NULL;
    for (int i = 0; i < node->children.size(); i++)
    {
      if (maxNode == NULL)
        maxNode = node->children[i];
      else
      {
        if (node->income < node->children[i]->income && maxNode->income < node->children[i]->income) // checks for multiple nodes with highest income
          maxNode = node->children[i];
      }
    }

    // node to be removed, maxNode to be replaced
    FamilyNode *temp = node;
    cout << "Node to be removed: " << node->name << " " << node->age << " " << node->income << " " << node->occupation << endl;

    // the node has no children
    if (maxNode == NULL)
    {
      delete temp;
      // update the vector
      for (int i = 0; i < parent->children.size(); i++)
      {
        if (parent->children[i]->name.compare(node->name) == 0 && parent->children[i]->age == node->age && parent->children[i]->income == node->income && parent->children[i]->occupation.compare(node->occupation) == 0)
        {
          parent->children.erase(parent->children.begin() + i);
          break;
        }
      }
      return;
    }

    // Otherwise
    for (auto x : node->children)
    {
      if (x->name.compare(maxNode->name) == 0 && x->age == maxNode->age && x->income == maxNode->income && x->occupation.compare(maxNode->occupation) == 0)
        continue;
      maxNode->children.push_back(x); // new node vector update
    }

    for (int i = 0; i < parent->children.size(); i++)
    {
      if (parent->children[i]->name.compare(node->name) == 0 && parent->children[i]->age == node->age && parent->children[i]->income == node->income && parent->children[i]->occupation.compare(node->occupation) == 0)
      {
        parent->children[i] = maxNode; // parent vector update
        break;
      }
    }

    delete (temp);
    node = maxNode;
  }
  // Continue the process for other nodes
  parent = node;

  for (int i = 0; i < parent->children.size(); i++)
    removeNode(parent->children[i], parent, name, age, income, occupation);
  return;
}

// debug preorder traversal
void preorder(FamilyNode *node)
{
  stack<FamilyNode *> s;
  vector<string> v;
  s.push(node);
  while (!s.empty())
  {
    FamilyNode *temp = s.top();
    s.pop();
    v.push_back(temp->name);
    for (int i = temp->children.size() - 1; i >= 0; i--)
      s.push(temp->children[i]);
  }
  for (string x : v)
  {
    cout << x << " ";
  }
}

// Complete the recursive function to calculate total income of a family
float getTotalIncome(FamilyNode *node)
{
  float totalIncome = node->income; // Complete initialization of totalIncome
  for (int i = 0; i < node->children.size(); i++)
  {
    // Complete the code
    totalIncome += node->children[i]->income;
  }
  return totalIncome;
}

// Complete the recursive function to calculate total income of a family
int getTotalAge(FamilyNode *node)
{
  int totalAge = node->age; // Complete initialization of totalIncome
  for (int i = 0; i < node->children.size(); i++)
  {
    // Complete the code
    totalAge += node->children[i]->age;
  }
  return totalAge;
}

// The function returns the ancestor of family having highest income-to-age ratio
FamilyNode *getHighestIncomeAgeRatioFamily(vector<FamilyNode *> &familyTrees)
{
  // Complete the code
  FamilyNode *maxFamilyRatio;
  float maxRatio = 0;
  for (int i = 0; i < familyTrees.size(); i++)
  {
    float currFamilyTotalIncome = getTotalIncome(familyTrees[i]);
    int currFamilyTotalAge = getTotalAge(familyTrees[i]);
    float currFamilyRatio = currFamilyTotalIncome / currFamilyTotalAge;
    // Complete the code here
    if (currFamilyRatio > maxRatio)
    {
      maxRatio = currFamilyRatio;
      maxFamilyRatio = familyTrees[i];
    }
  }
  // Return the ancestor node of family with highest income-to-age ratio
  return maxFamilyRatio;
}

bool comp(FamilyNode *node1, FamilyNode *node2)
{
  return getTotalIncome(node1) > getTotalIncome(node2);
}

void printFamiliesInDecrOrder(vector<FamilyNode *> &familyTrees)
{
  // Complete the code
  sort(familyTrees.begin(), familyTrees.end(), comp);
  for (auto x : familyTrees)
  {
    cout << x->name << " ";
  }
  cout << endl;
}

int main()
{
  int numOfFamilies;
  cout << "Enter the number of families: \n";
  cin >> numOfFamilies;

  vector<FamilyNode *> familyTrees; // This vector stores ancestor nodes of all families

  for (int i = 0; i < numOfFamilies; i++)
  {
    familyTrees.push_back(buildTree());
  }

  while (1)
  {

    int choice;
    cout << "\n\n1. Remove node" << endl;
    cout << "2. Find Highest Income-To-Age-Ratio Family" << endl;
    cout << "3. Print Family(Ancestor) Names in Decreasing Income Order" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: " << endl;

    cin >> choice;

    switch (choice)
    {
    case 1:
    {
      int num;
      cout << "Enter Family member whose node is to be removed: " << endl;
      cin >> num;
      cout << "Chosen Family: " << num << endl;
      cout << "Enter name, age, income and occupation of member to be removed: " << endl;
      string name, occupation;
      int age;
      float income;
      cin >> name >> age >> income >> occupation;

      if (!checkIfNodeExists(familyTrees[num - 1], name, age, income, occupation))
        cout << "No such family member exists: " << name << " " << age << " " << income << " " << occupation << endl;
      else
      {
        cout << "Family member exists: " << name << " " << age << " " << income << " " << occupation << endl;
        removeNode(familyTrees[num - 1], NULL, name, age, income, occupation);
      }
      cout << "Preorder traversal of family after removal: ";
      preorder(familyTrees[num - 1]);
      break;
    }
    case 2:
    {
      FamilyNode *node = getHighestIncomeAgeRatioFamily(familyTrees);
      cout << "Name of ancestor of family with highest total income is: " << node->name << endl;
      break;
    }
    case 3:
    {
      printFamiliesInDecrOrder(familyTrees);
      break;
    }
    case 4:
    {
      return 0;
      break;
    }
    default:
    {
      cout << "Incorrect choice!!!" << endl;
      break;
    }
    }
  }
  return 0;
}