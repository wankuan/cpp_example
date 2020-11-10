#include "operation.h"
#include <iostream>

Operation::~Operation()
{
    std::cout<<"deconstructor"<<std::endl;
}
void Operation::ToStart()
{
    state = op_state::DOING;
    std::cout<<"start"<<std::endl;
    Start();
}

void Operation::ToCancel()
{
    state = op_state::CANCEL;
    std::cout<<"be cancel"<<std::endl;
    CancelCallback();
}

void Operation::SetNotifyCallback(notify_func cb)
{
    notify_callback = cb;
}
bool Operation::CheckStateValid()
{
    return true;
}

void Operation::Finished()
{
    if(state == op_state::CANCEL)
    {
        std::cout << "Operation has been CANCEL, FINISHED WILL NOT DO" << std::endl;
        return;
    }
    FinishedCallback();
    state = op_state::FINSIHED;
    if(notify_callback != nullptr)
    {
        notify_callback(state);
    }
    else
    {
        std::cout << "notify is nullptr" << std::endl;
    }
    std::cout<<"Operation::Finished"<<std::endl;
}

op_state Operation::GetState()
{
    return state;
}
void Operation::Start()
{
    std::cout<<"Start"<<std::endl;
}

void Operation::FinishedCallback()
{
    std::cout<<"Operation::FinishedCallback"<<std::endl;
}

void Operation::CancelCallback()
{
    std::cout<<"CancelCallback"<<std::endl;
}