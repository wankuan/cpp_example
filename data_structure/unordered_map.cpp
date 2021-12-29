/**
 * @file hash_map.cpp
 * @author kendrick (wankuan98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-12-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <iostream>
// #include <unordered_map>
#include <utility>
#include <vector>
#include <stdio.h>
#include <stdarg.h>
#include <thread>
#include <string>
using namespace std;


typedef size_t bucket_size_t;

static const size_t default_bucket_size = 5;

#define HASH_INFO(x, ...)    _hash_print("[INFO] " x "", ##__VA_ARGS__)
#define HASH_ERROR(x, ...)   _hash_print("[ERR ] " x "", ##__VA_ARGS__)

#ifdef ENABLE_DEBUG
#define HASH_DEBUG(x, ...)   _hash_print("[DGB ] " x "", ##__VA_ARGS__)
#else
#define HASH_DEBUG(x, ...)
#endif
#define HASH_WARN(x, ...)    _hash_print("[WARN] " x "", ##__VA_ARGS__)
// #define HASH_INFO(x)   _hash_print("[INFO] " x)

#define _hash_print(x, ...) \
do                          \
{\
    printf("" x "",##__VA_ARGS__);\
} while (0)



enum NodeState
{
    EMPTY = 0,
    USED  = 1
};

template<class K, class V, class KeyOfValue, class HashFunc>
class HashIterator;
/* hash map实现
@ 哈希函数-余数方法
@
*/
// 使用模板偏特化对string进行编码
template<class K>
struct HashFunc1
{
    bucket_size_t operator() (const K &key, const bucket_size_t &cur_bucket_size)
    {
        return (key % cur_bucket_size);
    }
};
template<class K>

bucket_size_t hash_func(const K &key, const bucket_size_t &cur_bucket_size)
{
    return (key % cur_bucket_size);
}


// 这里探究class 和 struct 仿函数区别
template<class K, class V>
class MapKeyOfValue{
    const V& operator()(const pair<K,V> & data)
    {
        return data.first;
    }
};

template<class K, class V>
class HashNode{
public:
    HashNode(): state(EMPTY), next_node(nullptr){}
    pair<K,V>   data;
    NodeState   state;
    HashNode    *next_node;
};


template<class K, class V, class KeyOfValue = MapKeyOfValue<K,V>, class HashFunc = HashFunc1<K>>
class HashBucket{
public:
    friend  HashIterator<K, V, KeyOfValue, HashFunc>;
    typedef HashIterator<K, V, KeyOfValue, HashFunc> iterator;
    HashBucket(size_t size = default_bucket_size):m_bucket_count(size), m_node_begin(nullptr)
    {
        m_bucket_vector.resize(m_bucket_count);
        HASH_INFO("HashBucket constructor...\r\n");
    }
    iterator begin(void)
    {
        HashNode<K, V> *_node = nullptr;
        for(auto &_bucket: m_bucket_vector){
            _node = &_bucket;
            if(_node == nullptr){
                HASH_ERROR("hash_bucket nullptr");
                return iterator(this, nullptr);
            }
            do{
                // 只要不是空结点，就一直查找
                if(_node->state == USED){
                    return iterator(this, _node);
                }
                _node = _node->next_node;
            }while(_node != nullptr);
            // 还是没找到
        }
        return iterator(this, nullptr);
    }
    iterator end(void){
        return iterator(this, nullptr);
    }
    iterator m_bucket_vectorend(void)
    {
        return iterator(this, nullptr);
    }
    // TODO: 这里迭代器应该接受结点地址和bucket地址
    iterator insert(const pair<K,V> &_data)
    {
        size_t node_list_size = 0;
        // if(!CheckCapacity()){
        //     EnlargeCapacity();
        // }
        // 计算散列值对应的散列存储位置
        size_t index = find_node_index(_data.first);
        // 获得散列地址的结点地址
        HashNode<K, V> *_node = &m_bucket_vector[index];
        if(_node == nullptr)
        {
            HASH_ERROR("cur bucket had been destory");
            return iterator(this, nullptr);
        }
        // 编译结点，找到空结点或者相同的键地址
        while(_node->state !=  EMPTY){
            // 找到相同的键
            if(_node->data.first == _data.first)
            {
                break;
            }
            // 找到空结点并插入
            if(_node->next_node == nullptr){
                _node->next_node = new HashNode<K, V>();
            }
            _node = _node->next_node;
            node_list_size++;
        }
        // 赋值该结点的值
        _node->data.first  = _data.first;
        _node->data.second = _data.second;
        _node->state       = USED;
        HASH_INFO("insert OK, hash func ret index:%ld, first:%d, second:%d, node list:%ld\r\n",
                    index, _node->data.first, _node->data.second, node_list_size);
        // _bucket_used_cout++;
        // return true;
        return iterator(this, _node);
    }
    iterator find(const K key)
    {
        size_t index = find_node_index(key);
        HashNode<K, V> *_node = &m_bucket_vector[index];
        if(_node == nullptr){
            HASH_ERROR("find error..index:%ld, key:%d", index, _node->data.first);
        }
        do{
            // 找到结点，退出
            if(_node->state == USED && _node->data.first == key){
                return iterator(this, _node);
            }
            _node = _node->next_node;
        }while(_node != nullptr);
        HASH_DEBUG("can not find key..index:%ld, key:%d\r\n", index, key);
        return iterator(this, nullptr);
    }
    size_t bucket_count(void)
    {
        return m_bucket_count;
    }
    size_t bucket_size(void)
    {

    }
    ostream &print_all_bucket(ostream &_stream)
    {
        for(auto it = begin(); it != end(); ++it){
            _stream << "key:" << *it.first << " val:" << *it.second << endl;
        }
        return _stream;
    }
private:
    size_t find_node_index(K key)
    {
        // return hash_func<K>(key);
        return hashfunc(key, m_bucket_count);
    }
    HashFunc hashfunc;
    size_t m_bucket_count;
    vector<HashNode<K, V>> m_bucket_vector;
    HashNode<K, V>         *m_node_begin;
};


