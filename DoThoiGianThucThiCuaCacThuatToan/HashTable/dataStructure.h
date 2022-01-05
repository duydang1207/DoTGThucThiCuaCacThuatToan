#pragma once
#include "header.h"

struct Node {
    Node* next = nullptr;
    int index = -1;
};
struct HashTable
{
    bool check = false;
    string key = "";
    Node* headNext = nullptr;
    int prev = -1;
};

int HashFunction(string url, int HASHTABLESIZE);
int CollisionResolutionInsert(HashTable* URL[], int hashValue, int HASHTABLESIZE);


