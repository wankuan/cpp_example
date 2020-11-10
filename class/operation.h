/**
 * @file operaion.h
 * @author kendrick (wankuan98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-10-21
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __OPERATION_H__
#define __OPERATION_H__

#include <iostream>
#include <thread>
#include <functional>
enum class op_state{
    WAIT,
    DOING,
    FINSIHED,
    CANCEL,
    ERROR
};
using notify_func = std::function<void(op_state)>;

class Operation
{
public:
    Operation():state(op_state::WAIT){};
    virtual ~Operation();
    void ToStart();
    void ToCancel();
    virtual void Start();
    void Finished();
    bool CheckStateValid();
    void SetNotifyCallback(notify_func cb);
    op_state GetState();
    virtual void FinishedCallback();
    virtual void CancelCallback();
private:
    notify_func notify_callback;
    op_state state;
};


class testoperation : public Operation{
public:
    testoperation():Operation(){

    }
    ~testoperation() override{

    }
    void balaba_thread()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        Finished();
    }
    void Start() override
    {
        std::cout<<"start by testoperation"<<std::endl;
        std::thread a(&testoperation::balaba_thread, this);
        a.detach();
    }
    void FinishedCallback() override
    {
        std::cout<< "this is my finished callback "<< std::endl;
    }
    void CancelCallback() override
    {
        std::cout << "I has been cancel, this is my operation callback" << std::endl;
    }
private:
};

class testoperation222 : public Operation{
public:
    testoperation222():Operation(){

    }
    ~testoperation222() override{

    }
    void Start() override
    {
        std::cout<<"start by testoperation222"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        Finished();
    }
private:
};

#endif