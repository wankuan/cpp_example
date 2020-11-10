#include "operation.h"
#include "operation_task.h"

OperationTask *p_task = nullptr;
void test_stop();

void test_stop()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    p_task->cancel();
}


int main()
{
    auto op1 = new testoperation();
    auto op2 = new testoperation222();

    std::vector<Operation*> _vec;
    _vec.push_back(op1);
    _vec.push_back(op2);

    OperationTask my_task;
    p_task = &my_task;
    my_task.add_operation(&_vec);
    std::thread my_thread(test_stop);
    my_task.start();
    // my_thread.join();
    return 0;
}

