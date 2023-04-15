//*****************************************************************************
// purpose: driver Lab 3
//  author: Azim Bazarov (ab4908)
//*****************************************************************************
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "nodes.h"

void nodeExamples()
{
  //IntegerNode a(14);
  //cout << a << endl;
  IntegerNode a(14);
  cout << a << endl;

  //FloatNode b(99.99);
  //cout << b << endl;
  FloatNode b(99.99);
  cout << b << endl;

  //StringNode c("testing");
  //cout << c << endl;
  StringNode c("testing");
  cout << c << endl;

  cout << endl;
}

int main( int argc, char* argv[] ) {

  // create and print an example of each of the DataNodes
  nodeExamples();
  cout << endl;
  
  // Create a vector (a resizable list) of pointers to DataNodes
  vector<DataNode*> aVector;

  // Add four data item pointers to the vector: "first", 2, 3.14, "fourth"
  // aVector.push_back(new StringNode("first"));
  aVector.push_back(new StringNode("first")); // first
  aVector.push_back(new IntegerNode(2)); // 2
  aVector.push_back(new FloatNode(3.14)); // 3.14
  aVector.push_back(new StringNode("fourth")); // fourth
  

  // Output the size of the vector
  cout<<"Size of the vector: "<< aVector.size()<< endl;

  // Output the items pointed to by vector elements using the .at method
  for (int i=0; i < aVector.size(); i = i + 1)
  {
    cout << *(aVector.at(i)) << endl;
  }
  cout << endl;

  // Add four more data item pointers to the vector: 5, 6.28, "seventh", "eighth"
    aVector.push_back(new IntegerNode(5)); // 5
    aVector.push_back(new FloatNode(6.28)); // 6.28
    aVector.push_back(new StringNode("seventh")); // seventh
    aVector.push_back(new StringNode("eighth")); // eigth

  // Output the size of the vector
 cout <<"Size of the vector: "<< aVector.size() <<endl;

  // Output the items pointed to by vector elements using an iterator
  vector<DataNode*>::iterator it;
  for(it = aVector.begin(); it < aVector.end(); it++) 
  {
    cout << *(*it) <<endl;
  }
  cout << endl;

  // Delete the items pointed to by vector elements
  // Do NOT hard code the size of the vector
  // To indicate that the node is deleted, set the item pointer to nullptr
  for (int i=0;i<aVector.size(); i++ ) 
  {
    delete (aVector.at(i)); //delete
    aVector[i]=nullptr; // sets the item poiner to nullptr
  }
  cout<<endl;

  // Output the size of the vector
 cout<<"Size of the vector: "<<aVector.size() << endl;

  // Clear the vector
  aVector.clear();

  // Output the size of the vector
  cout << "Size of the vector: " << aVector.size() << endl;
  return 0;
}

