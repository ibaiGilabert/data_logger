# Data logger

Implementation of a server data logger for structured data.

The project also includes a client to test the application. It generates a random data and stream through TCP socket connection.

## Architecture overview

The data logger implements a server by using [Asio](https://think-async.com/Asio/) (header only) library. It will serve every sensor's data stream requests by managing concurrent sessions.

For each message received, it delegates the process to the 'Dispatcher', the class in charge of the business logic. It uses an [Thread Pool](https://www.geeksforgeeks.org/thread-pool-in-cpp/) pattern in order to distribute the workload in a handy way. The dispatcher task logs the data and notifies other components to  further data analysis following the [Observer pattern](https://refactoring.guru/design-patterns/observer).

So far, the unique observer is a the 'SafetyMgr' class, who performs the validation of the data received. For each monitored value, the system allows to concatenate validations by following the [Chain of Responsibility pattern](https://refactoring.guru/design-patterns/chain-of-responsibility).

The logging system as well as follows the alert handlers follow the [Strategy pattern](https://refactoring.guru/design-patterns/strategy) taking advantage of C++ polymorphism. The syntax is inspired by [Common Event Format (CEF)](https://www.microfocus.com/documentation/arcsight/arcsight-smartconnectors-8.4/pdfdoc/cef-implementation-standard/cef-implementation-standard.pdf).

## Notes about the style & code's guideline

The code follows (not 100%) the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html). The project includes a '.clang-format' in order to facilitate its maintenance.

The code documentation follows [Doxygen](https://www.doxygen.nl/) style although there is no configuration provided in that regard.


## Requirements

* CMake >= 3.10
* C++ compiler compliant with std++17 revision.

## Usage
The build process generates two executables, 'server' and 'client' such that:

* The server requires the port to listen.

* The client requires both IP and port.

```python
# Example of running server on port :1234
./server 1234

# Once client connects to the server, it will stream data each 1 second
./client localhost 1234
```

