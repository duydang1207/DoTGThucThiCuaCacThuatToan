#include "algorithms.h"

using namespace std;
int Search(HashTable* URL[], string url, int HASHTABLESIZE)
{
    int hashValue = HashFunction(url, HASHTABLESIZE); //gọi hash function để tạo hash value
    
    int valueLinear = 1;
    while (URL[hashValue]->key != url && valueLinear < HASHTABLESIZE)
    {
        hashValue = (hashValue + valueLinear) % HASHTABLESIZE;
        valueLinear++;
    }
    if (URL[hashValue]->key == url)
        return hashValue;
    return -1;
}
void Insert(HashTable* URL[], string url, int HASHTABLESIZE)
{
    int hashValue = HashFunction(url, HASHTABLESIZE);

    hashValue = CollisionResolutionInsert(URL, hashValue, HASHTABLESIZE);

    URL[hashValue]->check = true;
    URL[hashValue]->key = url;

    //Tìm url cha
    string url2 = url;
    url2.erase(url2.rfind('/'), url.length());//url2 là url phân cấp trước nó
    int indexParent = Search(URL, url2, HASHTABLESIZE); //tìm index cha

    if (indexParent >= 0 && URL[indexParent]->check)
    {
        Node* temp = URL[indexParent]->headNext;
        if (temp == nullptr)
        {
            temp = new Node();
            temp->next = nullptr;
            temp->index = hashValue;
            URL[indexParent]->headNext = temp;
        }
        else
        {
            while (temp->next != nullptr) temp = temp->next;
            Node* node = new Node();
            node->next = nullptr;
            node->index = hashValue;
            temp->next = node;
        }
        URL[hashValue]->prev = indexParent;
    }
}

bool Delete (HashTable* URL[], string url, int HASHTABLESIZE)
{
    int hashValue = Search(URL, url, HASHTABLESIZE);
    //xoa index cua ds next co lien quan den con
    if (hashValue < 0)
        return false;
    int indexParent = URL[hashValue]->prev;
    if (indexParent >= 0)
    {
        Node* temp1 = URL[indexParent]->headNext;
        while (temp1->index != hashValue && temp1->next != nullptr) temp1 = temp1->next;

        if (temp1 == URL[indexParent]->headNext)
            URL[indexParent]->headNext = temp1->next;
        else
        {
            Node* temp2 = URL[indexParent]->headNext;
            while (temp2->next->index != hashValue && temp2->next != nullptr) temp2 = temp2->next;
            temp2->next = temp1->next;
        }
    }

    int k = 0;
    int arrayHashValue[50];
    Node* temp_n = URL[hashValue]->headNext;
    while (temp_n != nullptr)
    {
        if (URL[temp_n->index]->key.find(URL[hashValue]->key) == 0)//kiem tra cac next co cung url cha khong
            arrayHashValue[k++] = temp_n->index;
        temp_n = temp_n->next;
    }
    delete URL[hashValue];//xoa vi tri hashvalue
    URL[hashValue] = new HashTable;

    //xoa cac next con co lien quan
    int i = 0;
    while (i != k)
    {
        Node* node = URL[arrayHashValue[i]]->headNext;
        while (node != nullptr)
        {
            if (URL[node->index]->key.find(URL[arrayHashValue[i]]->key) == 0)
                arrayHashValue[k++] = node->index;
            node = node->next;
        }
        delete URL[arrayHashValue[i]];
        URL[arrayHashValue[i]] = new HashTable;
        i++;
    }
    return true;
}



//va cham
int CollisionResolutionInsert_VC(HashTable* URL[], int hashValue, int prime, int& step, bool& check)
{
    while (URL[hashValue]->check)
    {
        check = true;
        step++;
        hashValue = (hashValue + 1) % prime;
    }
    return hashValue;
}
void Insert_VC(HashTable* URL[], string url, int prime, double& max, double& min, double& sum, int& sum_a)
{
    int hashValue = HashFunction(url, prime);

    int step = 0;
    bool check = false;
    hashValue = CollisionResolutionInsert_VC(URL, hashValue, prime, step, check);

    sum += step;
    if (step > max)
        max = step;
    if (step < min && step>0)
        min = step;
    if (check)
        sum_a++;

    URL[hashValue]->check = true;
    URL[hashValue]->key = url;
    //Tìm url cha
    string url2 = url;
    url2.erase(url2.rfind('/'), url.length());//url2 là url phân cấp trước nó
    int indexParent = Search(URL, url2, prime); //tìm index cha

    if (indexParent >= 0 && URL[indexParent]->check)
    {
        Node* temp = URL[indexParent]->headNext;
        if (temp == nullptr)
        {
            temp = new Node();
            temp->next = nullptr;
            temp->index = hashValue;
            URL[indexParent]->headNext = temp;
        }
        else
        {
            while (temp->next != nullptr) temp = temp->next;
            Node* node = new Node();
            node->next = nullptr;
            node->index = hashValue;
            temp->next = node;
        }
        URL[hashValue]->prev = indexParent;
    }
}