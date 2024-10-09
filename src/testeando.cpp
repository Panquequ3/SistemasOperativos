#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable> //proporciona una forma de manejar la sincronización entre hilos
#include <queue>

queue<int> taskQueue; // Cola de tareas
mutex queueMutex;      // Mutex para proteger la cola
condition_variable cv; // Variable de condición
bool finished = false;      // Variable para indicar si todas las tareas han sido procesadas

void worker(int id) {
    while (true) {
        unique_lock<mutex> lock(queueMutex);
        //lambdas en c++ : [ captures ] ( parameters ) -> return_type {
       // cuerpo de la función}
        cv.wait(lock, [] { return !taskQueue.empty() || finished; });

        if (!taskQueue.empty()) {
            int task = taskQueue.front();
            taskQueue.pop();
            lock.unlock(); // Liberar el mutex antes de procesar

            // Procesar la tarea
            cout << "Hilo " << id << " procesando tarea " << task << endl;
        } else if (finished) {
            break; // Salir si no hay más tareas y se ha terminado
        }
    }
}

int main() {
    const int numThreads = 3; // Número de hilos
    const int numTasks = 10;  // Número de tareas

    // Crear hilos trabajadores
    thread workers[numThreads];

    for (int i = 0; i < numThreads; ++i) {
        workers[i] = thread(worker, i);
    } //quedan en espera hasta que hayan tareas en cola
    

    // Agregar tareas a la cola
    for (int i = 0; i < numTasks; ++i) {
        {
            lock_guard<mutex> lock(queueMutex);
            taskQueue.push(i);
        }
        cv.notify_one(); // Notificar a un hilo
        //si todos los hilos estan ocupados, la nueva tarea se queda esperando a un hilo
    }

    // Marcar que todas las tareas han sido agregadas
    {
        lock_guard<mutex> lock(queueMutex);
        finished = true;
    }
    cv.notify_all(); // Notificar a todos los hilos para que salgan

    // Esperar a que todos los hilos terminen
    for (auto& worker : workers) {
        worker.join();
    }

    return 0;
}

// salida
// Hilo 2 procesando tarea 0
// Hilo 2 procesando tarea 3
// Hilo 2 procesando tarea 4
// Hilo 2 procesando tarea 5
// Hilo 2 procesando tarea 6
// Hilo 2 procesando tarea 7
// Hilo 2 procesando tarea 8
// Hilo 2 procesando tarea 9
// Hilo 0 procesando tarea 1
// Hilo 1 procesando tarea 2
