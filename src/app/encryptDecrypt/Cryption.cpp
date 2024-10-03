#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"


int executeCryption(const std:: string &taskData){
    Task task= Task::fromString(taskData);
    ReadEnv env;

    std::string envKey= env.getenv();
    int key= std::stoi(envKey);


    if(task.action== Action:: ENCRYPT){
        
    }


}