template<class K, class V, class KeyOfValue, class HashFunc>
class HashIterator{
public:

    typedef HashIterator<K, V, KeyOfValue, HashFunc>    iterator;
    typedef HashBucket<K, V, KeyOfValue, HashFunc>      hash_bucket;
    typedef HashNode<K, V>                                 node;

    HashIterator(hash_bucket *_bucket, node * _node): m_bucket(_bucket), m_node(_node)
    {
        HASH_DEBUG("HashIterator default constructor\r\n");
    }
    HashIterator(const iterator &it)
    {
        m_bucket = it.m_bucket;
        m_node   = it.m_node;
        HASH_DEBUG("HashIterator copy constructor\r\n");
    }
    HashIterator(const iterator &&it)
    {
        m_bucket = it.m_bucket;
        m_node   = it.m_node;
        HASH_DEBUG("HashIterator move constructor\r\n");
    }
    HashIterator &operator=(const iterator &it)
    {
        if(this != &it)
        {
            m_bucket = it.m_bucket;
            m_node   = it.m_node;
        }
        HASH_DEBUG("HashIterator copy assign\r\n");
        return *this;
    }
    HashIterator &operator=(const iterator &&it)
    {
        if(this != &it)
        {
            m_bucket = it.m_bucket;
            m_node   = it.m_node;
        }
        HASH_INFO("HashIterator move assign\r\n");
        return *this;
    }
    pair<K,V> &operator*(){
        return m_node->data;
    }
    bool operator ==(HashIterator it){
        return (this->m_node == it.m_node);
    }
    bool operator !=(HashIterator it){
        return !(*this == it);
    }
    // 前置自增
    iterator &operator++(){
        size_t node_list_size = 0;
        bool is_find_node = false;
        size_t index = m_bucket->find_node_index(m_node->data.first);
        HASH_DEBUG("operator++ index:%ld\r\n", index);
        // 获得散列地址的结点地址
        for(auto i = index; i < m_bucket->m_bucket_count; ++i){
            HashNode<K, V> *_node = &m_bucket->m_bucket_vector[i];
            while(_node != nullptr){
                // 找到当前的结点
                if(is_find_node == false){
                    if(_node->state == USED && _node->data.first == m_node->data.first){
                        is_find_node = true;
                    }
                }else{
                    if(_node->state == USED){
                        m_node  = _node;
                        return *this;
                    }
                }
                HASH_DEBUG("insert OK, hash func ret index:%ld, first:%d, second:%d, node list:%ld\r\n",
                    i, _node->data.first, _node->data.second, node_list_size);
                // 继续找下一个结点
                _node = _node->next_node;
                node_list_size++;
            }
        }
        m_node = nullptr;
        HASH_DEBUG("operator++ next node is nullptr\r\n");
        return *this;
    }
    iterator operator++(int){
        iterator _it = *this;
        ++(*this);
        return _it;
    }
private:
    hash_bucket *m_bucket;
    node        *m_node;
};


template<class K, class V, class KeyOfValue = MapKeyOfValue<K,V>, class HashFunc = HashFunc1<K>>
class unordered_map{
typedef HashIterator<K, V, KeyOfValue, HashFunc>    iterator;
typedef HashBucket<K, V, KeyOfValue, HashFunc>      hash_bucket;
public:
    unordered_map(size_t size = default_bucket_size):m_hash_bucket(size),m_max_load_factor(0.8){
        HASH_INFO("hash map constructor...\r\n");
    }
    iterator insert(const pair<K,V> & _pair)
    {
        return m_hash_bucket.insert(_pair);
    }
    iterator find(const K _key)
    {
        return m_hash_bucket.find(_key);
    }
    iterator begin(void)
    {
        return m_hash_bucket.begin();
    }
    iterator end(void)
    {
        return m_hash_bucket.end();
    }
private:
    hash_bucket      m_hash_bucket;
    float            m_max_load_factor;
};

ostream& operator << (ostream &os, HashBucket<int,int> &bucket)
{

    for(auto it = bucket.begin(); it != bucket.end(); ++it){
        os << "key:" << (*it).first << " val:" << (*it).second << endl;
    }
    return os;
}


unordered_map<int, int> map;

void test_find(int key)
{
    auto it = map.find(key);
    if(it != map.end()){
        printf("key:%d val:%d\r\n", (*it).first, (*it).second);
    }
    else{
        printf("can not find key:%d\r\n", key);
    }
}

void test_iterator_add_value(int value)
{
    printf("====before use iterator add value =======");
    for(auto it = map.begin(); it != map.end(); ++it){
        printf("key:%d val:%d \r\n", (*it).first, (*it).second);
    }
    for(auto it = map.begin(); it != map.end(); ++it){
        (*it).second += value;
    }
    printf("====after use iterator add value =======");
    for(auto it = map.begin(); it != map.end(); ++it){
        printf("key:%d val:%d \r\n", (*it).first, (*it).second);
    }
}

int main()
{
    auto it = map.insert({1, 2});
    map.insert({1, 3});
    map.insert({1, 100});
    map.insert({2, 4});

    map.insert({6, 2});

    map.insert({11, 3});
    for(auto it = map.begin(); it != map.end(); ++it){
        cout << "key:" << (*it).first << " val:" << (*it).second << endl;
    }
    test_find(0);
    test_find(1);
    test_find(2);

    test_iterator_add_value(10);
    return 0;
}