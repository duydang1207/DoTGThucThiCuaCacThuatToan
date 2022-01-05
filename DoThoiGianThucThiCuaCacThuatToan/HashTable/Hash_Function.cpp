﻿#include "dataStructure.h"


int HashFunction(string url, int HASHTABLESIZE)
{
    int hashValue = 0;
    for (int i = 0; i < url.length(); i++)
        hashValue += url[i] * i;
    return hashValue % HASHTABLESIZE;
}
int CollisionResolutionInsert(HashTable* URL[], int hashValue, int HASHTABLESIZE)
{
    while (URL[hashValue]->check)
    {
        hashValue = (hashValue + 1) % HASHTABLESIZE;
    }
    return hashValue;
}
