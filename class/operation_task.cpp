#include "operation_task.h"
void OperationTask::add_operation(std::vector<Operation*> *vec)
{
    task_vec = *vec;
}

void OperationTask::handler_operation_state(op_state state)
{
    if(state == op_state::FINSIHED)
    {
        std::cout<< "into OperationTask callback, SUCCESS~" << std::endl;
    }
    else
    {
        std::cout << "into OperationTask callback, state FAIL!" << std::endl;
    }
    std::cout<< "[OPERATION]current thread PID " << std::this_thread::get_id() << std::endl;
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_condition.notify_all();
    }

}
void OperationTask::cancel()
{
    std::cout << "OperationTask be cancel " << std::endl;
    p_cur_operation->ToCancel();
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_condition.notify_all();
    }
}

void OperationTask::start()
{
    std::cout<<"OperationTask::start"<<std::endl;
    for(auto it:task_vec)
    {
        p_cur_operation = it;
        std::cout<<"OperationTask::operation start" << std::endl;
        p_cur_operation->SetNotifyCallback(std::bind(&OperationTask::handler_operation_state, this, std::placeholders::_1));
        p_cur_operation->Start();

        std::unique_lock<std::mutex> lock(m_mutex);
        m_condition.wait(lock, [this]{
            auto state = p_cur_operation->GetState();
            return (state == op_state::FINSIHED) || (state == op_state::CANCEL);
        });
        lock.unlock();
    }
    std::cout<<"OperationTask::finish"<<std::endl;
}
void OperationTask::CancelCallback()
{

}
