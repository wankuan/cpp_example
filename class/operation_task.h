/**
 * @file operation_task.h
 * @author kendrick (wankuan98@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-10-26
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __OPERATION_TASK_H__
#define __OPERATION_TASK_H__

#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "operation.h"

class OperationTask{
public:
    OperationTask() = default;
    ~OperationTask() = default;
    void add_operation(std::vector<Operation*> *vec);
    void start();
    void cancel();
    void handler_operation_state(op_state state);
    void CancelCallback();
private:
    std::vector<Operation*> task_vec;
    Operation *p_cur_operation;
    std::mutex m_mutex;
    std::condition_variable m_condition;
};

#endif